#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"

int main(int argc, char* argv[]) {
    // in Python,after import numpy as np: [int(x) for x in np.linspace(100, 2674199464*3, 100)] gives you this:
    std::vector<unsigned long long> membits = {409909080,683181800,956454520,1229727240,2049545400,2459454480,2869363560,3279272640,3552545360,3825818080,4099090800,4372363520,4782272600,5465454400,64877120000,65142176000,65417408000,65684928000,66101760000,66780128000};

    unsigned long long K = 31;
    unsigned long long z = 3;

    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);

    std::cout << "[" << std::endl;

    std::vector<std::string> input_filenames = {"/groups/genscale/NGSdatasets/metagenomics/hmp/data/SRS014107/SRS014107.denovo_duplicates_marked.trimmed.1.fastq.gz"};
    std::string queryFile = "/groups/genscale/NGSdatasets/metagenomics/hmp/data/SRS016349/SRS016349.denovo_duplicates_marked.trimmed.1.fastq.gz";

    std::string querySeq = extractContentFromFastqGz(queryFile);

    robin_hood::unordered_set<std::string> truthBigK = truth::indexFastqGz(input_filenames, K, false);
    robin_hood::unordered_set<std::string> truthSmallK = truth::indexFastqGz(input_filenames, K - z, false);
    std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, K);

    for (const auto& membit : membits) {
        const auto& [normalfilter, numberOfIndexedElements] = QTF_internal::indexFastqGZGivenBits(input_filenames, membit, numHashes, K, false);
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexFastqGzGivenBits(input_filenames, numHashes, K, z, membit, false);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<bool> noFindereimpleQuery = noQTF::query(normalfilter, querySeq, K);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::vector<bool> findereOnBloomFilter = QTF::query(smallFilter, querySeq, K, z, true);
        auto t3 = std::chrono::high_resolution_clock::now();

        QTF_internal::printContextBits(K, z, membit);
        std::cout << "        \"time\": {" << std::endl;
        std::cout << "            \"computeBf\": " << timeTakenMs << "," << std::endl;
        std::cout << "            \"queryBfSkip\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << "," << std::endl;
        std::cout << "            \"queryNormalFilter\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
        std::cout << "        }," << std::endl;
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, findereOnBloomFilter), "findere", false, sizeOfBloomFilter);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, noFindereimpleQuery), "normalfilter", true, numberOfIndexedElements);
        std::cout << "    }";
        if (membit != 8022598392) {
            std::cout << ",";
        }
        std::cout << std::endl;

        delete smallFilter;
        delete normalfilter;
    }
    std::cout << "]" << std::endl;

    return 0;
}
