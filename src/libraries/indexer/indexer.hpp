#pragma once

#include <robin_hood.h>

#include <bf/all.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*, int, unsigned long long> indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent);

namespace truth {
inline robin_hood::unordered_set<std::string> indexFastas(std::vector<std::string> filenames, int k) {
    robin_hood::unordered_set<std::string> output;
    std::string line;
    for (auto const& filename : filenames) {
        std::ifstream myfile(filename);
        if (myfile.is_open()) {
            while (std::getline(myfile, line)) {
                if ((line[0] != '>') && (line[0] != '#')) {
                    unsigned long long start = 0;
                    unsigned long long l = line.length();
                    while ((start + k) <= l) {
                        output.insert(line.substr(start, k));
                        start++;
                    }
                }
            }
            myfile.close();
        } else {
            std::cerr << "The file " << filename << " does not exist." << std::endl;
            exit(1);
        }
    }
    return output;
}

}  // namespace truth

namespace QTF {
std::tuple<robin_hood::unordered_set<std::string>, bf::bloom_filter*, int, unsigned long long> indexFastas(const std::vector<std::string>& filenames, const unsigned int& numHashes, const unsigned int& k, const double& epsilon_percent, const unsigned& nbNeighboursMin);
}