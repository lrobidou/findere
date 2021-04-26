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
    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    unsigned int bigK = 32;
    // unsigned int smallK = bigK - 6;
    unsigned long long nbNeighboursMin = 6;
    robin_hood::unordered_set<std::string> truthBigK = computeTruth(input_filenames, bigK);

    const auto& [truthSmallK, smallFilter] = QTF::indexFastas(input_filenames, 1, bigK, 10, nbNeighboursMin);
    std::vector<bool> QTFOnTruth = QTF::query(truthSmallK, querySeq, bigK, nbNeighboursMin);
    std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, bigK, nbNeighboursMin);
    std::vector<bool> bigTruth = queryTruth(truthBigK, querySeq, bigK);

    printScore(getScore(bigTruth, QTFOnBloomFilter));
    // TP: 98412, TN :4757970, FP :1123, FN :0
    // FPR: 0.0235969%.
    // FNR: 0%.

    printScore(getScore(bigTruth, QTFOnTruth));
    // TP: 98412, TN :4758947, FP :146, FN :0
    // FPR: 0.00306781%.
    // FNR: 0%.

    return 0;
}