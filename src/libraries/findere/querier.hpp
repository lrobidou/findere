#pragma once

#include <vector>

#include "../findere/reader/file_manager.hpp"
#include "customAMQ.hpp"

namespace findere_internal {
/**
 * @brief get the position of the next possible kmer that is positive.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param k the value for (big) k
 * @param nbNeighboursMin the value for z
 * @param j the current position being queried in s
 * @return the number of jumps that can bo done. Each jump means that z position can be skipped.
 */
inline unsigned long long getNextPositiveKmerPositionInTheQuery(const customAMQ& filterOrTruth, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long j) {
    unsigned long long numberOfJumps = 0;
    unsigned long long size = s.size();
    do {
        numberOfJumps += 1;
    } while ((j + numberOfJumps * nbNeighboursMin < size - k + 1) && (filterOrTruth.contains(s.substr(j + numberOfJumps * nbNeighboursMin, k))) == false);
    numberOfJumps -= 1;
    return numberOfJumps;
}

/**
 * @brief Query using findere.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param k the value for (big) k
 * @param nbNeighboursMin the current position being queried in s
 * @return The result of findere's query on s.
 */
inline std::vector<bool> queryFilterOrTruth(const customAMQ& filterOrTruth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin) {
    const unsigned int smallK = k - nbNeighboursMin;  // small k, used to index
    unsigned long long size = s.size();               // size of the query
    std::vector<bool> response(size - k + 1);         // result of the query
    unsigned long long i = 0;                         // index of the response vector
    unsigned long long stretchLength = 0;             // number of consecutive positives kmers
    unsigned long long j = 0;                         // index of the query vector

    while (j < size - k + 1) {
        if (filterOrTruth.contains(s.substr(j, smallK))) {
            stretchLength++;
            j++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    for (unsigned long long t = 0; t < stretchLength - nbNeighboursMin; t++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long t = 0; t < nbNeighboursMin; t++) {
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
            if (nbNeighboursMin > 0) {
                unsigned long long numberOfJumps = getNextPositiveKmerPositionInTheQuery(filterOrTruth, s, smallK, nbNeighboursMin, j);
                for (unsigned long long temp = 0; temp < nbNeighboursMin * numberOfJumps; temp++) {
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

    //reminder: from here, (j == size - k + 1)
    // check if stretchLength can be even bigger
    bool sameStretch = true;
    while ((sameStretch) && (j < size - smallK + 1)) {
        if (filterOrTruth.contains(s.substr(j, smallK))) {
            stretchLength++;
        } else {
            sameStretch = false;
        }
        j++;
    }

    if (stretchLength != 0) {
        if (stretchLength > nbNeighboursMin) {
            for (unsigned long long k = 0; k < stretchLength; k++) {
                response[i] = true;
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
    return response;
}

/**
 * @brief Computes the number of shared position between the query and the index given the response of findere.
 * @param bv The result of the query.
 * @param k the value of (big) k.
 * @return The number of shared position between the query and the index.
 */
unsigned long long get_nb_positions_covered(std::vector<bool> bv, const unsigned int k) {
    unsigned long long nb_positions_covered = 0;  // NB pos covered by at least one shared K-mer
    long long last_covered_position = -1;
    long long pos = 0;
    for (auto shared : bv) {
        if (shared) {
            if (last_covered_position < pos) {
                nb_positions_covered += k;
            } else {
                nb_positions_covered += pos + k - last_covered_position - 1;
            }

            last_covered_position = pos + k - 1;
        }
        pos++;
    }
    return nb_positions_covered;
}
}  // namespace findere_internal

namespace findere {
/**
 * @brief Query only one read of the query using findere.
 * @param filename the name of the file to be queried
 * @param amq the amq wrapped within a customAMQ
 * @param k the value of (big) k
 * @param nbNeighboursMin the value of z
 * @return the result of findere's query applied on the first read
 */
std::vector<bool> inline query_one_sequence(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned long long& nbNeighboursMin) {
    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    return ::findere_internal::queryFilterOrTruth(amq, current_read, k, nbNeighboursMin);
}

/**
 * @brief Query every read of the query using findere.
 * @param filename the name of the file to be queried
 * @param amq the amq wrapped within a customAMQ
 * @param k the value of (big) k
 * @param nbNeighboursMin the value of z
 * @return the result of findere's query applied on alls reads
 */
std::vector<bool> query_all(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned long long& nbNeighboursMin) {
    FileManager read_files = FileManager();
    read_files.addFile(filename);

    std::string current_data = read_files.get_data();
    std::string current_read;
    std::vector<bool> result(0);

    while (!(current_read = read_files.get_next_read()).empty()) {
        std::vector<bool> res = ::findere_internal::queryFilterOrTruth(amq, current_read, k, nbNeighboursMin);
        result.insert(std::end(result), std::begin(res), std::end(res));
    }
    return result;
}

}  // namespace findere