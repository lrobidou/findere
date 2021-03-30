#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "../src/FileIndexer.hpp"
#include "../src/utils.hpp"
#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports

template <typename T>
void toFileTXT(std::string outfilename, T x) {
    if (remove(outfilename.c_str()) != 0) {
        perror("Error deleting file");
    } else {
        puts("File successfully deleted");
    }

    std::ofstream outFile(outfilename);
    for (const auto& e : x) {
        outFile << e;
    }
}

TEST(TestSuiteName, TestName) {
    robin_hood::unordered_set<std::string> truth;
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};
    BloomFilter* bf = indexFastas(input_filenames, k, epsilon_percent);
    // ASSERT_NE(bf, nullptr);

    computeTruth(input_filenames, k, truth);
    computeTruth(input_filenames, k + nbNeighboursMin, truthPlusK);
    std::vector<bool> truthQuery = queryTruth(truth, seq, k);
    std::vector<bool> truthPlusKQuery = queryTruth(truthPlusK, seq, k + nbNeighboursMin);
    std::vector<bool> responseQuery = query(bf, seq, numHashes, k);
    std::vector<bool> responseQTF = qtf(bf, seq, numHashes, k, nbNeighboursMin);
    std::vector<bool> responseQTFPlus = qtfIndexKPlusZ(bf, seq, numHashes, k, nbNeighboursMin);

    const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);

    std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;

    toFileTXT("responseQTF.txt", responseQTF);
    toFileTXT("responseQTFPlus.txt", responseQTFPlus);
    toFileTXT("responseQuery.txt", responseQuery);
    toFileTXT("truth.txt", truthQuery);
    toFileTXT("truthPlusK.txt", truthPlusKQuery);
}