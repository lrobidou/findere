#include <robin_hood.h>

#include <bf/all.hpp>
#include <cstdlib>
#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/indexer/indexer.hpp"
#include "libraries/querier/querier.hpp"
#include "libraries/truth/truth.hpp"
#include "libraries/utils/utils.hpp"

nlohmann::json loadJson(const std::string& filename) {
    std::ifstream myfile(filename);
    nlohmann::json j;
    myfile >> j;
    return j;
}

cxxopts::ParseResult parseArgv(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                           //
        ("i,input", "txt input files", cxxopts::value<std::vector<std::string>>())  //
        // ("o,output", "output directory", cxxopts::value<std::string>())                            //
        ("q,query", "fasta file containing the query", cxxopts::value<std::string>())              // use fastq.gz
        ("k", "length of k-mers", cxxopts::value<unsigned long long>())                            //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())               //
        ("epsilonpercent", "false positive rate of original Bloom filter", cxxopts::value<int>())  //
        ("s,scenario", "JSON parameter file", cxxopts::value<std::string>())                       //
        ;
    return options.parse(argc, argv);
}

template <typename T>
T getOneArg(const cxxopts::ParseResult& arguments, const nlohmann::json& json, const std::string& argName) {
    try {
        return arguments[argName].as<T>();
    } catch (const std::exception& e) {
        if (json.contains(argName)) {
            try {
                return json[argName];
            } catch (const nlohmann::detail::type_error& e) {
                std::cerr << "When tryong to get argument \"" << argName << "\":" << std::endl;
                std::cerr << e.what() << std::endl;
                exit(-1);
            }

        } else {
            std::cerr << "It appears you did not provide a valid json or parameter for \"" << argName << "\"" << std::endl;
            exit(-1);
        }
    }
}

std::tuple<std::vector<std::string>, std::string, unsigned long long, unsigned long long, int> getArgs(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    try {
        std::string jsonPath = arguments["s"].as<std::string>();
        json = loadJson(jsonPath);
    } catch (const std::domain_error& e) {
        // do nothing
    } catch (const cxxopts::option_has_no_value_exception& e) {
        //do nothing
    } catch (const nlohmann::detail::parse_error& e) {
        // the file do not exists
    }

    std::vector<std::string> input_filenames = getOneArg<std::vector<std::string>>(arguments, json, "i");
    // std::string output = getOneArg<std::string>(arguments, json, "o");
    std::string queryFile = getOneArg<std::string>(arguments, json, "q");
    const unsigned long long k = getOneArg<unsigned long long>(arguments, json, "k");
    const unsigned long long z = getOneArg<unsigned long long>(arguments, json, "z");
    const int epsilon = getOneArg<int>(arguments, json, "epsilonpercent");

    // return {input_filenames, output, queryFile, k, z, epsilon};
    return {input_filenames, queryFile, k, z, epsilon};
}

int main(int argc, char* argv[]) {
    // system("mkdir -p output/txt");  // TODO use parameter
    // system("mkdir -p output/bf");
    const unsigned numHashes = 1;  // number of hash functions

    cxxopts::ParseResult arguments = parseArgv(argc, argv);
    try {
        // const auto& [input_filenames, output, queryFile, k, z, epsilon] = getArgs(arguments);
        const auto& [input_filenames, queryFile, k, z, epsilon] = getArgs(arguments);

        printVector(input_filenames);
        std::cout
            // << output << std::endl
            << queryFile << std::endl
            << k << std::endl
            << z << std::endl
            << epsilon << std::endl;
        exit(1);

        std::string querySeq = extractContentFromFasta(queryFile);
        robin_hood::unordered_set<std::string> truthBigK = computeTruth(input_filenames, k);
        const auto& [truthSmallK, smallFilter] = QTF::indexFastas(input_filenames, numHashes, k, epsilon, z);

        std::vector<bool> QTFOnTruth = QTF::query(truthSmallK, querySeq, k, z);
        std::vector<bool> QTFOnBloomFilter = QTF::query(smallFilter, querySeq, k, z);
        std::vector<bool> bigTruth = queryTruth(truthBigK, querySeq, k);

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