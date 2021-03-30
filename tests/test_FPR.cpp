// #include <BloomFilterUtil.h>
#include <gtest/gtest.h>

#include "testutils.hpp"
// #include <filesystem>
// #include <nlohmann/json.hpp>
// #include <string>

#include "../src/FileIndexer.hpp"
// #include "../src/utils.hpp"
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

#include "vendor/ntHashIterator.hpp"

TEST(TestSuiteName, TestName2) {
    robin_hood::unordered_set<std::string> truth;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    // const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta"};
    BloomFilter* bf = indexFastas(input_filenames, k, epsilon_percent);
    std::string ecoli3_4 = extractMeaningfullLineFromFasta("data/ecoli3.fasta") + extractMeaningfullLineFromFasta("data/ecoli4.fasta");
    computeTruth(input_filenames, k, truth);
    std::vector<bool> truthQuery = queryTruth(truth, ecoli3_4, k);
    std::vector<bool> responseQuery = query(bf, ecoli3_4, numHashes, k);

    // unsigned long long n = randomSeq.length();
    // unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // m = m + 8 - (m % 8);

    // BloomFilter* bloom = new BloomFilter(m, 1, k);
    // ntHashIterator itr(randomSeq, numHashes, k);
    // int i = 0;
    // while (itr != itr.end()) {
    //     (*bloom).insert(*itr);
    //     i++;
    //     ++itr;
    // }
    const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);

    std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;

    // toFileTXT("responseQTF.txt", responseQTF);
    // toFileTXT("responseQTFPlus.txt", responseQTFPlus);
    // toFileTXT("responseQuery.txt", responseQuery);
    // toFileTXT("truth.txt", truthQuery);
    // toFileTXT("truthPlusK.txt", truthPlusKQuery);
}