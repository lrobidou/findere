#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <zstr.hpp>

/**
 * @brief turns a kmer into a canonical kmer
 * @param kmer the input kmer
 * @return the canonical kmer
 */
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

/**
 * @brief read a text file
 * @param filename the name of the file to be read
 * @return the content of the file
 */
inline std::string extractContentFromText(std::string filename) {
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);

    std::string line;
    std::string content;

    while (std::getline(myfile, line)) {
        content += line;
    }

    return content;
}