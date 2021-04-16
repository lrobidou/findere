#include "querier.hpp"

#include <bf/all.hpp>
#include <cassert>

#include "utils.hpp"
unsigned long long getNextPositiveKmerPositionInTheQuery(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long j, unsigned long long& nbQuery) {
    unsigned long long size = s.size();
    while ((j + nbNeighboursMin < size - k + 1) && (!filter->lookup(s.substr(j + nbNeighboursMin, k)))) {
        j += nbNeighboursMin;  //TODO si on veut *>=* nbnbNeighboursMin, enlever 1
        nbQuery++;
    }
    unsigned long long i = 1;
    //TODO eviter dernier query
    while ((j + i < size - k + 1) && (!filter->lookup(s.substr(j + i, k)))) {
        i++;
        nbQuery++;
    }
    j += i;
    return j;
}

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k) {
    checknonNull(filter, "Nullptr passed to query function.");
    unsigned long long size = s.size();
    unsigned long long nbQuery = 0;  //TODO remove
    std::vector<bool> response(size - k + 1);

    for (unsigned long long i = 0; i < size - k + 1; i++) {
        response[i] = filter->lookup(s.substr(i, k));
        nbQuery++;
    }

    // std::cout << "query " << nbQuery << std::endl;
    // std::cout << std::endl;
    return response;
}

std::vector<bool> qtfNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
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

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch) {
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

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    unsigned long long dontCare = 0;
    return qtf(filter, s, k, nbNeighboursMin, dontCare);
}

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch) {
    unsigned long long size = s.size();
    std::vector<bool> response(size - k + 1 - nbNeighboursMin);
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    for (unsigned long long j = 0; j < size - k + 1; j++) {
        if (filter->lookup(s.substr(j, k))) {
            stretchLength++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    nbStretch++;
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

    // std::cout << "number of query / size of qtfplus response " << i << std::endl;
    return response;
}

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    unsigned long long dontCare = 0;
    return qtfIndexKPlusZ(filter, s, k, nbNeighboursMin, dontCare);
}