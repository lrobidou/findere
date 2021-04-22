#include <robin_hood.h>

#include <bf/all.hpp>
std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k);

std::vector<bool> qtfNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtfNoSkip(robin_hood::unordered_set<std::string> hashSet, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch);

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch);

std::vector<bool> qtfIndexKPlusZ(robin_hood::unordered_set<std::string> truth, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch);

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtfIndexKPlusZ(robin_hood::unordered_set<std::string> truth, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);