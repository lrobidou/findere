#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/evaluation/indexer.hpp"
#include "../src/libraries/evaluation/querier.hpp"
#include "../src/libraries/findere/indexer.hpp"
#include "../src/libraries/findere/querier.hpp"

class forcedResponsebfAMQ : public customAMQ {
   private:
    bf::basic_bloom_filter* _bf;
    std::vector<bool> _tab;
    std::vector<std::string> v = {
        "iuapnvpdrazhjrljjmviihwiojocn",
        "uapnvpdrazhjrljjmviihwiojocns",
        "apnvpdrazhjrljjmviihwiojocnsm",
        "pnvpdrazhjrljjmviihwiojocnsmn",
        "nvpdrazhjrljjmviihwiojocnsmnn",
        "vpdrazhjrljjmviihwiojocnsmnnr",
        "pdrazhjrljjmviihwiojocnsmnnrw",
        "drazhjrljjmviihwiojocnsmnnrwi",
        "razhjrljjmviihwiojocnsmnnrwii"};

   public:
    forcedResponsebfAMQ(bf::basic_bloom_filter* bf, std::vector<bool> tab) : _bf(bf), _tab(tab) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        int i = 0;
        for (const auto& s : v) {
            if (s == x) {
                return _tab[i];
            }
            i++;
        }
        std::cout << "that should not happening" << std::endl;
        exit(1);
    }
};

TEST(TestFindere, TestQueryFilterOrTruth) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned K = 32;  // k-mer size
    const unsigned int z = 3;
    std::string s = "iuapnvpdrazhjrljjmviihwiojocnsmnnrwii";  //ucjukescrreuhrpobpuquhuefuemylbtotnucfqlkdoubadmludmyzxthvgyzyv";

    auto filter = new bf::basic_bloom_filter(0.05, 10);

    std::vector<std::vector<bool>> inputs = {
        {1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 0}};

    std::vector<std::vector<bool>> expectedResponses = {
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}};

    std::vector<std::vector<bool>> responses;

    for (const auto input : inputs) {
        responses.push_back(findere_internal::queryFilterOrTruth(forcedResponsebfAMQ(filter, input), s, K, z, false));
    }

    ASSERT_EQ(responses, expectedResponses);
}