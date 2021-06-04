#include <robin_hood.h>

#include <bf/all.hpp>

#include "../findere/querier.hpp"
#include "../utils/utils.hpp"

namespace noQTF {
/**
 * @brief Performs a simple query without findere.
 * @param filter the bloom filter, not wrapped into a customAMQ
 * @param s the sequence to be queried
 * @param k the value of k
 * @return 
 */
inline std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k) {
    checknonNull(filter, "Nullptr passed to query function.");
    unsigned long long size = s.size();
    std::vector<bool> response(size - k + 1);

    for (unsigned long long i = 0; i < size - k + 1; i++) {
        response[i] = filter->lookup(s.substr(i, k));
    }

    return response;
}
}  // namespace noQTF

namespace truth {

/**
 * @brief Performs a query, not using findere.
 * @param amq the amq, wrapped into a customAMQ
 * @param seq the sequence to be queried
 * @param k the value of k
 * @return 
 */
inline std::vector<bool> queryString(const customAMQ& amq, const std::string& seq, int k) {
    unsigned long long start = 0;
    unsigned long long l = seq.length();
    std::vector<bool> response(l - k + 1);

    while ((start + k) <= l) {
        response[start] = amq.contains(seq.substr(start, k));
        start++;
    }
    return response;
}

/**
 * @brief Performs a query, not using findere
 * @param filename the name of the file to be queried
 * @param amq the amq, wrapped into a customAMQ 
 * @param k the value of k
 * @return 
 */
inline std::vector<bool> query_all(const std::string& filename, const customAMQ& amq, const unsigned int& k) {
    FileManager read_files = FileManager();
    read_files.addFile(filename);

    std::string current_data = read_files.get_data();
    std::vector<bool> result(0);

    std::string current_read;
    while (!(current_read = read_files.get_next_read()).empty()) {
        std::vector<bool> res = queryString(amq, current_read, k);
        result.insert(std::end(result), std::begin(res), std::end(res));
    }
    return result;
}
}  // namespace truth