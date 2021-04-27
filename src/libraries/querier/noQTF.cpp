#include "noQTF.hpp"

#include <bf/all.hpp>
#include <vector>

#include "../utils/utils.hpp"

std::vector<bool> noQTF::query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k) {
    checknonNull(filter, "Nullptr passed to query function.");
    unsigned long long size = s.size();
    std::vector<bool> response(size - k + 1);

    for (unsigned long long i = 0; i < size - k + 1; i++) {
        response[i] = filter->lookup(s.substr(i, k));
    }

    return response;
}