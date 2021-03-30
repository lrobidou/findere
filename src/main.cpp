#include <cstdlib>
#include <cxxopts.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
// #include <nlohmann/json.hpp>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux import
#include "utils.hpp"
cxxopts::ParseResult parseArgv(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()  //
        ("i,input", "txt input files",
         cxxopts::value<std::vector<std::string>>())                        //
        ("j,json", "JSON output directory", cxxopts::value<std::string>())  //
        ("o,output", "output directory", cxxopts::value<std::string>())     //
        ;
    return options.parse(argc, argv);
}

int main(int argc, char* argv[]) {
    // system("mkdir -p output/txt");  // TODO use parameter
    // system("mkdir -p output/bf");
    // const unsigned k = 32;         // k-mer size
    // const unsigned numHashes = 1;  // number of hash functions
    // const int epsilon_percent = 5;
    // const unsigned long long nbNeighboursMin = 6;

    // cxxopts::ParseResult arguments = parseArgv(argc, argv);
    // try {
    //     robin_hood::unordered_set<std::string> truth;
    //     robin_hood::unordered_set<std::string> truthKPlusZ;
    //     std::vector<std::string> input_filenames = arguments["i"].as<std::vector<std::string>>();
    //     BloomFilter* bf = indexFastas(input_filenames, k, epsilon_percent);
    //     std::vector<bool> responseQuery = query(bf, seq, numHashes, k);
    //     std::vector<bool> responseQTF = qtf(bf, seq, numHashes, k, nbNeighboursMin);
    //     std::vector<bool> responseQTFPlus = qtfIndexKPlusZ(bf, seq, numHashes, k, nbNeighboursMin);
    //     computeTruth(input_filenames, k, truth);
    //     computeTruth(input_filenames, k + nbNeighboursMin, truthKPlusZ);
    //     std::vector<bool> truthQuery = queryTruth(truth, seq, k);
    //     std::vector<bool> truthKPlusZQuery = queryTruth(truth, seq, k + nbNeighboursMin);
    //     // const auto& [TP, TN, FP, FN] = getScore(truthKPlusZQuery, responseQTF);
    //     const auto& [TP, TN, FP, FN] = getScore(truthQuery, responseQTF);

    //     std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    //     std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    //     std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;

    //     // std::cout << computeSimilarity(bf, seq, 1, k) << std::endl;
    //     delete bf;
    // } catch (const std::domain_error& e) {
    //     std::cerr << "Missing option." << std::endl;
    // }
}