#include <robin_hood.h>

#include <bf/all.hpp>

#include "QTF.hpp"
#include "QTFNoSplitKmer.hpp"
#include "noQTF.hpp"

namespace truth {
inline std::vector<bool> queryTruth(const robin_hood::unordered_set<std::string>& truth, const std::string& seq, int k) {
    unsigned long long start = 0;
    unsigned long long l = seq.length();
    std::vector<bool> response(l - k + 1);

    while ((start + k) <= l) {
        response[start] = truth.contains(seq.substr(start, k));
        start++;
    }
    return response;
}
}  // namespace truth