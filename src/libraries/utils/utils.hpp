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
    //std::cout << s;
}

inline std::string make_canonical(std::string kmer) {
    std::string reverseComplement(kmer.rbegin(), kmer.rend());
    int l = kmer.length();
    for (int i = 0; i < l; i++) {
        switch (reverseComplement[i]) {
            case 'A':
                reverseComplement[i] = 'T';
                break;
            case 'C':
                reverseComplement[i] = 'G';
                break;
            case 'T':
                reverseComplement[i] = 'A';
                break;
            case 'G':
                reverseComplement[i] = 'C';
                break;
            case 'N':
                reverseComplement[i] = 'N';
                break;
            default:
                std::cerr << reverseComplement[i] << "encountered in a kmer. this is not alloex. Exiting." << std::endl;
                exit(1);
                break;
        }
        if (reverseComplement[i] > kmer[i]) {
            return kmer;
        }
    }
    return reverseComplement;
}

inline std::string extractContentFromFastqGz(std::string filename) {
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);

    std::string line;
    std::string content;

    int i = 0;
    while (std::getline(myfile, line)) {
        if (i == 1) {
            dbg("accept: " + line);
            content += line;
        } else {
            dbg("reject: " + line);
        }
        i++;
        i = i % 4;
    }

    return content;
}

inline std::string extractContentFromText(std::string filename) {
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);

    std::string line;
    std::string content;

    while (std::getline(myfile, line)) {
        content += line;
    }
    // std::cout << content.length() << std::endl; 100539

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

inline bool oneQuery(bf::bloom_filter* filter, const std::string s) {
    return filter->lookup(s);
}

inline bool oneQuery(const robin_hood::unordered_set<std::string>& hashSet, const std::string& s) {
    return hashSet.contains(s);
}

template <typename T>
inline unsigned long long getNextPositiveKmerPositionInTheQuery(T filterOrTruth, const std::string& s, unsigned int k, const unsigned long long& nbNeighboursMin, unsigned long long j, unsigned long long& nbQuery) {
    // std::cout << "getNextPositiveKmerPositionInTheQuery: " << k << " " << j << std::endl;
    unsigned long long numberOfJumps = 0;
    unsigned long long size = s.size();
    do {
        // std::cout << j + numberOfJumps * nbNeighboursMin << " is false." << std::endl;
        numberOfJumps += 1;
        nbQuery++;
    } while ((j + numberOfJumps * nbNeighboursMin < size - k + 1) && (oneQuery(filterOrTruth, s.substr(j + numberOfJumps * nbNeighboursMin, k))) == false);
    numberOfJumps -= 1;
    // std::cout << "returning numberOfJumps = numberOfJumps" << numberOfJumps << std::endl;
    // if (!(j + nbNeighboursMin < size - k + 1)) {
    //     // no positive kmer next
    //     std::cout << "j + nbNeighboursMin if after the end of the query" << std::endl;
    //     return j;
    // }
    // std::cout << "j=" << j << " si a positive" << std::endl;

    // j is now the index of a posiive kmer in the query. Let's backtrack, one kmer by one kmer, until we fond a negative kmer.

    //TODO eviter dernier query
    // while (oneQuery(filterOrTruth, s.substr(j - 1, k))) {
    //     std::cout << j - 1 << " is a positive" << std::endl;
    //     j--;
    //     nbQuery++;
    // }

    // nbQuery++;
    return numberOfJumps;
}