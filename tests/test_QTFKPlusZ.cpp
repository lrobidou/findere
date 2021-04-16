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

std::vector<bool> QTFToQTFKPlusZ(std::vector<bool> qtfed, unsigned int k, const unsigned long long& nbNeighboursMin) {
    unsigned long long size = qtfed.size();
    std::vector<bool> response(size + 1 - nbNeighboursMin);
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    for (unsigned long long j = 0; j < size; j++) {
        if (qtfed[j] == 1) {
            stretchLength++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    // nbStretch++;
                    for (unsigned long long k = 0; k < stretchLength - nbNeighboursMin; k++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long k = 0; k < nbNeighboursMin; k++) {
                        response[i] = false;
                        i++;
                    }
                } else {
                    for (unsigned long long k = 0; k < stretchLength; k++) {
                        response[i] = false;
                        i++;
                    }
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;
        }
    }

    if (stretchLength != 0) {
        std::cout << "still" << stretchLength << "found" << std::endl;
        if (stretchLength > nbNeighboursMin) {
            for (unsigned long long k = 0; k < stretchLength - nbNeighboursMin; k++) {
                response[i] = true;
                i++;
                std::cout << "un 1 ajoute, i=" << i << std::endl;
            }

            for (unsigned long long j = 0; j < nbNeighboursMin; j++) {
                response[i] = false;
                i++;
                std::cout << "i=" << i << std::endl;
            }
        } else {
            for (unsigned long long k = 0; k < stretchLength; k++) {
                response[i] = false;
                i++;
            }
        }
        stretchLength = 0;
    }
    return response;
}

TEST(TestQTF, TestQTFPlus) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;  // k-mer size
    // const unsigned numHashes = 1;  // number of hash functions
    // const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    // std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    // std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    // // create a truth and filter
    // const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> goal = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    std::vector<bool> responseQTF = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1};
    std::vector<bool> responseQTFKPlusZFromQTF = QTFToQTFKPlusZ(responseQTF, k, nbNeighboursMin);
    ASSERT_EQ(goal, responseQTFKPlusZFromQTF);
}