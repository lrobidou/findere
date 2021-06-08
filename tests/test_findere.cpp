#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/evaluation/indexer.hpp"
#include "../src/libraries/evaluation/querier.hpp"
#include "../src/libraries/findere/indexer.hpp"
#include "../src/libraries/findere/querier.hpp"

class bfAMQ : public customAMQ {
   private:
    bf::basic_bloom_filter* _bf;

   public:
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        if (canonical) {
            return _bf->lookup(make_canonical(x));
        }
        return _bf->lookup(x);
    }
};

class truthAMQ : public customAMQ {
   private:
    robin_hood::unordered_set<std::string> _t;

   public:
    truthAMQ(const robin_hood::unordered_set<std::string>& t) : _t(t) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        if (canonical) {
            return _t.contains(make_canonical(x));
        }
        return _t.contains(x);
    }
};

class ResultGetter : public customResponse {
   private:
    std::vector<bool> entireResponse;

   public:
    ResultGetter() {}
    void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) {
        entireResponse.insert(std::end(entireResponse), std::begin(res), std::end(res));
    }
    std::vector<bool> getResult() {
        return entireResponse;
    }
};

TEST(TestFindere, TestFPR) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned K = 32;               // k-mer size
    const unsigned numHashes = 1;        // number of hash functions
    const double epsilon_percent = 5.0;  //the value is not usefull, but I need it to use indexBio
    const unsigned int z = 3;
    unsigned long long bits = 284257904;  // size of the filter for a FPR of 5%

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string query_filename = "data/Salmonella enterica.fasta";

    // just need the truth
    const auto& [truth, x_, y_, z_] = indexBio(input_filenames, numHashes, K, epsilon_percent);
    // index with findere
    const auto& [filter, time, size] = findere::indexBioGivenBits(input_filenames, numHashes, K, z, bits);

    std::vector<bool> truthQuery = truth::query_all(query_filename, truthAMQ(truth), K);
    ResultGetter getter = ResultGetter();
    findere::query_all(query_filename, bfAMQ(filter), K, z, false, getter);
    std::vector<bool> responseQuery = getter.getResult();

    const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
    double fpr = (double)(100 * FP) / (double)(FP + TN);
    double fnr = (double)(100 * FN) / (double)(FN + TP);

    ASSERT_LT(fpr, 0.012);
    ASSERT_GT(fpr, 0.011);
    ASSERT_EQ(fnr, 0);
}