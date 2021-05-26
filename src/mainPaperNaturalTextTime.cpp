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
    bool canonical = false;

    unsigned long long K = 31;
    // unsigned long long z = 3;

    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);

    std::cout << "[" << std::endl;

    std::vector<std::string> input_filenames = {"enwiki-latest-pages-articles1_head100M.txt"};
    std::string queryFile = "enwiki-latest-pages-articles1_next100M.txt";

    std::string querySeq = extractContentFromText(queryFile);

    std::cout << "[" << std::endl;
    unsigned long long k_iter = K;
    robin_hood::unordered_set<std::string> truthBigK;
    auto t0 = std::chrono::high_resolution_clock::now();
    truthBigK = truth::indexText(input_filenames, k_iter, canonical);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, k_iter);
    auto t2 = std::chrono::high_resolution_clock::now();
    double epsilonPercent_iter = 5;
    bf::basic_bloom_filter* normalfilter = nullptr;
    unsigned long long numberOfIndexedElements = 0;
    std::tie(normalfilter, numberOfIndexedElements) = QTF_internal::indexTextGivenTruth(input_filenames, truthBigK, numHashes, k_iter, epsilonPercent_iter, canonical);

    auto t6 = std::chrono::high_resolution_clock::now();
    std::vector<bool> noQTFSimpleQuery = noQTF::query(normalfilter, querySeq, k_iter);
    auto t7 = std::chrono::high_resolution_clock::now();
    for (auto z_iter : zs) {
        // z_iter = 5;
        robin_hood::unordered_set<std::string> truthSmallK;
        bf::basic_bloom_filter* smallFilter = nullptr;
        int timeTakenMs;
        unsigned long long sizeOfBloomFilter;

        QTF_internal::printContext(k_iter, z_iter, epsilonPercent_iter);

        std::tie(truthSmallK, smallFilter, timeTakenMs, sizeOfBloomFilter) = QTF::indexText(input_filenames, numHashes, k_iter, epsilonPercent_iter, z_iter, canonical);

        auto t3 = std::chrono::high_resolution_clock::now();
        std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, k_iter, z_iter);
        auto t4 = std::chrono::high_resolution_clock::now();
        std::vector<bool> QTFOnBloomFilterSkip = QTF::query(smallFilter, querySeq, k_iter, z_iter, true);
        auto t5 = std::chrono::high_resolution_clock::now();

        std::vector<bool> QTFOnSmallTruth = QTF::query(truthSmallK, querySeq, k_iter, z_iter);

        QTF_internal::printTime(t0, t1, t2, t3, t4, t5, t6, t7, timeTakenMs);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, QTFOnBloomFilter), "queryBF", false, sizeOfBloomFilter);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, QTFOnBloomFilterSkip), "queryBFSkip", false, sizeOfBloomFilter);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, QTFOnSmallTruth), "resultsOnSmallTruth", false);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, noQTFSimpleQuery), "normalfilter", true, numberOfIndexedElements);

        std::cout << "    }";
        if (z_iter < 10) {
            std::cout << ",";
        }
        std::cout << std::endl;

        delete smallFilter;
    }
    std::cout << "]" << std::endl;
    return 0;
}
