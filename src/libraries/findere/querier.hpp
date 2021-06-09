#pragma once

#include <vector>

#include "../findere/reader/file_manager.hpp"
#include "customAMQ.hpp"
#include "customResponse.hpp"

namespace findere_internal {

/**
 * @brief Query using findere.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param K the value for (big) k
 * @param z the current position being queried in s
 * @param canonical do we query canonical kmers ?
 * @return The result of findere's query on s.
 */
inline std::vector<bool> queryFilterOrTruth(const customAMQ& amq, const std::string& s, const unsigned int& K, const unsigned int& z, const bool& canonical) {
    const unsigned int k = K - z;
    unsigned long long size = s.size();
    std::vector<bool> response(size - K + 1, false);
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector
    bool extending_stretch = true;
    while (j < size - k + 1) {
        if (amq.contains(s.substr(j, k), canonical)) {
            if (extending_stretch) {
                stretchLength++;
                j++;
            } else {
                extending_stretch = true;
                j = j - z;
            }
        } else {
            if (stretchLength >= z) {
                for (unsigned long long t = j - stretchLength; t < j - z; t++) response[t] = true;
            }
            stretchLength = 0;
            extending_stretch = false;
            j = j + z + 1;
        }
    }
    // Last values:
    if (stretchLength >= z) {
        for (unsigned long long t = size - k + 1 - stretchLength; t < size - K + 1; t++) response[t] = true;
    }

    return response;
}

}  // namespace findere_internal

namespace findere {
/**
 * @brief Computes the number of shared position between the query and the index given the response of findere.
 * @param bv The result of the query.
 * @param K the value of K.
 * @return The number of shared position between the query and the index.
 */
inline unsigned long long get_nb_positions_covered(std::vector<bool> bv, const unsigned int K) {
    unsigned long long nb_positions_covered = 0;  // NB pos covered by at least one shared K-mer
    long long last_covered_position = -1;
    long long pos = 0;
    for (auto shared : bv) {
        if (shared) {
            if (last_covered_position < pos) {
                nb_positions_covered += K;
            } else {
                nb_positions_covered += pos + K - last_covered_position - 1;
            }

            last_covered_position = pos + K - 1;
        }
        pos++;
    }
    return nb_positions_covered;
}

/**
 * @brief Applies findere directly on a string.
 * @param content the query as a string
 * @param amq the amq wrapped within a customAMQ
 * @param K the value of K
 * @param z the value of z
 * @return 
 */
inline void query_text(const std::string& filename, const customAMQ& amq, const unsigned int& K, const unsigned long long& z, const bool& canonical, customResponse& response) {
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);

    std::string line;
    std::string content;

    while (std::getline(myfile, line)) {
        content += line;
    }
    response.processResult(::findere_internal::queryFilterOrTruth(amq, content, K, z, canonical), K, "", content);
}

/**
 * @brief Query every read of the query using findere.
 * @param filename the name of the file to be queried
 * @param amq the amq wrapped within a customAMQ
 * @param K the value of K
 * @param z the value of z
 * @param response a instance of customResponse that implements processResult.
 * @return Nothing. Modify the parameter response instead.
 */
inline void query_all(const std::string& filename, const customAMQ& amq, const unsigned int& K, const unsigned long long& z, const bool& canonical, customResponse& response) {
    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string current_read;

    while (!(current_read = read_files.get_next_read()).empty()) {
        std::string current_data = read_files.get_data();
        std::string current_header = current_data.substr(0, current_data.find('\n'));
        std::vector<bool> res = ::findere_internal::queryFilterOrTruth(amq, current_read, K, z, canonical);
        response.processResult(res, K, current_header, current_read);
    }
}

inline void query_all_paper(const std::string& filename, const customAMQ& amq, const unsigned int& K, const unsigned long long& z, const bool& canonical, customResponse& response) {
    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string current_read;

    while (!(current_read = read_files.get_next_read()).empty()) {
        std::string current_data = read_files.get_data();
        std::string current_header = current_data.substr(0, current_data.find('\n'));
        std::vector<bool> res = ::findere_internal::queryFilterOrTruth(amq, current_read, K, z, canonical);
        response.processResult(res, K, current_header, current_read);
    }
}

}  // namespace findere