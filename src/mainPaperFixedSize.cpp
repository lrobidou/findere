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
    std::vector<unsigned long long> membits = {100, 81036446, 162072792, 243109139, 324145485, 405181831, 486218178, 567254524, 648290871, 729327217, 810363563, 891399910, 972436256, 1053472602, 1134508949, 1215545295, 1296581642, 1377617988, 1458654334, 1539690681, 1620727027, 1701763374, 1782799720, 1863836066, 1944872413, 2025908759, 2106945105, 2187981452, 2269017798, 2350054145, 2431090491, 2512126837, 2593163184, 2674199530, 2755235877, 2836272223, 2917308569, 2998344916, 3079381262, 3160417608, 3241453955, 3322490301, 3403526648, 3484562994, 3565599340, 3646635687, 3727672033, 3808708380, 3889744726, 3970781072, 4051817419, 4132853765, 4213890111, 4294926458, 4375962804, 4456999151, 4538035497, 4619071843, 4700108190, 4781144536, 4862180883, 4943217229, 5024253575, 5105289922, 5186326268, 5267362614, 5348398961, 5429435307, 5510471654, 5591508000, 5672544346, 5753580693, 5834617039, 5915653386, 5996689732, 6077726078, 6158762425, 6239798771, 6320835117, 6401871464, 6482907810, 6563944157, 6644980503, 6726016849, 6807053196, 6888089542, 6969125889, 7050162235, 7131198581, 7212234928, 7293271274, 7374307620, 7455343967, 7536380313, 7617416660, 7698453006, 7779489352, 7860525699, 7941562045, 8022598392};

    unsigned long long K = 31;
    unsigned long long z = 3;

    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);

    std::cout << "[" << std::endl;

    std::vector<std::string> input_filenames = {};
    std::string queryFile = "";

    std::string querySeq = extractContentFromFastqGz(queryFile);

    robin_hood::unordered_set<std::string> truthBigK = truth::indexFastqGz(input_filenames, K, false);
    robin_hood::unordered_set<std::string> truthSmallK = truth::indexFastqGz(input_filenames, K - z, false);
    std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, K);

    for (const auto& membit : membits) {
        const auto& [normalfilter, numberOfIndexedElements] = QTF_internal::indexFastqGZGivenBits(input_filenames, membit, numHashes, K, false);
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexFastqGzGivenBits(input_filenames, numHashes, K, z, membit, false);

        std::vector<bool> noFindereimpleQuery = noQTF::query(normalfilter, querySeq, K);
        std::vector<bool> findereOnBloomFilter = QTF::query(smallFilter, querySeq, K, z, true);

        QTF_internal::printContextBits(K, z, membit);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, findereOnBloomFilter), "findere", false, sizeOfBloomFilter);
        QTF_internal::printScore(QTF_internal::getScore(bigTruth, noFindereimpleQuery), "normalfilter", true, numberOfIndexedElements);
        std::cout << std::endl;

        delete smallFilter;
        delete normalfilter;
    }
    std::cout << "]" << std::endl;
    return 0;
}
