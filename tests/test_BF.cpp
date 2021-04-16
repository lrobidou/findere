#include <gtest/gtest.h>

#include <bf/all.hpp>
// #include <filesystem>
// #include <fstream>
// #include <iostream>
// #include <random>
#include <string>

#include "../src/FileIndexer.hpp"
#include "../src/truth.hpp"
#include "../src/utils.hpp"
#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports

TEST(TestBF, TestFPR) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    // create a truth and filter
    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> truthQuery = queryTruth(truth, querySeq, k);
    std::vector<bool> responseQuery = query(filter, querySeq, k);

    const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);
    double fpr = (double)(100 * FP) / (double)(FP + TN);
    double fnr = (double)(100 * FN) / (double)(FN + TP);
    // std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    ASSERT_LT(fpr, 5.1);
    ASSERT_GT(fpr, 4.9);
    ASSERT_EQ(fnr, 0);
}