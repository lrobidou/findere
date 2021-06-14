#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <findere_lib/indexer.hpp>
#include <findere_lib/querier.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/evaluation/indexer.hpp"
#include "../src/libraries/evaluation/querier.hpp"

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

TEST(TestBF, TestFPR) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned K = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const double epsilon_percent = 5.0;

    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string query_filename = "data/Salmonella enterica.fasta";

    // create a truth and filter
    const auto& [truth, filter, x, y] = indexBio(input_filenames, numHashes, K, epsilon_percent);

    std::vector<bool> truthQuery = truth::query_all(query_filename, truthAMQ(truth), K);
    ResultGetter getter = ResultGetter();
    findere::query_all(query_filename, bfAMQ(filter), K, 0, false, getter);
    std::vector<bool> responseQuery = getter.getResult();
    // std::cout << filter->storage().size() << std::endl; // about 284257904

    const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
    double fpr = (double)(100 * FP) / (double)(FP + TN);
    double fnr = (double)(100 * FN) / (double)(FN + TP);
    ASSERT_EQ(fnr, 0);
    ASSERT_LT(fpr, 5.1);
    ASSERT_GT(fpr, 4.9);
}