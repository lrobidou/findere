#pragma once

#include <string>
#include <vector>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports
void computeTruth(std::vector<std::string> filenames, int k, robin_hood::unordered_set<std::string>& output);

std::vector<bool> queryTruth(const robin_hood::unordered_set<std::string>& truth, const std::string& seq, int k);