#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/findere/indexer.hpp"
#include "../src/libraries/findere/querier.hpp"
#include "../src/libraries/indexer/indexer.hpp"
#include "../src/libraries/querier/querier.hpp"

class bfAMQ : public customAMQ {
   private:
    bf::basic_bloom_filter* _bf;

   public:
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
    }

    bool contains(const std::string& x) const {
        return _bf->lookup(x);
    }
};

class truthAMQ : public customAMQ {
   private:
    robin_hood::unordered_set<std::string> _t;

   public:
    truthAMQ(const robin_hood::unordered_set<std::string>& t) : _t(t) {
    }

    bool contains(const std::string& x) const {
        return _t.contains(x);
    }
};

TEST(TestBF, TestFPR) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string query_filename = "data/Salmonella enterica.fasta";

    // create a truth and filter
    const auto& [truth, filter, x, y] = indexBio(input_filenames, numHashes, k, epsilon_percent, 0);

    std::vector<bool> truthQuery = truth::query_all(query_filename, truthAMQ(truth), k);
    std::vector<bool> responseQuery = findere::query_all(query_filename, bfAMQ(filter), k, 0);

    const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
    double fpr = (double)(100 * FP) / (double)(FP + TN);
    double fnr = (double)(100 * FN) / (double)(FN + TP);

    ASSERT_LT(fpr, 5.1);
    ASSERT_GT(fpr, 4.9);
    ASSERT_EQ(fnr, 0);
}