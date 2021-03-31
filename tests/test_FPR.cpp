// #include <BloomFilterUtil.h>
#include <gtest/gtest.h>

#include <bf/all.hpp>

#include "testutils.hpp"
// #include <filesystem>
// #include <nlohmann/json.hpp>
// #include <string>

#include "../src/FileIndexer.hpp"
#include "../src/truth.hpp"
#include "../src/utils.hpp"
#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports

// template <typename T>
// void toFileTXT(std::string outfilename, T x) {
//     if (remove(outfilename.c_str()) != 0) {
//         perror("Error deleting file");
//     } else {
//         puts("File successfully deleted");
//     }

//     std::ofstream outFile(outfilename);
//     for (const auto& e : x) {
//         outFile << e;
//     }
// }

// #include "vendor/ntHashIterator.hpp"

TEST(TestSuiteName, TestName2) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};

    std::string querySeq = extractMeaningfullLineFromFasta("data/ecoli4.fasta");

    /* *****TRUTH***** */
    // // create ground truth
    robin_hood::unordered_set<std::string> truth;
    computeTruth(input_filenames, k, truth);
    robin_hood::unordered_set<std::string> truthKPlusZ;
    computeTruth(input_filenames, k + nbNeighboursMin, truthKPlusZ);
    // // query it
    std::vector<bool> truthQuery = queryTruth(truth, querySeq, k);
    std::vector<bool> truthQueryKPlusZ = queryTruth(truthKPlusZ, querySeq, k + nbNeighboursMin);

    /* *****BLOOM_FILTERS***** */
    // create a BF
    bf::bloom_filter* filter = indexFastas(input_filenames, numHashes, k, epsilon_percent);
    // // query it
    std::vector<bool> responseQuery = query(filter, querySeq, k);
    std::vector<bool> responseQTF = qtf(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFSkip = qtfSkip(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFPlus = qtfIndexKPlusZ(filter, querySeq, k, nbNeighboursMin);
    std::cout << std::endl
              << std::endl;
    /* *****SCORE***** */
    std::cout << "getScore(truthQuery, responseQuery)" << std::endl;
    getScore(truthQuery, responseQuery);
    std::cout << std::endl;

    // const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);
    std::cout << "getScore(truthQuery, responseQTF);" << std::endl;
    getScore(truthQuery, responseQTF);
    std::cout << std::endl;

    std::cout << "getScore(truthQuery, responseQTFSkip);" << std::endl;
    getScore(truthQuery, responseQTFSkip);
    std::cout << std::endl;

    // getScore(truthQuery, responseQTFPlus);//TODO FPR supr bas, pourquoi ?
    std::cout << "getScore(truthQueryKPlusZ, responseQTFPlus)" << std::endl;
    getScore(truthQueryKPlusZ, responseQTFPlus);
    std::cout << std::endl;
}