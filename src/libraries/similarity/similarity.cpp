#include "similarity.hpp"

#include <bf/all.hpp>
#include <iostream>
#include <tuple>
#include <vector>

#include "../querier/querier.hpp"
std::tuple<int, int> count0And1InAray(std::vector<bool> array) {
    int T = 0;
    int N = 0;
    for (auto const& x : array) {
        if (x) {
            T++;
        } else {
            N++;
        }
    }
    return {T, N};
}

double computeNumberOfExpectedFP(const unsigned int& epsilon_percent, int iteration) {
    double numberOfExpectedFP = 0;
    // only compute the five first terms
    for (int i = 0; i < iteration; i++) {
        numberOfExpectedFP += i * pow(((double)epsilon_percent) / 100.0, i);
    }
    std::cout << "proba" << 95 * numberOfExpectedFP / 100 << "." << std::endl;
    return std::round(95 * numberOfExpectedFP / 100);
}

std::tuple<int, int> computeSimilarityUsingQTFNoSplitKmer(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    std::vector<bool> qtfResponse = QTFNoSplitKmer::query(filter, s, k, nbNeighboursMin);
    return count0And1InAray(qtfResponse);
}

std::tuple<int, int> computeSimilarityQTFCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    unsigned long long nbStretch = 0;
    std::vector<bool> qtfResponse = QTFNoSplitKmer::query(filter, s, k, nbNeighboursMin, nbStretch);
    int numberOfFPExpected = nbStretch * 2 * computeNumberOfExpectedFP(epsilon_percent, 5);
    const auto& [P, N] = count0And1InAray(qtfResponse);
    int pToBeRemoved = std::min(P, numberOfFPExpected);
    return {P - pToBeRemoved, N + pToBeRemoved};
}

std::tuple<int, int> computeSimilarityQTFKPlusZ(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    std::vector<bool> responseQTFKPlusZ = QTF::query(filter, s, k, nbNeighboursMin);
    return count0And1InAray(responseQTFKPlusZ);
}

std::tuple<int, int> computeSimilarityQTFKPlusZCorrected(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, const unsigned int& epsilon_percent) {
    unsigned long long nbStretch = 0;
    std::vector<bool> responseQTFKPlusZ = QTF::query(filter, s, k, nbNeighboursMin, nbStretch);
    int numberOfFPExpected = nbStretch * 2 * computeNumberOfExpectedFP(epsilon_percent, 5);
    const auto& [P, N] = count0And1InAray(responseQTFKPlusZ);
    int pToBeRemoved = std::min(P, numberOfFPExpected);
    return {P - pToBeRemoved, N + pToBeRemoved};
}