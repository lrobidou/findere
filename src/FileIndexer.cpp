#include "FileIndexer.hpp"

// #include <bloom_filter/basic.hpp>

#include <bf/all.hpp>
#include <cassert>
#include <fstream>
#include <string>

#include "truth.hpp"
#include "utils.hpp"

inline int countLines(const std::string& filename) {
    std::ifstream inFile(filename);
    return std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
}

void insertStringToBloomFilter(bf::bloom_filter* filter, const std::string& s, unsigned int k) {
    checknonNull(filter);
    unsigned long long size = s.size();
    for (unsigned long long i = 0; i < size - k + 1; i++) {
        filter->add(s.substr(i, k));
    }
}

bf::bloom_filter* indexFastasGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent) {
    // number of *unique* elements to add in that filter
    const unsigned long long n = truth.size();
    // size (in b**i**t) required for that filter
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by most implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);

    // TODO do not use cout but a log library (do that everywhere too)
    // std::cout << "n = " << n << std::endl;
    // std::cout << "m = " << m << std::endl;

    // now that we have the size, let's index those files
    bf::bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), m);
    for (auto const& filename : filenames) {
        // std::cout << "Indexing " << filename << "." << std::endl;
        insertStringToBloomFilter(filter, extractContentFromFasta(filename), k);
    }
    return filter;
}

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*> indexFastas(const std::vector<std::string>& filenames, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth;
    computeTruth(filenames, k, truth);
    bf::bloom_filter* filter = indexFastasGivenTruth(filenames, truth, numHashes, k, epsilon_percent);
    return {truth, filter};
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

std::tuple<int, int, int, int> getScore(const std::vector<bool>& truth, const std::vector<bool>& queryResult) {
    if (truth.size() != queryResult.size()) {
        std::cerr << "The vectors do not have the same size" << std::endl;
        std::cerr << "truth.size()" << truth.size() << std::endl;
        std::cerr << "queryResult.size()" << queryResult.size() << std::endl;
        exit(1);
    }

    unsigned long long size = truth.size();
    unsigned long long TP = 0;
    unsigned long long TN = 0;
    unsigned long long FP = 0;
    unsigned long long FN = 0;

    for (unsigned long long i = 0; i < size; i++) {
        if (truth[i] == true) {
            if (queryResult[i] == true) {
                TP++;
            } else {
                FN++;
            }
        } else {  // truth[i] == false
            if (queryResult[i] == true) {
                FP++;
            } else {
                TN++;
            }
        }
    }

    return {TP, TN, FP, FN};
}

std::tuple<int, int> count0And1InAray(std::vector<bool> array) {
    int T = 0;
    int N = 0;
    for (auto const& x : array) {
        if (x) {
            T++;
        } else {
            N++;
        }
    }
    return {T, N};
}

int computeNumberOfExpectedFP(const unsigned int& epsilon_percent, int iteration) {
    double numberOfExpectedFP = 0;
    // only compute the five first terms
    for (int i = 0; i < iteration; i++) {
        numberOfExpectedFP += i * pow(((double)epsilon_percent) / 100.0, i);
    }
    std::cout << "proba" << 95 * numberOfExpectedFP / 100 << "." << std::endl;
    return std::round(95 * numberOfExpectedFP / 100);
}

std::tuple<int, int> computeSimilarityQTF(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    std::vector<bool> qtfResponse = qtf(filter, s, k, nbNeighboursMin);
    return count0And1InAray(qtfResponse);
}

std::tuple<int, int> computeSimilarityQTFCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    unsigned long long nbStretch = 0;
    std::vector<bool> qtfResponse = qtf(filter, s, k, nbNeighboursMin, nbStretch);
    int numberOfFPExpected = nbStretch * 2 * computeNumberOfExpectedFP(epsilon_percent, 5);
    const auto& [P, N] = count0And1InAray(qtfResponse);
    int pToBeRemoved = std::min(P, numberOfFPExpected);
    return {P - pToBeRemoved, N + pToBeRemoved};
}

std::tuple<int, int> computeSimilarityQTFKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    std::vector<bool> responseQTFKPlusZ = qtfIndexKPlusZ(filter, s, k, nbNeighboursMin);
    return count0And1InAray(responseQTFKPlusZ);
}

std::tuple<int, int> computeSimilarityQTFKPlusZCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    unsigned long long nbStretch = 0;
    std::vector<bool> responseQTFKPlusZ = qtfIndexKPlusZ(filter, s, k, nbNeighboursMin, nbStretch);
    int numberOfFPExpected = nbStretch * 2 * computeNumberOfExpectedFP(epsilon_percent, 5);
    const auto& [P, N] = count0And1InAray(responseQTFKPlusZ);
    int pToBeRemoved = std::min(P, numberOfFPExpected);
    return {P - pToBeRemoved, N + pToBeRemoved};
}
