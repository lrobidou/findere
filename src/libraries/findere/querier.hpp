#pragma once

#include <vector>

#include "../findere/reader/file_manager.hpp"
#include "customAMQ.hpp"
#include "customResponse.hpp"

namespace findere_internal {
/**
 * @brief get the number of jumps doable before getting to the next kmer that is likely to be positive.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param k the value for (small) k
 * @param z the value for z
 * @param j the current position being queried in s
 * @return the number of jumps that can bo done. Each jump means that z position can be skipped.
 */
inline unsigned long long getNumberOfJumpBeforeTheNextPositiveKmerPositionInTheQuery(const customAMQ& filterOrTruth, const std::string& s, unsigned int k, const unsigned long long& z, unsigned long long j, const bool& canonical) {
    unsigned long long numberOfJumps = 0;
    unsigned long long size = s.size();
    do {
        numberOfJumps += 1;
    } while ((j + numberOfJumps * z < size - k + 1) && (filterOrTruth.contains(s.substr(j + numberOfJumps * z, k), canonical)) == false);
    numberOfJumps -= 1;
    return numberOfJumps;
}

/**
 * @brief Query using findere.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param k the value for (big) k
 * @param z the current position being queried in s
 * @return The result of findere's query on s.
 */

inline std::vector<bool> queryFilterOrTruthPapier(const customAMQ& filterOrTruth, const std::string& s, const unsigned int& K, const unsigned int& z, const bool& canonical) {
    const unsigned int k = K - z;
    unsigned long long size = s.size();
    std::vector<bool> response(size - K + 1, false);
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector
    bool extending_stretch = true;
    while (j < size - k + 1) {
        if (filterOrTruth.contains(s.substr(j, k), canonical)) {
            stretchLength++;
            if (extending_stretch)
                j++;
            else {
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

inline std::vector<bool> queryFilterOrTruth(const customAMQ& filterOrTruth, const std::string& s, const unsigned int& K, const unsigned int& z, const bool& canonical) {
    const unsigned int k = K - z;                     // small k, used to index
    unsigned long long size = s.size();               // size of the query
    std::vector<bool> response(size - K + 1, false);  // result of the query
    unsigned long long i = 0;                         // index of the response vector
    unsigned long long stretchLength = 0;             // number of consecutive positives kmers
    unsigned long long j = 0;                         // index of the query vector

    while (j < size - K + 1) {
        if (filterOrTruth.contains(s.substr(j, k), canonical)) {
            stretchLength++;
            j++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > z) {
                    for (unsigned long long t = 0; t < stretchLength - z; t++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long t = 0; t < z; t++) {
                        response[i] = false;
                        i++;
                    }
                } else {
                    for (unsigned long long t = 0; t < stretchLength; t++) {
                        response[i] = false;
                        i++;
                    }
                }
                stretchLength = 0;
            }

            // skip queries between current position and the next positive kmer
            if (z > 0) {
                unsigned long long numberOfJumps = getNumberOfJumpBeforeTheNextPositiveKmerPositionInTheQuery(filterOrTruth, s, k, z, j, canonical);
                for (unsigned long long temp = 0; temp < z * numberOfJumps; temp++) {
                    response[i] = false;
                    i++;
                    j++;
                }
            }
            response[i] = 0;
            i++;
            j++;
        }
    }

    //reminder: from here, (j == size - K + 1)
    // check if stretchLength can be even bigger
    bool sameStretch = true;
    while ((sameStretch) && (j < size - k + 1)) {
        if (filterOrTruth.contains(s.substr(j, k), canonical)) {
            stretchLength++;
        } else {
            sameStretch = false;
        }
        j++;
    }

    if (stretchLength != 0) {
        if (stretchLength > z) {
            for (unsigned long long l = 0; l < stretchLength - z; l++) {
                response[i] = true;
                i++;
            }
        }
        stretchLength = 0;
    }
    return response;
}

}  // namespace findere_internal

namespace findere {
// TODO not used once, should we remove it ?
// /**
//  * @brief Query only one read of the query using findere.
//  * @param filename the name of the file to be queried
//  * @param amq the amq wrapped within a customAMQ
//  * @param k the value of (big) k
//  * @param z the value of z
//  * @return the result of findere's query applied on the first read
//  */
// std::vector<bool> inline query_one_sequence(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned long long& z) {
//     FileManager read_files = FileManager();
//     read_files.addFile(filename);
//     std::string& current_read = read_files.get_next_read();
//     return ::findere_internal::queryFilterOrTruth(amq, current_read, k, z);
// }

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
inline std::vector<bool> query_text(const std::string& content, const customAMQ& amq, const unsigned int& K, const unsigned long long& z, const bool& canonical) {
    return ::findere_internal::queryFilterOrTruth(amq, content, K, z, canonical);
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
        std::vector<bool> res = ::findere_internal::queryFilterOrTruthPapier(amq, current_read, K, z, canonical);
        response.processResult(res, K, current_header, current_read);
    }
}

}  // namespace findere