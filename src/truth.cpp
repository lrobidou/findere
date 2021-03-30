#include "truth.hpp"

#include <string>
#include <vector>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports
#include "utils.hpp"

void computeTruth(std::vector<std::string> filenames, int k, robin_hood::unordered_set<std::string>& output) {
    for (auto const& filename : filenames) {
        std::string line = extractMeaningfullLineFromFasta(filename);
        unsigned long long start = 0;
        unsigned long long l = line.length();
        while ((start + k) <= l) {
            output.insert(line.substr(start, k));
            start++;
            // std::cout << start * 1.0 / l << std::endl;
        }
    }
}

std::vector<bool> queryTruth(const robin_hood::unordered_set<std::string>& truth, const std::string& seq, int k) {
    unsigned long long start = 0;
    unsigned long long l = seq.length();
    std::vector<bool> response(l - k + 1);

    while ((start + k) <= l) {
        response[start] = truth.contains(seq.substr(start, k));
        start++;
    }
    return response;
}