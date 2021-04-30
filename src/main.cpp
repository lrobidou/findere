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

void read_fastq(std::string filename) {
    std::ifstream myfile(filename);
    zstr::istream is(myfile);
    std::string s;
    while (getline(is, s)) {
        std::cout << s << std::endl;
    }
}

void printContext(const unsigned long long& k, const unsigned long long& z, const double& epsilon) {
    std::cout << "    {" << std::endl;
    std::cout << "        \"param\": {" << std::endl;
    std::cout << "            \"k\" : " << k << "," << std::endl;
    std::cout << "            \"z\" : " << z << "," << std::endl;
    std::cout << "            \"epsilon\" : " << epsilon << std::endl;
    std::cout << "        }," << std::endl;
}

void printTime(std::chrono::_V2::system_clock::time_point t0,
               std::chrono::_V2::system_clock::time_point t1,
               std::chrono::_V2::system_clock::time_point t2,
               std::chrono::_V2::system_clock::time_point t3,
               std::chrono::_V2::system_clock::time_point t4,
               int taimeTakenByIndexingBf) {
    std::cout << "        \"time\": {" << std::endl;
    std::cout << "            \"computeTruth\":" << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "," << std::endl;
    std::cout << "            \"computeBf\":" << taimeTakenByIndexingBf << "," << std::endl;
    std::cout << "            \"queryTruth\":" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "," << std::endl;
    std::cout << "            \"queryBf\":" << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << std::endl;
    std::cout << "        }," << std::endl;
}

int main(int argc, char* argv[]) {
    // read_fastq("data/ecoli1.fasta");
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
            for (double epsilonPercent_iter = 0.5; epsilonPercent_iter <= epsilonPercent; epsilonPercent_iter += 0.5) {
                printContext(k_iter, z_iter, epsilonPercent_iter);
                const auto& [truthSmallK, smallFilter, timeTakenMs] = QTF::indexFastas(input_filenames, numHashes, k_iter, epsilonPercent_iter, z_iter);
                auto t3 = std::chrono::high_resolution_clock::now();
                std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, k_iter, z_iter);
                auto t4 = std::chrono::high_resolution_clock::now();

                printTime(t0, t1, t2, t3, t4, timeTakenMs);
                printScore(getScore(bigTruth, QTFOnBloomFilter));
                std::cout << "    }," << std::endl;
                delete smallFilter;
                // 38m 39s

                // TP: 98412, TN :4757970, FP :1123, FN :0
                // FPR: 0.0235969%.
                // FNR: 0%.
            }
        }
    }
    std::cout << "]" << std::endl;
}