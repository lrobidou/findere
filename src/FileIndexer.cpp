#include "FileIndexer.hpp"

// #include <bloom_filter/basic.hpp>

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

