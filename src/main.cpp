#include <robin_hood.h>
#include <zlib.h>

#include <cxxopts.hpp>
#include <string>
#include <zstr.hpp>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/utils/argsUtils.hpp"
#include "libraries/utils/utils.hpp"
void read_fastq(std::string filename) {
    std::ifstream myfile(filename);
    zstr::istream is(myfile);
    std::string s;
    while (getline(is, s)) {
        std::cout << s << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // read_fastq("data/ecoli1.fasta");
    // system("mkdir -p output/txt");  // TODO use parameter
    // system("mkdir -p output/bf");
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);
    try {
        // const auto& [input_filenames, output, queryFile, k, z, epsilon] = getArgs(arguments);
        const auto& [input_filenames, queryFile, k, z, epsilon] = getArgs(arguments);

        std::string querySeq = extractContentFromFasta(queryFile);
        robin_hood::unordered_set<std::string> truthBigK = truth::indexFastas(input_filenames, k);
        const auto& [truthSmallK, smallFilter] = QTF::indexFastas(input_filenames, numHashes, k, epsilon, z);

        std::vector<bool> QTFOnTruth = QTF::query(truthSmallK, querySeq, k, z);
        std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, k, z);
        std::vector<bool> bigTruth = truth::queryTruth(truthBigK, querySeq, k);

        printScore(getScore(bigTruth, QTFOnBloomFilter));
        // TP: 98412, TN :4757970, FP :1123, FN :0
        // FPR: 0.0235969%.
        // FNR: 0%.

        printScore(getScore(bigTruth, QTFOnTruth));
        // TP: 98412, TN :4758947, FP :146, FN :0
        // FPR: 0.00306781%.
        // FNR: 0%.
    } catch (const std::domain_error& e) {
        std::cerr << "Missing option." << std::endl;
    }
}