#include <gtest/gtest.h>

#include <bf/all.hpp>
// #include <filesystem>
// #include <fstream>
// #include <iostream>
// #include <random>
#include <string>

#include "../src/FileIndexer.hpp"
#include "../src/querier.hpp"
#include "../src/truth.hpp"
#include "../src/utils.hpp"
#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports

TEST(TestQTF, TestQTFNoSkipEqualsQTF) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");

    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);

    std::vector<bool> responseQTFNoSkip = qtfNoSkip(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTF = qtf(filter, querySeq, k, nbNeighboursMin);

    ASSERT_EQ(responseQTFNoSkip, responseQTF);
}