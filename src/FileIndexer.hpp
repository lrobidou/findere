#pragma once

// #include <bloom_filter/basic.hpp>
// #include <BloomFilter.hpp>
#include <bf/all.hpp>
#include <string>
#include <unordered_set>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"
// BloomFilter* index(const std::string& occurences_and_filenames, const unsigned int& k, const int& epsilon_percent);
bf::bloom_filter* indexFastasGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent);

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*> indexFastas(const std::vector<std::string>& filenames, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent);

// BloomFilter* toBloomFilterFromFilename(const std::string& filename, const unsigned int& numHashes, const int& epsilon_percent, const unsigned long long& n);

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k);

// double computeSimilarity(BloomFilter* bf, const std::string& seq, unsigned int numHashes, int k);

std::vector<bool> qtfNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::tuple<int, int, int, int> getScore(const std::vector<bool>& truth, const std::vector<bool>& queryResult);
