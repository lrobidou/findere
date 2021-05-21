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
    std::vector<unsigned long long> membits = {100, 81036446, 162072792, 243109139, 324145485, 405181831, 486218178, 567254524, 648290870, 729327217, 810363563, 891399910, 1053472602, 1323593756, 1593714911, 1863836066, 2133957220, 2404078375, 2674199530, 2998344916, 5591508000, 6644980503, 35619976713, 64594972924, 93569969135, 122544965346, 151519961556, 180494957767, 209469953978, 238444950189, 267419946400};

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

        std::vector<bool> noFindereimpleQuery = noQTF::query(normalfilter, querySeq, K);
        std::vector<bool> findereOnBloomFilter = QTF::query(smallFilter, querySeq, K, z, true);

        QTF_internal::printContextBits(K, z, membit);
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
