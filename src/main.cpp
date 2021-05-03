#include <robin_hood.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>
#include <zstr.hpp>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"

int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);
    const auto& [input_filenames, queryFile, k, z, epsilonPercent] = getArgs(arguments);

    std::string querySeq = extractContentFromFasta(queryFile);

    std::cout << "[" << std::endl;
    for (unsigned long long k_iter = k; k_iter > z; k_iter -= 1) {
        auto t0 = std::chrono::high_resolution_clock::now();
        robin_hood::unordered_set<std::string> truthBigK = truth::indexFastas(input_filenames, k_iter);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, k_iter);
        auto t2 = std::chrono::high_resolution_clock::now();

        for (unsigned long long z_iter = 0; z_iter < z; z_iter++) {
            // robin_hood::unordered_set<std::string> truthSmallK = truth::indexFastas(input_filenames, k_iter - z);
            for (double epsilonPercent_iter = 0.5; epsilonPercent_iter <= epsilonPercent; epsilonPercent_iter += 0.5) {
                QTF_internal::printContext(k_iter, z_iter, epsilonPercent_iter);
                const auto& [truthSmallK, smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexFastqGz(input_filenames, numHashes, k_iter, epsilonPercent_iter, z_iter);
                auto t3 = std::chrono::high_resolution_clock::now();
                std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, k_iter, z_iter);
                auto t4 = std::chrono::high_resolution_clock::now();
                std::vector<bool> QTFOnSmallTruth = QTF::query(truthSmallK, querySeq, k_iter, z_iter);

                QTF_internal::printTime(t0, t1, t2, t3, t4, timeTakenMs);
                QTF_internal::printScore(QTF_internal::getScore(bigTruth, QTFOnBloomFilter), sizeOfBloomFilter);
                std::cout << "," << std::endl;
                QTF_internal::printScore(QTF_internal::getScore(bigTruth, QTFOnSmallTruth), "resultsOnSmallFilter");

                std::cout << "    }," << std::endl;
                delete smallFilter;
            }
        }
    }
    std::cout << "]" << std::endl;
}