#include "FileIndexer.hpp"

// #include <bloom_filter/basic.hpp>

#include <bf/all.hpp>
#include <fstream>
#include <string>

#include "utils.hpp"
inline int countLines(const std::string& filename) {
    std::ifstream inFile(filename);
    return std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
}

// BloomFilter* index(const std::string& filename, const unsigned int& k, const int& epsilon_percent) {  // TODO type k ?
//     const unsigned long long n = countLines(filename);
//     return toBloomFilterFromFilename(filename, k, epsilon_percent, n);
// }
void insertStringToBloomFilter(bf::bloom_filter* filter, const std::string& s, unsigned int k) {
    checknonNull(filter);
    unsigned long long size = s.size();
    for (unsigned long long i = 0; i < size - k + 1; i++) {
        filter->add(s.substr(i, k));
    }
}

bf::bloom_filter* indexFastas(const std::vector<std::string>& filenames, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent) {
    unsigned long long n = 0;
    for (auto const& filename : filenames) {
        n += extractMeaningfullLineFromFasta(filename).length() - k + 1;
    }

    // now that we have the size, let's index those files
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by this implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);
    std::cout << "n = " << n << std::endl;

    std::cout << "m = " << m << std::endl;

    bf::bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), m);

    for (auto const& filename : filenames) {
        std::cout << "Indexing " << filename << "." << std::endl;
        insertStringToBloomFilter(filter, extractMeaningfullLineFromFasta(filename), k);
    }
    std::cout << "exiting indexFastas" << std::endl;
    return filter;
}

// TODO: remove that function
// take a file (ex: abundance_1.txt) and return its bloom filter
// BloomFilter* toBloomFilterFromFilename(const std::string& filename,
//                                        const unsigned int& k,
//                                        const int& epsilon_percent,
//                                        const unsigned long long& n) {
//     std::ifstream file(filename);
//     if (file.is_open()) {
//         unsigned long long m =
//             -(n / log(1 - ((double)epsilon_percent / (double)100)));
//         // oops, maybe m is not a multiple of 8
//         // this is required by this implementation of Bloom filters
//         // let's fix that
//         m = m + 8 - (m % 8);

//         BloomFilter* bloom = new BloomFilter(m, 1, k);
//         std::string line;
//         // store everyting into the BF
//         while (std::getline(file, line)) {
//             insertSeq(*bloom, line, 1, k);
//         }
//         file.close();
//         return bloom;
//     } else {
//         std::cerr << "No file named \"" << filename << "\" found." << std::endl;
//         exit(-1);
//     }
// }

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k) {
    checknonNull(filter, "Nullptr passed to query function.");
    unsigned long long size = s.size();
    unsigned long long nbQuery = 0;  //TODO remove
    std::vector<bool> response(size - k + 1);

    for (unsigned long long i = 0; i < size - k + 1; i++) {
        response[i] = filter->lookup(s.substr(i, k));
        nbQuery++;
    }

    std::cout << "query " << nbQuery << std::endl;
    std::cout << std::endl;
    return response;
}

// double computeSimilarity(BloomFilter* bf, const std::string& seq, int numHashes,
//                          int k) {
//     checknonNull(bf, "Nullptr passed to computeSimilarity function.");
//     ntHashIterator itr(seq, numHashes, k);
//     unsigned long long nbHits = 0;
//     int i = 0;
//     while (itr != itr.end()) {
//         if (bf->contains(*itr)) {
//             nbHits++;
//         }
//         i++;
//         ++itr;
//     }
//     return (nbHits * 1.0) / (i * 1.0);
// }

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    checknonNull(filter, "Nullptr passed to qtf function.");
    unsigned long long size = s.size();

    std::vector<bool> response(size - k + 1);
    unsigned long long nbQuery = 0;  //TODO remove
    unsigned long long i = 0;

    unsigned long long stretchLength = 0;  // number of consecutive positives kmers

    for (unsigned long long j = 0; j < size - k + 1; j++) {
        if (filter->lookup(s.substr(j, k))) {
            stretchLength++;
            nbQuery++;
        } else {
            if (stretchLength != 0) {
                bool responseToAdd = false;
                if (stretchLength > nbNeighboursMin) {
                    responseToAdd = true;
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
        response[i] = 1;
        i++;
    }
    std::cout << "number of query " << i << std::endl;
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

std::vector<bool> qtfSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
    checknonNull(filter, "Nullptr passed to qtfSkip function.");
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
                }
                for (unsigned long long k = 0; k < stretchLength; k++) {
                    response[i] = responseToAdd;
                    i++;
                }
                stretchLength = 0;
            }
            response[i] = 0;
            i++;
            unsigned long long nextPositivePosition = getNextPositiveKmerPositionInTheQuery(filter, s, k, nbNeighboursMin, j, nbQuery);
            // let's fill nextPositivePosition-i-1 negative resuls
            while (i < nextPositivePosition) {
                response[i] = 0;
                i++;
            }
            j = i;
        }
    }
    for (unsigned long long j = 0; j < stretchLength; j++) {
        response[i] = 1;
        i++;
    }
    // TODO remove those cout
    std::cout << "number of query expected" << i << std::endl;
    std::cout << "number of query actaullly made" << nbQuery << std::endl;
    return response;
}

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin) {
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

    std::cout << "number of query / size of qtfplus response " << i << std::endl;
    return response;
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
    std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;
    return {TP, TN, FP, FN};
}
