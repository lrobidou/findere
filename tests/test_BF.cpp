#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.hpp"
#include "../src/libraries/similarity/similarity.hpp"
#include "../src/libraries/utils/utils.hpp"

TEST(TestBF, TestFPR) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    // create a truth and filter
    const auto& [truth, filter, x, y] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> truthQuery = truth::queryTruth(truth, querySeq, k);
    std::vector<bool> responseQuery = noQTF::query(filter, querySeq, k);

    const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQuery);
    double fpr = (double)(100 * FP) / (double)(FP + TN);
    double fnr = (double)(100 * FN) / (double)(FN + TP);

    ASSERT_LT(fpr, 5.1);
    ASSERT_GT(fpr, 4.9);
    ASSERT_EQ(fnr, 0);
}