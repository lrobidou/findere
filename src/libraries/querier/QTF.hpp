#pragma once
#include <robin_hood.h>

#include <bf/all.hpp>
#include <vector>

#include "../utils/customAMQ.hpp"
#include "../utils/utils.hpp"

template <typename T>
inline std::vector<bool> queryFilterOrTruth(const T& filterOrTruth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
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

            // skip queries between current position and the next positive kmer
            if (skip && (nbNeighboursMin > 0)) {
                unsigned long long dontCare = 0;
                unsigned long long numberOfJumps = getNextPositiveKmerPositionInTheQuery(filterOrTruth, s, smallK, nbNeighboursMin, j, dontCare);
                // std::cout << "numberOfJumps = " << numberOfJumps << std::endl;
                for (unsigned long long temp = 0; temp < nbNeighboursMin * numberOfJumps; temp++) {
                    response[i] = false;
                    i++;
                    j++;
                }
            }

            response[i] = 0;
            i++;
            j++;
        }
    }
    if (stretchLength != 0) {
        if (stretchLength > nbNeighboursMin) {
            nbStretch++;
            for (unsigned long long k = 0; k < stretchLength; k++) {
                response[i] = true;
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

namespace findere {

std::vector<bool> inline query(bf::basic_bloom_filter* filter, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    return queryFilterOrTruth(filter, s, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query(const robin_hood::unordered_set<std::string>& truth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    return queryFilterOrTruth(truth, s, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query(bf::basic_bloom_filter* filter, const std::string& s, const unsigned int& k, const unsigned long long& nbNeighboursMin, bool skip = false) {
    unsigned long long dontCare = 0;
    return queryFilterOrTruth(filter, s, k, nbNeighboursMin, dontCare, skip);
}

std::vector<bool> inline query(const robin_hood::unordered_set<std::string>& truth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, bool skip = false) {
    unsigned long long dontCare = 0;
    return queryFilterOrTruth(truth, s, k, nbNeighboursMin, dontCare, skip);
}

std::vector<bool> inline query(const customAMQ& amq, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    return queryFilterOrTruth(amq, s, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query(const customAMQ& amq, const std::string& s, const unsigned int& k, const unsigned long long& nbNeighboursMin, bool skip = false) {
    unsigned long long dontCare = 0;
    return queryFilterOrTruth(amq, s, k, nbNeighboursMin, dontCare, skip);
}

}  // namespace findere
