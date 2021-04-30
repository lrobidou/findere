#include "indexer.hpp"

// #include <bloom_filter/basic.hpp>

#include <robin_hood.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/utils.hpp"

inline void insertStringToBloomFilter(bf::bloom_filter* filter, const std::string& s, unsigned int k) {
    checknonNull(filter);

    unsigned long long start = 0;
    unsigned long long l = s.length();
    while ((start + k) <= l) {
        filter->add(s.substr(start, k));
        start++;
    }
}

inline bf::bloom_filter* indexFastasGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const double& epsilon_percent) {
    // number of *unique* elements to add in that filter
    const unsigned long long n = truth.size();
    // size (in bit) required for that filter
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by most implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);

    // now that we have the size, let's index those files
    bf::bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), m);

    std::string line;
    for (auto const& filename : filenames) {
        std::ifstream myfile(filename);
        if (myfile.is_open()) {
            while (std::getline(myfile, line)) {
                if ((line[0] != '>') && (line[0] != '#')) {
                    insertStringToBloomFilter(filter, line, k);
                }
            }
            myfile.close();
        } else {
            std::cerr << "The file " << filename << " does not exist." << std::endl;
            exit(1);
        }
    }

    return filter;
}

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*, int> indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth = truth::indexFastas(filenames, k);
    auto t0 = std::chrono::high_resolution_clock::now();
    bf::bloom_filter* filter = indexFastasGivenTruth(filenames, truth, numHashes, k, epsilon_percent);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()};
}

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*, int> QTF::indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin) {
    // indexing for QTF is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexFastas(filenames, numHashes, k - nbNeighboursMin, epsilon_percent);
}