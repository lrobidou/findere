#pragma once
#include <robin_hood.h>

#include <bf/all.hpp>
#include <vector>

#include "../utils/utils.hpp"

template <typename T>
inline std::vector<bool> queryFilterOrTruth(T filterOrTruth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch) {
    const unsigned int smallK = k - nbNeighboursMin;
    unsigned long long size = s.size();
    std::vector<bool> response(size - smallK + 1 - nbNeighboursMin);
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector

    while (j < size - k + 1) {
        std::cout << "start loop j = " << j << "; i = " << i << std ::endl;

        if (oneQuery(filterOrTruth, s.substr(j, smallK))) {
            std::cout << "start if j = " << j << "; i = " << i << std ::endl;
            stretchLength++;
            j++;
            std::cout << "end if j = " << j << "; i = " << i << std ::endl;
        } else {
            std::cout << "start else j = " << j << "; i = " << i << std ::endl;
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    nbStretch++;
                    for (unsigned long long t = 0; t < stretchLength - nbNeighboursMin; t++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long t = 0; t < nbNeighboursMin; t++) {
                        response[i] = false;
                        i++;
                    }
                } else {
                    for (unsigned long long t = 0; t < stretchLength; t++) {
                        response[i] = false;
                        i++;
                    }
                }
                stretchLength = 0;
            }
            std::cout << "after emptied stretchlength j = " << j << "; i = " << i << std ::endl;

            // skip queries between current position and the next positive kmer
            unsigned long long dontCare = 0;
            unsigned long long numberOfJumps = getNextPositiveKmerPositionInTheQuery(filterOrTruth, s, smallK, nbNeighboursMin, j, dontCare);
            std::cout << "numberOfJumps = " << numberOfJumps << std::endl;
            for (unsigned long long temp = 0; temp < nbNeighboursMin * numberOfJumps; temp++) {
                response[i] = false;
                i++;
                j++;
            }
            std::cout << "after skip j = " << j << "; i = " << i << std ::endl;
            response[i] = 0;
            i++;
            j++;
            // while (i < nextPositivePosition) {
            //     std::cout << "incrementingiand j" << std::endl;
            //     response[i] = 0;
            //     i++;
            //     j++;
            // }
            std::cout << "end else j = " << j << "; i = " << i << std ::endl;
        }
        std::cout << "end loop j = " << j << "; i = " << i << std ::endl;
    }

    if (stretchLength != 0) {
        if (stretchLength > nbNeighboursMin) {
            nbStretch++;
            for (unsigned long long k = 0; k < stretchLength - nbNeighboursMin; k++) {
                response[i] = true;
                i++;
            }
            for (unsigned long long j = 0; j < nbNeighboursMin; j++) {
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
    return response;
}

namespace QTF {

std::vector<bool> inline query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch) {
    return queryFilterOrTruth(filter, s, k, nbNeighboursMin, nbStretch);
}

std::vector<bool> inline query(const robin_hood::unordered_set<std::string>& truth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch) {
    return queryFilterOrTruth(truth, s, k, nbNeighboursMin, nbStretch);
}

std::vector<bool> inline query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k, const unsigned long long& nbNeighboursMin) {
    unsigned long long dontCare = 0;
    return queryFilterOrTruth(filter, s, k, nbNeighboursMin, dontCare);
}

std::vector<bool> inline query(const robin_hood::unordered_set<std::string>& truth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin) {
    unsigned long long dontCare = 0;
    return queryFilterOrTruth(truth, s, k, nbNeighboursMin, dontCare);
}

}  // namespace QTF
