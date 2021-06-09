#pragma once
#include <chrono>
#include <tuple>
#include <vector>

namespace findere_internal {

/**
 * @brief Returns the number of TP, TN, FP and FN given the truth and the response.
 * @param truth the result of the query against the truth
 * @param queryResult the result of the query against the AMQ
 * @return a tuple (TP, TN, FP, FN)
 */
inline std::tuple<int, int, int, int> getScore(const std::vector<bool>& truth, const std::vector<bool>& queryResult) {
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

inline void printContext(const unsigned long long& k, const unsigned long long& z, const double& epsilon) {
    std::cout << "    {" << std::endl;
    std::cout << "        \"param\": {" << std::endl;
    std::cout << "            \"k\": " << k << "," << std::endl;
    std::cout << "            \"z\": " << z << "," << std::endl;
    std::cout << "            \"epsilon\": " << epsilon << std::endl;
    std::cout << "        }," << std::endl;
}

inline void printContextBits(const unsigned long long& k, const unsigned long long& z, const double& epsilon) {
    std::cout << "    {" << std::endl;
    std::cout << "        \"param\": {" << std::endl;
    std::cout << "            \"k\": " << k << "," << std::endl;
    std::cout << "            \"z\": " << z << "," << std::endl;
    std::cout << "            \"bits\": " << epsilon << std::endl;
    std::cout << "        }," << std::endl;
}

inline void printTime(std::chrono::system_clock::time_point t0,
                      std::chrono::system_clock::time_point t1,
                      std::chrono::system_clock::time_point t2,
                      std::chrono::system_clock::time_point t3,
                      std::chrono::system_clock::time_point t4,
                      std::chrono::system_clock::time_point t5,
                      std::chrono::system_clock::time_point t6,
                      std::chrono::system_clock::time_point t7,
                      int taimeTakenByIndexingBf) {
    std::cout << "        \"time\": {" << std::endl;
    // std::cout << "            \"computeTruth\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "," << std::endl;
    std::cout << "            \"computeBf\": " << taimeTakenByIndexingBf << "," << std::endl;
    // std::cout << "            \"queryTruth\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "," << std::endl;
    std::cout << "            \"queryBf\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "," << std::endl;
    ;
    std::cout << "            \"queryBfSkip\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4).count() << "," << std::endl;
    ;
    std::cout << "            \"queryNormalFilter\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t7 - t6).count() << std::endl;
    std::cout << "        }," << std::endl;
}

/**
 * @brief Prints the score in a JSON format
 * @param TP_TN_FP_FN a tuple (TP, TN, FP, FN)
 * @param key a string to be used as a key in the json
 * @param end is this the last object of your json ?
 * @param long the size in bits of the filter.
 * @return 
 */
inline void printScore(const std::tuple<int, int, int, int>& TP_TN_FP_FN, const std::string& key = "", bool end = false, unsigned long long sizeOfBloomFilterInBits = 0) {
    const auto& [TP, TN, FP, FN] = TP_TN_FP_FN;
    std::cout << "        \"" << key << "\": {" << std::endl;
    if (sizeOfBloomFilterInBits > 0) {
        std::cout << "            \"BFSize(bits)\": " << sizeOfBloomFilterInBits << "," << std::endl;
    }
    std::cout << "            \"TP\": " << TP << ",\n            \"TN\": " << TN << ",\n            \"FP\": " << FP << ",\n            \"FN\": " << FN << std::endl;
    std::cout << "        }";
    if (!end) {
        std::cout << ",";
    }
    std::cout << std::endl;
}

// inline void printScore(const std::tuple<int, int, int, int>& TP_TN_FP_FN, const std::string& key) {
//     const auto& [TP, TN, FP, FN] = TP_TN_FP_FN;
//     std::cout << "        \"" << key << "\": {" << std::endl;
//     std::cout << "            \"TP\": " << TP << ", \"TN\":" << TN << ", \"FP\":" << FP << ", \"FN\":" << FN << "," << std::endl;
//     std::cout << "            \"FPR\": " << (double)(100 * FP) / (double)(FP + TN) << "," << std::endl;
//     std::cout << "            \"FNR\": " << (double)(100 * FN) / (double)(FN + TP) << std::endl;
//     std::cout << "        }" << std::endl;
// }
}  // namespace findere_internal
