#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"

int main(int argc, char* argv[]) {
    // in Python,after import numpy as np: [int(x) for x in np.linspace(100, 2674199464*3, 100)] gives you this:
    std::vector<unsigned long long> membits = {100, 81036446, 162072792, 187000000, 243109139, 324145485, 405181831, 486218178, 567254524, 648290870, 729327217, 810363563, 891399910, 1053472602, 1323593756, 1593714911, 1863836066, 2133957220, 2404078375, 2674199530, 2998344916, 5591508000, 6644980503, 27000000000, 35619976713, 64594972924, 93569969135, 122544965346, 151519961556, 180494957767, 209469953978, 238444950189, 267419946400};

    unsigned long long K = 31;
    unsigned long long z = 3;

    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);

    std::cout << "[" << std::endl;

    std::vector<std::string> input_filenames = {"enwiki-latest-pages-articles1_head100M.txt"};
    std::string queryFile = "enwiki-latest-pages-articles1_next100M.txt";

    std::string querySeq = extractContentFromText(queryFile);

    robin_hood::unordered_set<std::string> truthBigK = truth::indexFastqGz(input_filenames, K, false);
    robin_hood::unordered_set<std::string> truthSmallK = truth::indexFastqGz(input_filenames, K - z, false);
    std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, K);
    // const auto& [normalfilter, size] = findere_internal::indexFastqGZGivenTruth(input_filenames, truthBigK, numHashes, K, 5, false);
    // std::cout << size << std::endl;

    for (const auto& membit : membits) {
        const auto& [normalfilter, sizeSimpleFilter] = findere_internal::indexFastqGZGivenBits(input_filenames, membit, numHashes, K, false);
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilterFindere] = findere::indexFastqGzGivenBits(input_filenames, numHashes, K, z, membit, false);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<bool> noFindereimpleQuery = noQTF::query(normalfilter, querySeq, K);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::vector<bool> findereOnBloomFilter = findere::query(smallFilter, querySeq, K, z, true);
        auto t3 = std::chrono::high_resolution_clock::now();

        findere_internal::printContextBits(K, z, membit);
        std::cout << "        \"time\": {" << std::endl;
        std::cout << "            \"computeBf\": " << timeTakenMs << "," << std::endl;
        std::cout << "            \"queryBfSkip\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << "," << std::endl;
        std::cout << "            \"queryNormalFilter\": " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
        std::cout << "        }," << std::endl;
        findere_internal::printScore(findere_internal::getScore(bigTruth, findereOnBloomFilter), "findere", false, sizeOfBloomFilterFindere);
        findere_internal::printScore(findere_internal::getScore(bigTruth, noFindereimpleQuery), "normalfilter", true, sizeSimpleFilter);
        std::cout << "    }";
        if (membit != 267419946400) {
            std::cout << ",";
        }
        std::cout << std::endl;

        delete smallFilter;
        delete normalfilter;
    }
    std::cout << "]" << std::endl;

    return 0;
}
