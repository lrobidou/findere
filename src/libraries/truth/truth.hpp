#pragma once

#include <robin_hood.h>

#include <string>
#include <vector>
void computeTruth(std::vector<std::string> filenames, int k, robin_hood::unordered_set<std::string>& output);

robin_hood::unordered_set<std::string> computeTruth(std::vector<std::string> filenames, int k);

std::vector<bool> queryTruth(const robin_hood::unordered_set<std::string>& truth, const std::string& seq, int k);