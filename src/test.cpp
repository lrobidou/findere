// #include <gtest/gtest.h>

#include <bf/all.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "../thirdparty/robinHoodHashing/src/include/robin_hood.h"  // TODO faire de beaux imports
#include "FileIndexer.hpp"
#include "querier.hpp"
#include "truth.hpp"
#include "utils.hpp"

std::string generateRandomLetter() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);  // distribution in range [1, 4]
    int randomInt = dist4(rng);
    if (randomInt == 0) {
        return "A";
    } else if (randomInt == 1) {
        return "C";
    } else if (randomInt == 2) {
        return "T";
    }
    return "G";
}

std::string generateRandomSequence(unsigned long size) {
    std::string s = "";
    while (s.size() < size) {
        s += generateRandomLetter();
    }
    return s;
}

std::string mutate(const std::string& s, int percent_similarity_target, unsigned long blockLength) {
    unsigned long long size = s.size();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, size - 1 - blockLength);  // distribution in range [1, 6]

    std::string smut = s;

    double diff = 1;
    int same = 0;
    while ((double)diff > ((double)percent_similarity_target / 100)) {
        same = 0;
        // std::cout << "muting" << std::endl;
        int start = dist(rng);
        smut = smut.replace(start, blockLength, generateRandomSequence(blockLength));
        for (unsigned long long i = 0; i < size; i++) {
            if (s[i] == smut[i]) {
                same++;
            }
            diff = 1 - (((double)size - (double)same) / (double)size);
        }
        std::cout << "diff" << diff << std::endl;
    }
    return smut;
}

int main() {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned k = 32;         // k-mer size
    const unsigned numHashes = 1;  // number of hash functions
    const int epsilon_percent = 5;
    const unsigned long long nbNeighboursMin = 6;

    // std::vector<std::string> input_filenames = {"data/ecoli1.fasta", "data/ecoli2.fasta", "data/ecoli3.fasta"};
    // std::string querySeq = extractMeaningfullLineFromFasta("data/ecoli4.fasta");
    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string querySeq = extractContentFromFasta("data/Salmonella enterica.fasta");
    /* *****TRUTH***** */
    // // create ground truth
    // robin_hood::unordered_set<std::string> truthKPlusZ;
    // computeTruth(input_filenames, k + nbNeighboursMin, truthKPlusZ);

    /* *****BLOOM_FILTERS***** */
    const auto& [truth, filter] = indexFastas(input_filenames, numHashes, k, epsilon_percent);  // // query it

    // // query it
    std::vector<bool> truthQuery = queryTruth(truth, querySeq, k);
    // std::vector<bool> truthQueryKPlusZ = queryTruth(truthKPlusZ, querySeq, k + nbNeighboursMin);
    unsigned long long nbStretch = 0;
    std::vector<bool> responseQTF = qtf(filter, querySeq, k, nbNeighboursMin, nbStretch);
    // std::vector<bool> responseQTFPlus = qtfIndexKPlusZ(filter, querySeq, k, nbNeighboursMin);
    /* *****SCORE***** */
    // std::cout << "getScore(truthQuery, responseQuery)" << std::endl;
    // printScore(getScore(truthQuery, responseQuery));
    // std::cout << std::endl;

    std::cout << "getScore(truthQuery, responseQTF);" << std::endl;
    printScore(getScore(truthQuery, responseQTF));
    std::cout << std::endl;

    // // getScore(truthQuery, responseQTFPlus);//TODO FPR supr bas, pourquoi ?
    // std::cout << "getScore(truthQueryKPlusZ, responseQTFPlus)" << std::endl;
    // printScore(getScore(truthQueryKPlusZ, responseQTFPlus));
    // std::cout << std::endl;

    // toFileTXT("responseQTFNoSkip.txt", responseQTFNoSkip);
    // toFileTXT("responseQTF.txt", responseQTF);
    // toFileTXT("responseQTFPlus.txt", responseQTFPlus);
    // toFileTXT("responseQuery.txt", responseQuery);
    // toFileTXT("truth.txt", truthQuery);
    // toFileTXT("truthPlusK.txt", truthQueryKPlusZ);

    // std::ofstream out("ecoli75.txt");
    // out << mutate(extractMeaningfullLineFromFasta("data/ecoli1.fasta"), 75, 100);
    // out.close();

    return 0;
}