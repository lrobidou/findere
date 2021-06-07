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
    std::vector<bool> _tab;
    std::vector<std::string> v = {
        "01234567890123456789012345678",
        "12345678901234567890123456789",
        "23456789012345678901234567890",
        "34567890123456789012345678901",
        "45678901234567890123456789012",
        "56789012345678901234567890123"};

   public:
    bfAMQ(bf::basic_bloom_filter* bf, std::vector<bool> tab) : _bf(bf), _tab(tab) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        int i = 0;
        for (const auto& s : v) {
            if (s == x) {
                return _tab[i];
            }
            i++;
        }
        std::cout << x << std::endl;
        exit(1);
    }
};

TEST(TestFindere, TestQueryFilterOrTruth) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned K = 32;  // k-mer size
    const unsigned int z = 3;
    std::string s = "0123456789012345678901234567890123";

    auto filter = new bf::basic_bloom_filter(0.05, 10);

    std::vector<std::vector<bool>> vect = {
        {1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 0}};

    for (const auto v : vect) {
        std::vector<bool> responseQueryp = findere_internal::queryFilterOrTruth(bfAMQ(filter, v), s, K, z, false);
        std::vector<bool> responseQueryl = findere_internal::queryFilterOrTruthPapier(bfAMQ(filter, v), s, K, z, false);
        ASSERT_EQ(responseQueryp, responseQueryl);
    }

    delete filter;
}