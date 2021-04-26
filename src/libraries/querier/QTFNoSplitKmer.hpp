#include <robin_hood.h>

#include <bf/all.hpp>
#include <vector>

namespace QTFNoSplitKmer {
std::vector<bool> queryNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> queryNoSkip(robin_hood::unordered_set<std::string> hashSet, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch);

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);
}  // namespace QTFNoSplitKmer