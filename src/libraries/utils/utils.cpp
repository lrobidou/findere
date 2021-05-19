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