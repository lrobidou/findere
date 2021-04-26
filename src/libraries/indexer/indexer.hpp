#pragma once

#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>
#include <unordered_set>

bf::bloom_filter* indexFastasGivenTruth(const std::vector<std::string>& filenames, const robin_hood::unordered_set<std::string>& truth, const unsigned numHashes, const unsigned int& k, const int& epsilon_percent);

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*> indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const int& epsilon_percent);

namespace QTF {
std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*> indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const int& epsilon_percent, const unsigned& nbNeighboursMin);
}