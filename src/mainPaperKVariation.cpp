#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/utils.hpp"

int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions

    std::vector<std::string> input_filenames = {"/groups/genscale/NGSdatasets/metagenomics/hmp/SRS014107_SRS016349_fasta/SRS014107.denovo_duplicates_marked.trimmed.1.fasta"};
    bool canonical = false;
    std::string queryFile = "/groups/genscale/NGSdatasets/metagenomics/hmp/SRS014107_SRS016349_fasta/SRS016349.denovo_duplicates_marked.trimmed.1.fasta";
    double epsilonPercent = 5.0;
    unsigned long long z = 3;

    std::string querySeq = extractContentFromFastqGz(queryFile);

    std::cout << "[" << std::endl;
    for (unsigned long long k_iter = 21; k_iter <= 35; k_iter += 2) {
        auto t0 = std::chrono::high_resolution_clock::now();
        robin_hood::unordered_set<std::string> truthBigK = truth::indexFastas(input_filenames, k_iter, canonical);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, k_iter);
        auto t2 = std::chrono::high_resolution_clock::now();

        const auto& [normalfilter, numberOfIndexedElements] = findere_internal::indexFastasGivenTruth(input_filenames, truthBigK, numHashes, k_iter, epsilonPercent, canonical);

        const unsigned long long n = bigTruth.size();

        unsigned long long m = -(n / log(1 - ((double)epsilonPercent / (double)100)));
        m = m + 8 - (m % 8);
        unsigned long long bits = m;

        auto t6 = std::chrono::high_resolution_clock::now();
        std::vector<bool> noQTFSimpleQuery = noQTF::query(normalfilter, querySeq, k_iter);
        auto t7 = std::chrono::high_resolution_clock::now();

        std::cout << "    {" << std::endl;
        std::cout << "        \"param\": {" << std::endl;
        std::cout << "            \"k\": " << k_iter << "," << std::endl;
        std::cout << "            \"z\": " << z << "," << std::endl;
        std::cout << "            \"bits\": " << m << std::endl;
        std::cout << "        }," << std::endl;

        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = findere::indexFastasGivenBits(input_filenames, numHashes, k_iter, z, bits, canonical);

        auto t3 = std::chrono::high_resolution_clock::now();
        std::vector<bool> QTFOnBloomFilter = findere::query(smallFilter, querySeq, k_iter, z);
        auto t4 = std::chrono::high_resolution_clock::now();
        std::vector<bool> QTFOnBloomFilterSkip = findere::query(smallFilter, querySeq, k_iter, z, true);
        auto t5 = std::chrono::high_resolution_clock::now();

        findere_internal::printTime(t0, t1, t2, t3, t4, t5, t6, t7, timeTakenMs);
        findere_internal::printScore(findere_internal::getScore(bigTruth, QTFOnBloomFilter), "queryBF", false, sizeOfBloomFilter);
        findere_internal::printScore(findere_internal::getScore(bigTruth, QTFOnBloomFilterSkip), "queryBFSkip", false, sizeOfBloomFilter);
        findere_internal::printScore(findere_internal::getScore(bigTruth, noQTFSimpleQuery), "normalfilter", true, numberOfIndexedElements);

        std::cout << "    }";
        if (k_iter < 35) {
            std::cout << ",";
        }
        std::cout << std::endl;

        delete smallFilter;
        delete normalfilter;
    }
    std::cout << "]" << std::endl;
    return 0;
}
