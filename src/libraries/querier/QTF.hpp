#pragma once
#include <robin_hood.h>

#include <bf/all.hpp>
#include <vector>

#include "../utils/customAMQ.hpp"
#include "../utils/file_manager.hpp"
#include "../utils/utils.hpp"

template <typename T>
inline std::vector<bool> queryFilterOrTruth(const T& filterOrTruth, const std::string& s, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    const unsigned int smallK = k - nbNeighboursMin;
    unsigned long long size = s.size();
    std::vector<bool> response(size - smallK + 1 - nbNeighboursMin);
    unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector

    while (j < size - k + 1) {
        if (oneQuery(filterOrTruth, s.substr(j, smallK))) {
            stretchLength++;
            j++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > nbNeighboursMin) {
                    nbStretch++;
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
            if (skip && (nbNeighboursMin > 0)) {
                unsigned long long dontCare = 0;
                unsigned long long numberOfJumps = getNextPositiveKmerPositionInTheQuery(filterOrTruth, s, smallK, nbNeighboursMin, j, dontCare);
                // std::cout << "numberOfJumps = " << numberOfJumps << std::endl;
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
    if (stretchLength != 0) {
        if (stretchLength > nbNeighboursMin) {
            nbStretch++;
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

unsigned long long get_nb_positions_covered(std::vector<bool> bv, const unsigned int k) {
    unsigned long long nb_positions_covered = 0;  // NB pos covered by at least one shared K-mer
    long long last_covered_position = -1;
    unsigned long long pos = 0;
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
namespace findere {

std::vector<bool> inline query_one_sequence(const std::string& filename, bf::basic_bloom_filter* filter, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    std::cerr << "query_one_sequence0" << std::endl;
    FileManager read_files = FileManager();
    read_files.addFile(filename);

    std::string& current_read = read_files.get_next_read();
    return queryFilterOrTruth(filter, current_read, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query_one_sequence(const std::string& filename, const robin_hood::unordered_set<std::string>& truth, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    std::cerr << "query_one_sequence1" << std::endl;
    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    return queryFilterOrTruth(truth, current_read, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query_one_sequence(const std::string& filename, bf::basic_bloom_filter* filter, const unsigned int& k, const unsigned long long& nbNeighboursMin, bool skip = false) {
    std::cerr << "query_one_sequence2" << std::endl;
    unsigned long long dontCare = 0;
    FileManager read_files = FileManager();

    std::cerr << "Adding file " << filename << std::endl;
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    std::cerr << "Querying " << current_read << std::endl;
    return queryFilterOrTruth(filter, current_read, k, nbNeighboursMin, dontCare, skip);
}

std::vector<bool> inline query_one_sequence(const std::string& filename, const robin_hood::unordered_set<std::string>& truth, const unsigned int& k, const unsigned int& nbNeighboursMin, bool skip = false) {
    std::cerr << "query_one_sequence3" << std::endl;

    unsigned long long dontCare = 0;

    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    return queryFilterOrTruth(truth, current_read, k, nbNeighboursMin, dontCare, skip);
}

std::vector<bool> inline query_one_sequence(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned int& nbNeighboursMin, unsigned long long& nbStretch, bool skip = false) {
    std::cerr << "query_one_sequence4" << std::endl;
    FileManager read_files = FileManager();
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    return queryFilterOrTruth(amq, current_read, k, nbNeighboursMin, nbStretch, skip);
}

std::vector<bool> inline query_one_sequence(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned long long& nbNeighboursMin, bool skip = false) {
    std::cerr << "query_one_sequence5" << std::endl;
    unsigned long long dontCare = 0;
    FileManager read_files = FileManager();

    std::cerr << "Adding file " << filename << std::endl;
    read_files.addFile(filename);
    std::string& current_read = read_files.get_next_read();
    std::cerr << "Querying " << current_read << std::endl;
    return queryFilterOrTruth(amq, current_read, k, nbNeighboursMin, dontCare, skip);
}

void query_all(const std::string& filename, const customAMQ& amq, const unsigned int& k, const unsigned long long& nbNeighboursMin, bool skip = false) {
    unsigned long long dontCare = 0;
    FileManager read_files = FileManager();
    read_files.addFile(filename);

    std::string current_data = read_files.get_data();
    std::string current_read = read_files.get_next_read();

    while (!current_read.empty()) {
        // Analyse the result of each query
        std::vector<bool> res = queryFilterOrTruth(amq, current_read, k, nbNeighboursMin, dontCare, skip);
        std::cout << current_data << "\n"
                  << get_nb_positions_covered(res, k) << std::endl;
        current_read = read_files.get_next_read();
    }
}

}  // namespace findere