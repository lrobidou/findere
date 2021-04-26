#include "QTFNoSplitKmer.hpp"

#include <bf/all.hpp>
#include <cassert>
#include <vector>

#include "../utils/utils.hpp"

std::vector<bool> QTFNoSplitKmer::queryNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    checknonNull(filter, "Nullptr passed to qtfNoSkip function.");
    unsigned long long size = s.size();

    std::vector<bool> response(size - k + 1);
    unsigned long long nbQuery = 0;  //TODO remove
    unsigned long long i = 0;

    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    long nb_strechs = 0;

    for (unsigned long long j = 0; j < size - k + 1; j++) {
        if (filter->lookup(s.substr(j, k))) {
            stretchLength++;
            nbQuery++;
        } else {
            if (stretchLength != 0) {
                bool responseToAdd = false;
                if (stretchLength > nbNeighboursMin) {
                    responseToAdd = true;
                    nb_strechs++;
                }
                for (unsigned long long k = 0; k < stretchLength; k++) {
                    response[i] = responseToAdd;
                    i++;
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;
        }
    }
    for (unsigned long long j = 0; j < stretchLength; j++) {
        response[i] = stretchLength > nbNeighboursMin ? true : false;  //TODO do that everywhere
        i++;
    }
    std::cout << "number of query " << i << " nb stretchs " << nb_strechs << std::endl;
    assert(i == size - k + 1);
    return response;
}
std::vector<bool> QTFNoSplitKmer::queryNoSkip(robin_hood::unordered_set<std::string> hashSet, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    unsigned long long size = s.size();

    std::vector<bool> response(size - k + 1);
    unsigned long long nbQuery = 0;  //TODO remove
    unsigned long long i = 0;

    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    long nb_strechs = 0;

    for (unsigned long long j = 0; j < size - k + 1; j++) {
        if (hashSet.contains(s.substr(j, k))) {
            stretchLength++;
            nbQuery++;
        } else {
            if (stretchLength != 0) {
                bool responseToAdd = false;
                if (stretchLength > nbNeighboursMin) {
                    responseToAdd = true;
                    nb_strechs++;
                }
                for (unsigned long long k = 0; k < stretchLength; k++) {
                    response[i] = responseToAdd;
                    i++;
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;
        }
    }
    for (unsigned long long j = 0; j < stretchLength; j++) {
        response[i] = stretchLength > nbNeighboursMin ? true : false;  //TODO do that everywhere
        i++;
    }
    std::cout << "number of query " << i << " nb stretchs " << nb_strechs << std::endl;
    assert(i == size - k + 1);
    return response;
}

std::vector<bool> QTFNoSplitKmer::query(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch) {
    checknonNull(filter, "Nullptr passed to qtf function.");
    unsigned long long size = s.size();

    std::vector<bool> response(size - k + 1);
    unsigned long long nbQuery = 0;        //TODO remove
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector
    while (j < size - k + 1) {
        if (filter->lookup(s.substr(j, k))) {
            stretchLength++;
            nbQuery++;
            j++;
        } else {
            if (stretchLength != 0) {
                bool responseToAdd = false;
                if (stretchLength > nbNeighboursMin) {
                    responseToAdd = true;
                    nbStretch++;
                }
                for (unsigned long long k = 0; k < stretchLength; k++) {
                    response[i] = responseToAdd;
                    i++;
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;
            // skip queries between current position and the next positive kmer
            unsigned long long nextPositivePosition = getNextPositiveKmerPositionInTheQuery(filter, s, k, nbNeighboursMin, j, nbQuery);
            // let's fill nextPositivePosition-i-1 negative resuls
            while (i < nextPositivePosition) {
                response[i] = 0;
                i++;
            }
            j = i;
        }
    }
    if (stretchLength > nbNeighboursMin) {
        nbStretch++;
    }

    // let's not forget the last stretch if it exists
    for (unsigned long long j = 0; j < stretchLength; j++) {
        response[i] = stretchLength > nbNeighboursMin ? true : false;  //TODO do that everywhere
        i++;
    }
    // TODO remove those cout
    std::cout << "number of query expected: " << i << std::endl;
    std::cout << "number of query actaullly made: " << nbQuery << std::endl;
    std::cout << "( " << (((double)(i - nbQuery)) / (double)i) * 100 << " %less)" << std::endl;
    return response;
}

std::vector<bool> QTFNoSplitKmer::query(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    unsigned long long dontCare = 0;
    return QTFNoSplitKmer::query(filter, s, k, nbNeighboursMin, dontCare);
}