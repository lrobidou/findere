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
        if (oneQuery(filterOrTruth, s.substr(j, smallK))) {
            stretchLength++;
            j++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    nbStretch++;
                    for (unsigned long long j = 0; j < stretchLength - nbNeighboursMin; j++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long j = 0; j < nbNeighboursMin; j++) {
                        response[i] = false;
                        i++;
                    }
                } else {
                    for (unsigned long long j = 0; j < stretchLength; j++) {
                        response[i] = false;
                        i++;
                    }
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;

            // skip queries between current position and the next positive kmer
            unsigned long long dontCare = 0;
            unsigned long long nextPositivePosition = getNextPositiveKmerPositionInTheQuery(filterOrTruth, s, k, nbNeighboursMin, j, dontCare);
            // let's fill nextPositivePosition-i-1 negative resuls
            while (i < nextPositivePosition) {
                response[i] = 0;
                i++;
            }
            j = i;
        }
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
