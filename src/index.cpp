#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/evaluation/indexer.hpp"
#include "libraries/evaluation/querier.hpp"
#include "libraries/findere/indexer.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"

int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgvIndexer(argc, argv);
    const auto& [input_filenames, output, K, z, b, typeInput, canonical] = getArgsIndexer(arguments);

    if (typeInput == "bio") {
        const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexBioGivenBits(input_filenames, numHashes, K, z, b, canonical);
        filter->save(output, K, z, canonical);
        delete filter;
    } else if (typeInput == "text") {
        const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexTextGivenBits(input_filenames, numHashes, K, z, b);
        filter->save(output, K, z, canonical);
        delete filter;
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised (enter \"bio\" or \"text\")." << std::endl;
    }
    return 0;
}
