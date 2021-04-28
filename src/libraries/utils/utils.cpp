#include "utils.hpp"

#include <iostream>
#include <tuple>

std::string changeFilenameExtensionIfAnyOrAddOne(std::string filename, std::string newExtension) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos) {
        filename = filename.substr(0, pos);
    }
    return filename + "." + newExtension;
}

std::string extractContentFromFasta(std::string filename) {
    std::ifstream myfile(filename);
    std::string line;
    std::string content;
    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            if ((line[0] != '>') && (line[0] != '#')) {
                content += line;
            }
        }
        myfile.close();
    } else {
        std::cerr << "The file " << filename << " does not exist." << std::endl;
        exit(1);
    }
    return content;
}

void printScore(const std::tuple<int, int, int, int>& TP_TN_FP_FN) {
    const auto& [TP, TN, FP, FN] = TP_TN_FP_FN;
    std::cout << "        \"results\": {" << std::endl;
    std::cout << "            \"TP\": " << TP << ", \"TN\":" << TN << ", \"FP\":" << FP << ", \"FN\":" << FN << "," << std::endl;
    std::cout << "            \"FPR\": " << (double)(100 * FP) / (double)(FP + TN) << "," << std::endl;
    std::cout << "            \"FNR\": " << (double)(100 * FN) / (double)(FN + TP) << std::endl;
    std::cout << "        }" << std::endl;
}