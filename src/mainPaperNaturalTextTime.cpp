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
    std::vector<unsigned long long> zs = {0, 1, 2, 3, 4, 5, 10};

    unsigned long long K = 31;
    // unsigned long long z = 3;

    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);

    std::cout << "[" << std::endl;

    std::vector<std::string> input_filenames = {"enwiki-latest-pages-articles1_head100M.txt"};
    std::string queryFile = "enwiki-latest-pages-articles1_next100M.txt";

    std::string querySeq = extractContentFromText(queryFile);

    robin_hood::unordered_set<std::string> truthBigK = truth::indexText(input_filenames, K, false);
    std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, K);
    double epsilonPercent = 5.0;

    const auto& [normalfilter, sizeSimpleFilter] = QTF_internal::indexTextGivenTruth(input_filenames, truthBigK, numHashes, K, epsilonPercent, false);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<bool> noFindereimpleQuery = noQTF::query(normalfilter, querySeq, K);
    auto t2 = std::chrono::high_resolution_clock::now();

    for (const auto& z : zs) {
        const auto& [truthSmallK, smallFilter, timeTakenMs, sizeOfBloomFilterFindere] = QTF::indexText(input_filenames, numHashes, K, epsilonPercent, z, false);

        auto t3 = std::chrono::high_resolution_clock::now();
        std::vector<bool> findereOnBloomFilter = QTF::query(smallFilter, querySeq, K, z, true);
        auto t4 = std::chrono::high_resolution_clock::now();

        QTF_internal::printContext(K, z, epsilonPercent);
        std::cout << "        \"time\": {" << std::endl;
        std::cout << "            \"computeBf\": " << timeTakenMs << "," << std::endl;
        std::cout << "            \"queryBfSkip\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "," << std::endl;
        std::cout << "            \"queryNormalFilter\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
        std::cout << "        }," << std::endl;
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, findereOnBloomFilter), "findere", false, sizeOfBloomFilterFindere);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, noFindereimpleQuery), "normalfilter", true, sizeSimpleFilter);
        std::cout << "}";
        if (z != 10) {
            std::cout << ",";
        }
        std::cout << std::endl;

        delete smallFilter;
        delete normalfilter;
    }

    std::cout << "]" << std::endl;

    return 0;
}
