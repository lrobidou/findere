#include <bf/all.hpp>
#include <tuple>

std::tuple<int, int> count0And1InAray(std::vector<bool> array);

double computeNumberOfExpectedFP(const unsigned int& epsilon_percent, int iteration);

std::tuple<int, int> computeSimilarityQTF(bf::basic_bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFCorrected(bf::basic_bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFKPlusZ(bf::basic_bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);

std::tuple<int, int> computeSimilarityQTFKPlusZCorrected(bf::basic_bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent);