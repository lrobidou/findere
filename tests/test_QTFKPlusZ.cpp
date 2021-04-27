#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.hpp"
#include "../src/libraries/utils/utils.hpp"

// TODO : debug that function, seems to be buggy :(
std::vector<bool> QTFToQTFKPlusZ(std::vector<bool> qtfed, unsigned int k, const unsigned long long& nbNeighboursMin) {
    std::cout << "QTFToQTFKPlusZ is bugged do not use that for your own safety" << std::endl;
    exit(-1);
    unsigned long long size = qtfed.size();
    std::vector<bool> response(size + 1 - nbNeighboursMin);
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    for (unsigned long long j = 0; j < size; j++) {
        if (qtfed[j] == 1) {
            stretchLength++;
        } else {
            if (stretchLength != 0) {
                for (unsigned long long k = 0; k < stretchLength - nbNeighboursMin; k++) {
                    response[i] = true;
                    i++;
                }
                for (unsigned long long k = 0; k < nbNeighboursMin; k++) {
                    response[i] = false;
                    i++;
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
    const unsigned long long nbNeighboursMin = 6;
    std::vector<bool> goal = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    std::vector<bool> responseQTF = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1};
    std::vector<bool> responseQTFKPlusZFromQTF = QTFToQTFKPlusZ(responseQTF, k, nbNeighboursMin);
    ASSERT_EQ(goal, responseQTFKPlusZFromQTF);
}

std::vector<bool> queryTruthBySplittingBigKmerIntoSmallKmer(robin_hood::unordered_set<std::string> thruthSmallK, unsigned int bigK, unsigned int smallK, std::string querySeq) {
    unsigned long long size = querySeq.size();
    std::vector<bool> response(size - bigK + 1);

    for (unsigned long long j = 0; j < size - bigK + 1; j++) {
        std::string thatBigKmer = querySeq.substr(j, bigK);
        bool found = true;
        for (unsigned long long k = 0; k < thatBigKmer.size() - smallK + 1; k++) {
            found &= thruthSmallK.contains(thatBigKmer.substr(k, smallK));
        }
        if (found) {
            response[j] = true;
        } else {
            response[j] = false;
        }
    }
    return response;
}