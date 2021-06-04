#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/findere/customAMQ.hpp"
#include "libraries/findere/customResponse.hpp"
#include "libraries/findere/indexer.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"

// magic trick to use findere with your own AMQ
// exemple with a bloom filter:
class bfAMQ : public customAMQ {
   private:
    // juste one inner variable: the AMQ we are wrapping
    // (change this type depending on the data structure you want to use)
    bf::basic_bloom_filter* _bf;

   public:
    // pass the bloom filter to our constructor so wa can copy it and just store it
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
        //do nothing more
    }

    // finally, map the contains method to whatever the name of the method of our inner bloom filter
    bool contains(const std::string& x) const {
        // just pass the parameter to your amq
        return _bf->lookup(x);
    }

    //that's all folks
};

class truthAMQ : public customAMQ {
   private:
    robin_hood::unordered_set<std::string> _t;

   public:
    truthAMQ(const robin_hood::unordered_set<std::string>& t) : _t(t) {}

    bool contains(const std::string& x) const {
        return _t.contains(x);
    }
};

class ResultPrinter : public customResponse {
   public:
    ResultPrinter() {}

    void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) {
        long long nb_positions_covered = findere::get_nb_positions_covered(res, K);
        float ratio = (100 * nb_positions_covered) / float(current_read.length());
        if (ratio > 50) {
            std::cout << current_header
                      << "\n"
                      << nb_positions_covered
                      << " over "
                      << current_read.length()
                      << " :"
                      << ratio
                      << "%"
                      << std::endl;
        }
    }
};

void printCommon(std::vector<bool> response, std::string querySeq, int k) {
    unsigned long long j = 0;
    bool stretch = false;
    unsigned long long size = response.size();
    while (j < size) {
        if (response[j] == true) {
            std::cout << querySeq[j];
            stretch = true;
        } else {
            if (stretch) {
                for (int i = 0; i < k - 1; i++) {
                    std::cout << querySeq[j + i];
                }
                std::cout << std::endl;
                stretch = false;
            }
        }
        j++;
    }
}

int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions
    std::string querySeq;
    cxxopts::ParseResult arguments = parseArgvQuerier(argc, argv);
    const auto& [filterFilenameName, query_filename, k, z, typeInput, canonical] = getArgsQuerier(arguments);

    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), filterFilenameName);
    // arg, we have a bf::basic_bloom_filter * now
    // but what if you want to query something else in your own program ?
    // how can you exectute findere::query on your own data structure ?
    // look no further, there we go:
    bfAMQ myAMQ = bfAMQ(filter);
    // the end.

    ResultPrinter printer = ResultPrinter();
    if (typeInput == "bio") {
        findere::query_all(query_filename, myAMQ, k, z, printer);
    } else if (typeInput == "text") {
        std::vector<bool> response = findere::query_text(extractContentFromText(query_filename), myAMQ, k, z);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
        exit(1);
    }
    return 0;
}