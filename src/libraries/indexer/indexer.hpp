#pragma once

#include <robin_hood.h>

#include <bf/all.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <zstr.hpp>

#include "../findere/reader/file_manager.hpp"
#include "../findere/utils.hpp"

namespace truth {

/**
 * @brief computes the truth of biological data. Warning: space intensive function.
 * @param filenames the name of the files to be indexed.
 * @param k the value of k
 * @param canonical do xe index canonical kmers ?
 * @return 
 */
inline robin_hood::unordered_set<std::string> indexBio(std::vector<std::string> filenames, int k, bool canonical = false) {
    robin_hood::unordered_set<std::string> output;
    FileManager read_files = FileManager();

    for (auto const& filename : filenames) {
        read_files.addFile(filename);
    }

    std::string& current_read = read_files.get_next_read();
    while (!current_read.empty()) {
        unsigned long long start = 0;
        unsigned long long l = current_read.length();

        if (canonical) {
            while ((start + k) <= l) {
                output.insert(make_canonical(current_read.substr(start, k)));
                start++;
            }
        } else {
            while ((start + k) <= l) {
                output.insert(current_read.substr(start, k));
                start++;
            }
        }
        current_read = read_files.get_next_read();
    }
    return output;
}

/**
 * @brief computes the truth of natural language data. Warning: space intensive function.
 * @param filenames the name of the files to be indexed.
 * @param k the value of k
 * @return the truth
 */
inline robin_hood::unordered_set<std::string> indexText(std::vector<std::string> filenames, int k) {
    robin_hood::unordered_set<std::string> output;
    for (auto const& filename : filenames) {
        std::ifstream myfile(filename);
        std::string content = extractContentFromText(filename);
        unsigned long long start = 0;
        unsigned long long l = content.length();

        while ((start + k) <= l) {
            output.insert(content.substr(start, k));
            start++;
        }
    }

    return output;
}

}  // namespace truth

namespace findere_internal {
inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexBioGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    // number of *unique* elements to add in that filter
    const unsigned long long n = truth.size();
    // size (in bit) required for that filter
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by most implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);

    // now that we have the size, let's index those files
    return findere_internal::indexBioGivenBits(filenames, m, numHashes, k, canonical);
}

inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexTextGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const double& epsilon_percent) {
    // number of *unique* elements to add in that filter
    const unsigned long long n = truth.size();
    // size (in bit) required for that filter
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by most implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);
    return indexTextGivenBits(filenames, m, numHashes, k);
}
}  // namespace findere_internal

/**
 * @brief index biological data using findere (computes the truth too) 
 * @param filenames the name of the files to be indexed
 * @param numHashes the number of hash functions
 * @param k the value of (big) k
 * @param epsilon_percent the desired FPR of the bloom filter (FPR *without* findere)
 * @param canonical do we index canonical kmers ?
 * @return 
 */
inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexBio(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth = truth::indexBio(filenames, k, canonical);
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexBioGivenTruth(filenames, truth, numHashes, k, epsilon_percent, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}

/**
 * @brief index natural language data using findere (computes the truth too) 
 * @param filenames the name of the files to be indexed
 * @param numHashes the number of hash functions
 * @param k the value of (big) k
 * @param epsilon_percent the desired FPR of the bloom filter (FPR *without* findere)
 * @return 
 */
inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexText(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth = truth::indexText(filenames, k);
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexTextGivenTruth(filenames, truth, numHashes, k, epsilon_percent);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}
