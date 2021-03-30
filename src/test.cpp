// #include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "seq.hpp"
// #include "../src/utils.hpp"
#include <bf/all.hpp>
#include <fstream>
#include <iostream>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports
#include "FileIndexer.hpp"
#include "truth.hpp"

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

int main() {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};

    // // create ground truth
    robin_hood::unordered_set<std::string> truth;
    computeTruth(input_filenames, k, truth);
    robin_hood::unordered_set<std::string> truthKPlusZ;
    computeTruth(input_filenames, k + nbNeighboursMin, truthKPlusZ);
    // // query it
    std::vector<bool> truthQuery = queryTruth(truth, seq, k);
    std::vector<bool> truthQueryKPlusZ = queryTruth(truthKPlusZ, seq, k + nbNeighboursMin);

    // create a BF
    bf::bloom_filter* filter = indexFastas(input_filenames, numHashes, k, epsilon_percent);
    // // query it
    std::vector<bool> responseQuery = query(filter, seq, k);
    std::vector<bool> responseQTF = qtf(filter, seq, k, nbNeighboursMin);
    std::vector<bool> responseQTFSkip = qtfSkip(filter, seq, k, nbNeighboursMin);
    std::vector<bool> responseQTFPlus = qtfIndexKPlusZ(filter, seq, k, nbNeighboursMin);
    getScore(truthQuery, responseQuery);
    // const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);
    getScore(truthQuery, responseQTF);
    // getScore(truthQuery, responseQTFPlus);//TODO FPR supr bas, pourquoi ?
    getScore(truthQueryKPlusZ, responseQTFPlus);

    toFileTXT("responseQTF.txt", responseQTF);
    toFileTXT("responseQTFSkip.txt", responseQTFSkip);
    toFileTXT("responseQTFPlus.txt", responseQTFPlus);
    toFileTXT("responseQuery.txt", responseQuery);
    toFileTXT("truth.txt", truthQuery);
    toFileTXT("truthPlusK.txt", truthQueryKPlusZ);
    return 0;
}