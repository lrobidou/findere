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
//TODO canonical for fastas too
int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);
    const auto& [input_filenames, queryFile, k, z, epsilonPercent, canonical, typeInput, bits] = getArgs(arguments);
    std::string querySeq;
    if (typeInput == "fastq") {
        querySeq = extractContentFromFastqGz(queryFile);
    } else if (typeInput == "fasta") {
        querySeq = extractContentFromFasta(queryFile);
    } else if (typeInput == "text") {
        querySeq = extractContentFromText(queryFile);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
        exit(1);
    }
    std::cout << "[" << std::endl;
    for (unsigned long long k_iter = k; k_iter > 13; k_iter -= 2) {
        robin_hood::unordered_set<std::string> truthBigK;
        auto t0 = std::chrono::high_resolution_clock::now();

        if (typeInput == "fastq") {
            querySeq = extractContentFromFastqGz(queryFile);
        } else if (typeInput == "fasta") {
            truthBigK = truth::indexFastqGz(input_filenames, k_iter, canonical);
        } else if (typeInput == "text") {
            querySeq = extractContentFromText(queryFile);
        } else {
            std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
            exit(1);
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, k_iter);
        auto t2 = std::chrono::high_resolution_clock::now();
        for (double epsilonPercent_iter = 0.5; epsilonPercent_iter <= epsilonPercent; epsilonPercent_iter += 0.5) {
            epsilonPercent_iter = 5;
            bf::basic_bloom_filter* normalfilter = nullptr;
            unsigned long long numberOfIndexedElements = 0;
            if (bits) {
                std::tie(normalfilter, numberOfIndexedElements) = QTF_internal::indexFastqGZGivenBits(input_filenames, bits, numHashes, k_iter, epsilonPercent_iter, canonical);
            } else {
                std::tie(normalfilter, numberOfIndexedElements) = QTF_internal::indexFastqGZGivenTruth(input_filenames, truthBigK, numHashes, k_iter, epsilonPercent_iter, canonical);
            }

            auto t6 = std::chrono::high_resolution_clock::now();
            std::vector<bool> noQTFSimpleQuery = noQTF::query(normalfilter, querySeq, k_iter);
            auto t7 = std::chrono::high_resolution_clock::now();
            for (unsigned long long z_iter = 0; z_iter < z; z_iter++) {
                // z_iter = 5;
                robin_hood::unordered_set<std::string> truthSmallK;
                bf::basic_bloom_filter* smallFilter = nullptr;
                int timeTakenMs;
                unsigned long long sizeOfBloomFilter;

                QTF_internal::printContext(k_iter, z_iter, epsilonPercent_iter);

                if (bits) {
                    truthSmallK = truth::indexFastqGz(input_filenames, k_iter - z_iter, canonical);
                    std::tie(smallFilter, timeTakenMs, sizeOfBloomFilter) = QTF::indexFastqGz(input_filenames, numHashes, k_iter, epsilonPercent_iter, z_iter, bits, canonical);
                } else {
                    std::tie(truthSmallK, smallFilter, timeTakenMs, sizeOfBloomFilter) = QTF::indexFastqGz(input_filenames, numHashes, k_iter, epsilonPercent_iter, z_iter, canonical);
                }

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

                std::cout << "    }," << std::endl;
                delete smallFilter;

                // std::cout << "]" << std::endl;
                //toFileTXT("qtfonbf.txt", QTFOnBloomFilter);
                //toFileTXT("truth.txt", bigTruth);
                //toFileTXT("qtfOnTruth.txt", QTFOnSmallTruth);
            }
            return 0;
        }
    }
    std::cout << "]" << std::endl;
}
