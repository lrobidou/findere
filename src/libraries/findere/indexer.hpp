#include <bf/all.hpp>
#include <chrono>

#include "reader/file_manager.hpp"
#include "utils.hpp"

namespace findere_internal {

inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned long long bits, const unsigned numHashes, const unsigned int& k, bool canonical) {
    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), bits);
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

inline std::tuple<bf::basic_bloom_filter*, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, unsigned long long bits, const unsigned numHashes, const unsigned int& k) {
    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), bits);

    for (auto const& filename : filenames) {
        // std::ifstream myfilegz(filename);
        // zstr::istream myfile(myfilegz);
        std::string content = extractContentFromText(filename);

        unsigned long long start = 0;
        unsigned long long l = content.length();

        while ((start + k) <= l) {
            filter->add(content.substr(start, k));
            start++;
        }
    }

    return {filter, bits};
}

}  // namespace findere_internal

// inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexBio(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
//     // create ground truth
//     robin_hood::unordered_set<std::string> truth = truth::indexBio(filenames, k, canonical);
//     auto t0 = std::chrono::high_resolution_clock::now();
//     const auto& [filter, sizeOfFilter] = findere_internal::indexBioGivenTruth(filenames, truth, numHashes, k, epsilon_percent, canonical);
//     auto t1 = std::chrono::high_resolution_clock::now();
//     return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
// }

// inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexText(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, bool canonical = false) {
//     // create ground truth
//     robin_hood::unordered_set<std::string> truth = truth::indexText(filenames, k, canonical);
//     auto t0 = std::chrono::high_resolution_clock::now();
//     const auto& [filter, sizeOfFilter] = findere_internal::indexTextGivenTruth(filenames, truth, numHashes, k, epsilon_percent, canonical);
//     auto t1 = std::chrono::high_resolution_clock::now();
//     return {truth, filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
// }

// passing bits as parameter

/**
 * @brief Index biological data given a size in bits.
 * @param filenames the list of filenames that contains reads to be indexed
 * @param numHashes the number of hash function to be used
 * @param k the value for (small) k
 * @param bits the size in bits to be allocated to the filter
 * @param canonical do we index canonical data ?
 * @return 
 */
inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, unsigned long long bits, bool canonical = false) {
    // create ground truth
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexBioGivenBits(filenames, bits, numHashes, k, canonical);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}

/**
 * @brief Index texts given a size in bits.
 * @param filenames the list of filenames that contains texts to be indexed
 * @param numHashes the number of hash function to be used
 * @param k the value for (small) k
 * @param bits the size in bits to be allocated to the filter
 * @return 
 */
inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, unsigned long long bits) {
    // create ground truth
    auto t0 = std::chrono::high_resolution_clock::now();
    const auto& [filter, sizeOfFilter] = findere_internal::indexTextGivenBits(filenames, bits, numHashes, k);
    auto t1 = std::chrono::high_resolution_clock::now();
    return {filter, std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(), sizeOfFilter};
}

namespace findere {
// inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexBio(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin, bool canonical = false) {
//     // indexing for findere is easy: just index as usual, but with k = k - nbNeighboursMin
//     return ::indexBio(filenames, numHashes, k - nbNeighboursMin, epsilon_percent, canonical);
// }

// inline std::tuple<robin_hood::unordered_set<std::string>, bf::basic_bloom_filter*, int, unsigned long long> indexText(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin, bool canonical = false) {
//     // indexing for findere is esay: just index as usual, but with k = k - nbNeighboursMin
//     return ::indexText(filenames, numHashes, k - nbNeighboursMin, epsilon_percent, canonical);
// }

// passing bits as parameter

/**
 * @brief Index biological data using findere, given a size in bits.
 * @param filenames the list of filenames that contains reads to be indexed
 * @param numHashes the number of hash function to be used
 * @param k the value for (big) k
 * @param nbNeighboursMin the value of z
 * @param bits the size in bits to be allocated to the filter
 * @param canonical
 * @return 
 */
inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexBioGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const unsigned& nbNeighboursMin, unsigned long long bits, bool canonical = false) {
    // indexing for findere is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexBioGivenBits(filenames, numHashes, k - nbNeighboursMin, bits, canonical);
}

/**
 * @brief Index texts uding findere, given a size in bits.
 * @param filenames the list of filenames that contains texts to be indexed
 * @param numHashes the number of hash function to be used
 * @param k the value for (big) k
 * @param nbNeighboursMin the value of z
 * @param bits the size in bits to be allocated to the filter
 * @return 
 */
inline std::tuple<bf::basic_bloom_filter*, int, unsigned long long> indexTextGivenBits(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const unsigned& nbNeighboursMin, unsigned long long bits) {
    // indexing for findere is esay: just index as usual, but with k = k - nbNeighboursMin
    return ::indexTextGivenBits(filenames, numHashes, k - nbNeighboursMin, bits);
}
}  // namespace findere