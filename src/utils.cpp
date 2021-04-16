#include "utils.hpp"

#include <iostream>
#include <tuple>

// #include <BloomFilter.hpp>
// nlohmann::json load_json(std::string filename) {
//     std::ifstream file(filename);
//     if (file.is_open()) {
//         nlohmann::json j;
//         file >> j;
//         file.close();
//         return j;
//     } else {
//         std::cerr << "No file named \"" << filename << "\" found." << std::endl;
//         exit(-1);
//     }
// }

// template <typename T>
// void save_as_json(T x, std::string filename) {
//     nlohmann::json json(x);
//     std::ofstream o(filename);
//     o << std::setw(4) << json << std::endl;
// }

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
    std::cout << "TP: " << TP << ", TN :" << TN << ", FP :" << FP << ", FN :" << FN << std::endl;
    std::cout << "FPR: " << (double)(100 * FP) / (double)(FP + TN) << "%." << std::endl;
    // std::cout << (double)(100 * FN) << "          " << (double)(FN + TP) << std::endl;
    std::cout << "FNR: " << (double)(100 * FN) / (double)(FN + TP) << "%." << std::endl;
}

// inline bool thisFilenameExists(const std::string& name) {
//     struct stat buffer;
//     return (stat(name.c_str(), &buffer) == 0);
// }

// std::unordered_map<int, std::tuple<std::string, unsigned long long>> splitfile(std::string filename) {  //TODO return number of kmer per file
//     std::unordered_map<int, std::tuple<std::string, unsigned long long>> occurences_and_filenames;
//     std::ifstream file(filename);
//     std::string json_filename = changeFilenameExtensionIfAnyOrAddOne(filename, "json");
//     if (thisFilenameExists(json_filename)) {
//         return load_json(json_filename);
//     }
//     if (file.is_open()) {
//         std::unordered_map<int, std::ofstream> filesAlreadyOpened;
//         std::string line;
//         std::string kmer;
//         std::string occurence_str;
//         std::string filename_out;
//         int nline = 0;
//         int occurence = 0;

//         while (std::getline(file, line)) {
//             std::ofstream outfile;
//             size_t pos = line.find('\t');
//             if (string::npos == pos) {
//                 std::cerr << "Line " << line << " of " << filename << " is not correct : \"" << line << "\"." << std::endl;
//             }
//             // get the kmer (first column)
//             kmer = line.substr(0, pos - 1);
//             // get the abundance (second -and last- column)
//             occurence_str = line.substr(pos + 1, line.length() - pos);
//             occurence = std::stoi(occurence_str);
//             filename_out = "output/txt/abundance_" + occurence_str + ".txt";  // TODO change it

//             if (auto it{occurences_and_filenames.find(occurence)}; it != std::end(occurences_and_filenames)) {
//                 std::tuple<std::string, unsigned long long> value{it->second};
//                 std::get<1>(it->second)++;
//             } else {  // Key was not found..
//                 occurences_and_filenames.insert(std::make_pair(occurence, std::make_pair(filename_out, 1)));
//             }
//             outfile.open(filename_out, std::ios_base::app);  // TODO store it a map, so that I don't hav to do open it everytime
//             outfile << kmer;
//         }
//         file.close();
//         nline++;
//     } else {
//         std::cerr << "No file named \"" << filename << "\" found." << std::endl;
//         exit(-1);
//     }
//     save_as_json(occurences_and_filenames, json_filename);
//     return occurences_and_filenames;
// }