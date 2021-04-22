#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.cpp"
#include "../src/libraries/similarity/similarity.hpp"
#include "../src/libraries/truth/truth.hpp"
#include "../src/libraries/utils/utils.hpp"

TEST(TestQTF, TestSimilarity) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const unsigned int epsilon_percent = 10;
    const unsigned long long nbNeighboursMin = 6;

    std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};
    std::string querySeq = extractContentFromFasta("data/ecoli4.fasta");
    // std::vector<std::string> input_filenames = {
    //     "data/ecoli2.fasta",
    //     "data/ecoli3.fasta",
    //     "data/Listeria phage.fasta",
    //     "data/Penicillium chrysogenum.fasta"};

    // std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");
    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);
    std::vector<bool> truthQuery = queryTruth(truth, querySeq, k);

    robin_hood::unordered_set<std::string> truthKPlusZ;
    computeTruth(input_filenames, k + nbNeighboursMin, truthKPlusZ);
    std::vector<bool> truthKPlusZQuery = queryTruth(truthKPlusZ, querySeq, k + nbNeighboursMin);

    std::vector<bool> responseQTF = qtf(filter, querySeq, k, nbNeighboursMin);
    std::vector<bool> responseQTFKPlusZ = qtfIndexKPlusZ(filter, querySeq, k, nbNeighboursMin);

    const auto& [truth_P, truth_N] = count0And1InAray(truthQuery);
    const auto& [qtf_P, qtf_N] = computeSimilarityQTFKPlusZ(filter, querySeq, k, nbNeighboursMin, epsilon_percent);
    const auto& [qtf_corr_P, qtf_corr_N] = computeSimilarityQTFKPlusZCorrected(filter, querySeq, k, nbNeighboursMin, epsilon_percent);

    std::cout << "truth:         P: " << truth_P << " ,N: " << truth_N << std::endl;
    std::cout << "qtf:           P: " << qtf_P << " ,N: " << qtf_N << std::endl;
    std::cout << "qtf_corrected: P: " << qtf_corr_P << " ,N: " << qtf_corr_N << std::endl;

    printScore(getScore(truthQuery, responseQTF));
    printScore(getScore(truthKPlusZQuery, responseQTFKPlusZ));
    toFileTXT("truthQuery.txt", truthQuery);
    toFileTXT("responseQTF.txt", responseQTF);
    toFileTXT("truthKPlusZQuery.txt", truthKPlusZQuery);
    toFileTXT("responseQTFKPlusZ.txt", responseQTFKPlusZ);
}