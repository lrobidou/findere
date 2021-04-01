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

std::vector<bool> QTFToQTFKPlusZ(std::vector<bool> responseQTF, const unsigned& k, const unsigned long long& nbNeighboursMin) {
    unsigned long long size = responseQTF.size() - nbNeighboursMin;
    if (size <= 0) {
        std::cerr << "responseQTF array is too small to be transformed into responseQTFPlus." << std::endl;
        exit(1);
    }
    std::vector<bool> responseQTFPlus(size);
    bool wasInAPositiveStretch = false;
    for (unsigned long long i = 0; i < size; i++) {
        if (responseQTF[i]) {
            responseQTFPlus[i] = true;
            wasInAPositiveStretch = true;
        } else {
            if (wasInAPositiveStretch) {
                wasInAPositiveStretch = false;
                for (unsigned long long j = 0; j <= nbNeighboursMin; j++) {  //TODO change if nbNeighboursMin meaning changes
                    responseQTFPlus[i - j] = false;
                }
            } else {
                responseQTFPlus[i] = false;
            }
        }
    }
    return responseQTFPlus;
}

TEST(TestQTF, TestQTFPlus) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    // create a truth and filter
    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> responseQTF = qtf(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFKPlusZ = qtfIndexKPlusZ(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFKPlusZFromQTF = QTFToQTFKPlusZ(responseQTF, k, nbNeighboursMin);
    ASSERT_EQ(responseQTFKPlusZ, responseQTFKPlusZFromQTF);
}