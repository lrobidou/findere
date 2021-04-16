#pragma once

// #include <bloom_filter/basic.hpp>
// #include <BloomFilter.hpp>
#include <bf/all.hpp>
#include <string>
#include <unordered_set>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"

bf::bloom_filter* indexFastasGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent);

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*> indexFastas(const std::vector<std::string>& filenames, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent);

std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k);

std::vector<bool> qtfNoSkip(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long& nbStretch);

std::vector<bool> qtf(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::vector<bool> qtfIndexKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin);

std::tuple<int, int, int, int> getScore(const std::vector<bool>& truth, const std::vector<bool>& queryResult);

std::tuple<int, int> count0And1InAray(std::vector<bool> array);

double computeNumberOfExpectedFPPerStretch(const unsigned int& epsilon_percent, int iteration);

std::tuple<int, int> computeSimilarityQTF(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFKPlusZCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);
