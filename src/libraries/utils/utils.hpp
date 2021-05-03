#pragma once

#include <robin_hood.h>

#include <bf/all.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <zstr.hpp>
std::string changeFilenameExtensionIfAnyOrAddOne(std::string filename, std::string newExtension);
std::string extractContentFromFasta(std::string filename);

inline bool thisFilenameExists(const std::string& name);

inline void dbg(std::string s) {
    std::cout << s;
}

inline std::string extractContentFromFastqGz(std::string filename) {
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);

    std::string line;
    std::string content;

    int i = 0;
    while (std::getline(myfile, line)) {
        if (i == 1) {
            std::cout << "accept: " << line << std::endl;
            content += line;
        } else {
            std::cout << "reject: " << line << std::endl;
        }
        i++;
        i = i % 4;
    }

    return content;
}

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
    for (auto const& i : std::as_const(x)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

inline unsigned long long getNextPositiveKmerPositionInTheQuery(bf::bloom_filter* filter, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long j, unsigned long long& nbQuery) {
    unsigned long long size = s.size();
    while ((j + nbNeighboursMin < size - k + 1) && (!filter->lookup(s.substr(j + nbNeighboursMin, k)))) {
        j += nbNeighboursMin;  //TODO si on veut *>=* nbnbNeighboursMin, enlever 1
        nbQuery++;
    }
    unsigned long long i = 1;
    //TODO eviter dernier query
    while ((j + i < size - k + 1) && (!filter->lookup(s.substr(j + i, k)))) {
        i++;
        nbQuery++;
    }
    j += i;
    return j;
}

inline bool oneQuery(bf::bloom_filter* filter, const std::string s) {
    return filter->lookup(s);
}

inline bool oneQuery(const robin_hood::unordered_set<std::string>& hashSet, const std::string& s) {
    return hashSet.contains(s);
}