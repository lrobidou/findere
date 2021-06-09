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
    const auto& [input_filenames, output, k, z, b, typeInput, canonical] = getArgsIndexer(arguments);
    if (typeInput == "fastq") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = findere::indexFastqGzGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
        delete(smallFilter);
    } else if (typeInput == "fasta") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = findere::indexFastasGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
        delete(smallFilter);
    } else if (typeInput == "text") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = findere::indexTextGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
        delete(smallFilter);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised (enter \"bio\" or \"text\")." << std::endl;
    }
    return 0;
}
