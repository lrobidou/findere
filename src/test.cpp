#include <robin_hood.h>

#include <bf/all.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/truth/truth.hpp"
#include "libraries/utils/utils.hpp"

int main() {
    robin_hood::unordered_set<std::string> truthBigK;

    unsigned int bigK = 32;
    unsigned int smallK = bigK - 6;
    unsigned long long nbNeighboursMin = bigK - smallK;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");
    computeTruth(input_filenames, bigK, truthBigK);

    const auto& [truthSmallK, smallFilter] = indexFastas(input_filenames, 1, smallK, 10);

    std::vector<bool> bigKEmulatedFromQTF = qtfIndexKPlusZ(truthSmallK, querySeq, smallK, nbNeighboursMin);
    std::vector<bool> bigKEmulatedFromQTFBloomFilter = qtfIndexKPlusZ(smallFilter, querySeq, smallK, nbNeighboursMin);
    std::vector<bool> bigTruth = queryTruth(truthBigK, querySeq, bigK);

    printScore(getScore(bigTruth, bigKEmulatedFromQTFBloomFilter));
    // TP: 98412, TN :4757970, FP :1123, FN :0
    // FPR: 0.0235969%.
    // FNR: 0%.

    printScore(getScore(bigTruth, bigKEmulatedFromQTF));
    // TP: 98412, TN :4758947, FP :146, FN :0
    // FPR: 0.00306781%.
    // FNR: 0%.

    // toFileTXT("bigTruth.txt", bigTruth);
    // toFileTXT("bigKEmulatedFromQTFBloomFilter.txt", bigKEmulatedFromQTFBloomFilter);

    return 0;
}