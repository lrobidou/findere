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
    std::ifstream myfilegz(filename);
    zstr::istream myfile(myfilegz);
    // std::ifstream myfile(filename);
    std::string line;
    std::string content;

    while (std::getline(myfile, line)) {
        if ((line[0] != '>') && (line[0] != '#')) {
            content += line;
        }
    }
    return content;
}