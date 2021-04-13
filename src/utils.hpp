#pragma once

#include <iostream>
// #include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
typedef std::vector<std::string> strvect;
// typedef std::unordered_map<int, std::tuple<std::string, unsigned long long>> map_int_tuple;
// typedef std::unordered_map<int, std::string> map_int_string;

// nlohmann::json load_json(std::string filename);
std::string changeFilenameExtensionIfAnyOrAddOne(std::string filename, std::string newExtension);
std::string extractContentFromFasta(std::string filename);

void printScore(const std::tuple<int, int, int, int>& TP_TN_FP_FN);

inline bool thisFilenameExists(const std::string& name);
// inline bool query(BloomFilter bf, const std::string& seq, int numHashes, int k);
// std::unordered_map<int, std::tuple<std::string, unsigned long long>> splitfile(std::string filename);
// void insertSeq(BloomFilter& bloom, const string& seq, unsigned hashNum, unsigned kmerSize);
template <typename T>
inline void checknonNull(T x) {
    if (x == nullptr) {
        std::cerr << "Error: nullptr detected." << std::endl;
        exit(1);
    }
}

template <typename T>
inline void checknonNull(T x, std::string msg) {
    if (x == nullptr) {
        std::cerr << "Error: nullptr detected: " << msg << std::endl;
        exit(1);
    }
}

template <typename T>
void inline toFileTXT(std::string outfilename, T x) {
    remove(outfilename.c_str());

    std::ofstream outFile(outfilename);
    for (const auto& e : x) {
        outFile << e;
    }
}

template <typename T>
inline void printVector(T x) {
    std::cout << "printv:";
    for (auto const& i : std::as_const(x)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}