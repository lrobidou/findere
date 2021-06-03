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

inline bool thisFilenameExists(const std::string& name);

inline void dbg(std::string s) {
    //std::cout << s;
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