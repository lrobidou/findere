#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/customAMQ.hpp"
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
    if (typeInput == "bio") {
        std::cout<<"Querying "<<query_filename<<std::endl;
        std::vector<bool> response = findere::query_one_sequence(query_filename, myAMQ, k, z);
        printVector(response);  // beware the huge print
        // findere::query_all(query_filename,myAMQ, k, z);
    } else if (typeInput == "text") {
        std::cerr << "not implemented" <<std::endl;
            // querySeq = extractContentFromText(query_filename);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
    }
    
    // the end.

    //do whatever you want with the response vector.

    //For instance, you can print it:

    // or print common parts between the query and the index
    // printCommon(response, querySeq, k);  // nice french poetry

    // you can also reconstruct the truth to see if everything worked well :
    // of course, the lines below only works if you indexed those files:
    // std::vector<std::string> filenames = {"data/texts/contemplations.txt",
    //                                       "data/texts/Horace.txt",
    //                                       "data/texts/Le_Cid.txt",
    //                                       "data/texts/Maastricht.txt",
    //                                       "data/texts/Othon.txt",
    //                                       "data/texts/Lettres_persanes.txt"};
    // so be sure to change the filenames variable accordingly, to cumpute the correct truth
    // but in real life, you do not reconstruct the truth, because it wont fit in your memory
    // this is just here to test findere

    // std::vector<bool> truthQuery = truth::queryTruth(truth::indexText(filenames, k, canonical), querySeq, k);
    // findere_internal::printScore(findere_internal::getScore(truthQuery, response));
    return 0;
}