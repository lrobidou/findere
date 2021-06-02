#pragma once

#include <robin_hood.h>

#include <bf/all.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <zstr.hpp>

#include "../utils/utils.hpp"
#include "../utils/file_manager.hpp"

namespace truth {


inline robin_hood::unordered_set<std::string> indexBio(std::vector<std::string> filenames, int k, bool canonical = false) {
    robin_hood::unordered_set<std::string> output;



    FileManager read_files = FileManager ();
    
    for (auto const& filename : filenames) {
        read_files.addFile(filename);
    }


    std::string & current_read = read_files.get_next_read();
    while (!current_read.empty()) {


        unsigned long long start = 0;
        unsigned long long l = current_read.length();
        
        if (canonical) {
            // std::cout << "canonical" << std::endl;
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

inline robin_hood::unordered_set<std::string> indexText(std::vector<std::string> filenames, int k, bool canonical = false) {
    robin_hood::unordered_set<std::string> output;
    for (auto const& filename : filenames) {
        std::ifstream myfile(filename);
        std::string content = extractContentFromText(filename);
        unsigned long long start = 0;
        unsigned long long l = content.length();
        if (canonical) {
            while ((start + k) <= l) {
                output.insert(make_canonical(content.substr(start, k)));
                start++;
            }
        } else {
            while ((start + k) <= l) {
                output.insert(content.substr(start, k));
                start++;
            }
        }
    }

    return output;
}

}  // namespace truth

namespace findere_internal {



inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned long long bits, const unsigned numHashes, const unsigned int& k, bool canonical) {
    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), bits);
    
    FileManager read_files = FileManager ();
    
    for (auto const& filename : filenames) {
        read_files.addFile(filename);
    }


    std::string & current_read = read_files.get_next_read();
    while (!current_read.empty()) {


        unsigned long long start = 0;
        unsigned long long l = current_read.length();
        if (canonical) {
            while ((start + k) <= l) {
                filter->add(make_canonical(current_read.substr(start, k)));
                start++;
            }
        } else {
            while ((start + k) <= l) {
                filter->add(current_read.substr(start, k));
                start++;
            }
        }    
        current_read = read_files.get_next_read();
    }

    return {filter, bits};
}

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
    return indexBioGivenBits(filenames, m, numHashes, k, canonical);
}

inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, unsigned long long bits, const unsigned numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), bits);

    for (auto const& filename : filenames) {
        // std::ifstream myfilegz(filename);
        // zstr::istream myfile(myfilegz);
        std::string content = extractContentFromText(filename);

        unsigned long long start = 0;
        unsigned long long l = content.length();
        if (canonical) {
            while ((start + k) <= l) {
                filter->add(make_canonical(content.substr(start, k)));
                start++;
            }
        } else {
            while ((start + k) <= l) {
                filter->add(content.substr(start, k));
                start++;
            }
        }
    }

    return {filter, bits};
}

inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexTextGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    // number of *unique* elements to add in that filter
    const unsigned long long n = truth.size();
    // size (in bit) required for that filter
    unsigned long long m = -(n / log(1 - ((double)epsilon_percent / (double)100)));
    // oops, maybe m is not a multiple of 8
    // this is required by most implementation of Bloom filters
    // let's fix that
    m = m + 8 - (m % 8);
    return indexTextGivenBits(filenames, m, numHashes, k, epsilon_percent, canonical);
}
}  // namespace findere_internal

inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexBio(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth = truth::indexBio(filenames, k, canonical);
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexBioGivenTruth(filenames, truth, numHashes, k, epsilon_percent, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}


inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexText(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
    // create ground truth
    robin_hood::unordered_set<std::string> truth = truth::indexText(filenames, k, canonical);
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexTextGivenTruth(filenames, truth, numHashes, k, epsilon_percent, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}

// passing bits as parameter

inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, unsigned long long bits, bool canonical = false) {
    // create ground truth
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexBioGivenBits(filenames, bits, numHashes, k, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}


inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, unsigned long long bits, bool canonical = false) {
    // create ground truth
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexTextGivenBits(filenames, bits, numHashes, k, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}

namespace findere {
inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexBio(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin, bool canonical = false) {
    // indexing for QTF is easy: just index as usual, but with k = k - nbNeighboursMin
    return ::indexBio(filenames, numHashes, k - nbNeighboursMin, epsilon_percent, canonical);
}

inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexText(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin, bool canonical = false) {
    // indexing for QTF is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexText(filenames, numHashes, k - nbNeighboursMin, epsilon_percent, canonical);
}

// passing bits as parameter

inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const unsigned& nbNeighboursMin, unsigned long long bits, bool canonical = false) {
    // indexing for QTF is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexBioGivenBits(filenames, numHashes, k - nbNeighboursMin, bits, canonical);
}

inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const unsigned& nbNeighboursMin, unsigned long long bits, bool canonical = false) {
    // indexing for QTF is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexTextGivenBits(filenames, numHashes, k - nbNeighboursMin, bits, canonical);
}
}  // namespace findere