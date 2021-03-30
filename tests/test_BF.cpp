#include <gtest/gtest.h>

#include <filesystem>
#include <string>

// #include "../src/FileIndexer.hpp"
#include "../src/utils.hpp"
#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports

TEST(TestBF, _FPR) {
    // robin_hood::unordered_set<std::string> truthPlusK;
    // const unsigned k = 32;         // k-mer size
    // const unsigned numHashes = 1;  // number of hash functions
    // const int epsilon_percent = 5;

    // std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};

    // // create ground truth
    // robin_hood::unordered_set<std::string> truth;
    // computeTruth(input_filenames, k, truth);
    // // query it
    // std::vector<bool> truthQuery = queryTruth(truth, seq, k);

    // // create a BF
    // BloomFilter* bf = indexFastas(input_filenames, k, epsilon_percent);
    // // query it
    // std::vector<bool> responseQuery = query(bf, seq, numHashes, k);
    // responseQuery = query(bf, seq, numHashes, k);
    // responseQuery = query(bf, seq, numHashes, k);
    // responseQuery = query(bf, seq, numHashes, k);

    // const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);

    // std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    // std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    // std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;
}