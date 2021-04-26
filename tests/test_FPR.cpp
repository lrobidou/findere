#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <iostream>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.hpp"
#include "../src/libraries/truth/truth.hpp"
#include "../src/libraries/utils/utils.hpp"
#include "testutils.hpp"
TEST(TestSuiteName, TestName2) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};

    std::string querySeq = extractContentFromFasta("data/ecoli4.fasta");

    const auto &[truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);
    robin_hood::unordered_set<std::string> truthKPlusZ = computeTruth(input_filenames, k + nbNeighboursMin);

    // query truth
    std::vector<bool> truthQuery = queryTruth(truth, querySeq, k);
    std::vector<bool> truthQueryKPlusZ = queryTruth(truthKPlusZ, querySeq, k + nbNeighboursMin);

    // query BF
    std::vector<bool> responseQuery = noQTF::query(filter, querySeq, k);
    std::vector<bool> responseQTFNoSkip = QTFNoSplitKmer::queryNoSkip(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTF = QTFNoSplitKmer::query(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFPlus = QTF::query(filter, querySeq, k, nbNeighboursMin);
    std::cout << std::endl
              << std::endl;
    /* *****SCORE***** */
    std::cout << "getScore(truthQuery, responseQuery)" << std::endl;
    printScore(getScore(truthQuery, responseQuery));
    std::cout << std::endl;

    // const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);
    std::cout << "getScore(truthQuery, responseQTFNoSkip);" << std::endl;
    printScore(getScore(truthQuery, responseQTFNoSkip));
    std::cout << std::endl;

    std::cout << "getScore(truthQuery, responseQTF);" << std::endl;
    printScore(getScore(truthQuery, responseQTF));
    std::cout << std::endl;

    // getScore(truthQuery, responseQTFPlus);//TODO FPR supr bas, pourquoi ?
    std::cout << "getScore(truthQueryKPlusZ, responseQTFPlus)" << std::endl;
    printScore(getScore(truthQueryKPlusZ, responseQTFPlus));
    std::cout << std::endl;
}