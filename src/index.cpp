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
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgvIndexer(argc, argv);
    const auto& [input_filenames, output, k, z, b, typeInput, canonical] = getArgsIndexer(arguments);
    if (typeInput == "fastq") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexFastqGzGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
    } else if (typeInput == "fasta") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexFastasGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
    } else if (typeInput == "text") {
        const auto& [smallFilter, timeTakenMs, sizeOfBloomFilter] = QTF::indexTextGivenBits(input_filenames, numHashes, k, z, b, canonical);
        smallFilter->save(output);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
    }
    return 0;
}
