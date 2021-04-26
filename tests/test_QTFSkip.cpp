#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.hpp"
#include "../src/libraries/truth/truth.hpp"
#include "../src/libraries/utils/utils.hpp"

TEST(TestQTF, TestQTFNoSkipEqualsQTF) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> responseQTFNoSkip = QTFNoSplitKmer::queryNoSkip(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTF = QTFNoSplitKmer::query(filter, querySeq, k, nbNeighboursMin);

    ASSERT_EQ(responseQTFNoSkip, responseQTF);
}