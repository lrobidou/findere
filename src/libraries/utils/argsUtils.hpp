#pragma once
#include <cxxopts.hpp>
#include <nlohmann/json.hpp>

#include "utils.hpp"

nlohmann::json
loadJson(const std::string& filename) {
    std::ifstream myfile(filename);
    nlohmann::json j;
    myfile >> j;
    return j;
}

cxxopts::ParseResult parseArgv(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                                             //
        ("i,input", "txt input files", cxxopts::value<std::vector<std::string>>())                    //
        ("q,query", "file containing the query", cxxopts::value<std::string>())                       //
        ("K", "length of K-mers", cxxopts::value<unsigned long long>())                               //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                  //
        ("epsilonpercent", "false positive rate of original Bloom filter", cxxopts::value<double>())  //
        ("s,scenario", "JSON parameter file", cxxopts::value<std::string>())                          //
        ("t,type", "txt input files", cxxopts::value<std::string>())                                  //
        ("b,bits", "size of the filter", cxxopts::value<unsigned long long>())                        //
        ("c,canonical", "do you want to index canonical kmers ?", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
    return options.parse(argc, argv);
}

cxxopts::ParseResult parseArgvIndexer(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                                                        //
        ("i,input", "txt input files", cxxopts::value<std::vector<std::string>>())                               //
        ("o,output", "output filename for the BF", cxxopts::value<std::string>())                                //
        ("K", "length of K-mers", cxxopts::value<unsigned long long>())                                          //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                             //
        ("epsilonpercent", "false positive rate of original Bloom filter", cxxopts::value<double>())             //
        ("t,type", "txt input files", cxxopts::value<std::string>())                                             //
        ("b,bits", "size of the filter", cxxopts::value<unsigned long long>())                                   //
        ("h,help", "display this help", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))  //
        ("c,canonical", "do you want to index canonical kmers ?", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
    return options.parse(argc, argv);
}

cxxopts::ParseResult parseArgvQuerier(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                                                        //
        ("i,input", "index input files", cxxopts::value<std::string>())                                          //
        ("q,query", "file containing the query", cxxopts::value<std::string>())                                  //
        ("K", "length of K-mers", cxxopts::value<unsigned long long>())                                          //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                             //
        ("c", "do you want to index canonical kmers ?", cxxopts::value<bool>())                                  //
        ("h,help", "display this help", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))  //
        ("t,type", "txt input files", cxxopts::value<std::string>()->default_value("bio"))                       //
        ("threshold", "percentage threshold for a read to be considered positive", cxxopts::value<double>())     //
        ;
    return options.parse(argc, argv);
}

template <typename T>
T getOneArg(const cxxopts::ParseResult& arguments, const nlohmann::json& json, const std::string& argName) {
    try {
        return arguments[argName].as<T>();
    } catch (const std::exception& e) {
        if (json.contains(argName)) {
            try {
                return json[argName];
            } catch (const nlohmann::detail::type_error& e) {
                std::cerr << "When trying to get argument \"" << argName << "\":" << std::endl;
                std::cerr << e.what() << std::endl;
                exit(-1);
            }

        } else {
            std::cerr << "It appears you did not provide a valid json or parameter for \"" << argName << "\"" << std::endl;
            std::cerr << "Worry not, for option -h displays some help." << std::endl;
            exit(-1);
        }
    }
}

template <typename T>
T getOneArgOptional(const cxxopts::ParseResult& arguments, const nlohmann::json& json, const std::string& argName, T defaultvalue) {
    try {
        return arguments[argName].as<T>();
    } catch (const std::exception& e) {
        if (json.contains(argName)) {
            try {
                return json[argName];
            } catch (const nlohmann::detail::type_error& e) {
                std::cerr << "When trying to get argument \"" << argName << "\":" << std::endl;
                std::cerr << e.what() << std::endl;
                exit(-1);
            }

        } else {
            std::cout << "using default value for " << argName << " = " << defaultvalue << std::endl;
            return defaultvalue;
        }
    }
}

template <typename T>
T getOneArgOptional(const cxxopts::ParseResult& arguments, const nlohmann::json& json, const std::string& argName, T defaultvalue, bool& isOptionalValue) {
    try {
        return arguments[argName].as<T>();
    } catch (const std::exception& e) {
        if (json.contains(argName)) {
            try {
                return json[argName];
            } catch (const nlohmann::detail::type_error& e) {
                std::cerr << "When trying to get argument \"" << argName << "\":" << std::endl;
                std::cerr << e.what() << std::endl;
                exit(-1);
            }

        } else {
            isOptionalValue = true;
            return defaultvalue;
        }
    }
}

std::tuple<std::vector<std::string>, std::string, unsigned long long, unsigned long long, double, bool, std::string, unsigned long long> getArgs(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    try {
        std::string jsonPath = arguments["s"].as<std::string>();
        json = loadJson(jsonPath);
    } catch (const std::domain_error& e) {
        // do nothing
    } catch (const nlohmann::detail::parse_error& e) {
        // the file do not exists
    }

    std::vector<std::string> input_filenames = getOneArg<std::vector<std::string>>(arguments, json, "i");
    std::string queryFile = getOneArg<std::string>(arguments, json, "q");
    const unsigned long long K = getOneArg<unsigned long long>(arguments, json, "K");
    const unsigned long long z = getOneArg<unsigned long long>(arguments, json, "z");
    const double epsilon = getOneArg<double>(arguments, json, "epsilonpercent");
    const bool canonical = getOneArg<bool>(arguments, json, "c");

    std::string typeInput = getOneArgOptional<std::string>(arguments, json, "type", "bio");
    unsigned long long bits = getOneArgOptional<unsigned long long>(arguments, json, "b", 0);
    return {input_filenames, queryFile, K, z, epsilon, canonical, typeInput, bits};
}

std::tuple<std::vector<std::string>, std::string, unsigned long long, unsigned long long, unsigned long long, std::string, bool> getArgsIndexer(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    const bool displayHelp = getOneArg<bool>(arguments, json, "h");
    if (displayHelp) {
        std::cout << "findere_index: index Kmers using kmers (K>k) indexed in an Approximate Membership Query data structure (a Bloom filter in this implementation)." << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "    ./bin/findere_index -i <inputFiles> -o <index> -b <bits> [-K <K>] [-z <z>] [-t type] [-c]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -i: the input files you want to index. Multiplle files are authorized, with the following format: \"file_name1\",\"file_name2\",\"file_name3\". Files may be gzipped." << std::endl;
        std::cout << "    -o: output index name" << std::endl;
        std::cout << "    -K: the value for K: size of the Kmers queried by findere_query. Default=31" << std::endl;
        std::cout << "    -z: the value for z. findere indexes kmers of size K-z. Default=3" << std::endl;
        std::cout << "    -b: size in bits of the Bloom filter" << std::endl;
        std::cout << "    -t: type of data [bio/text]. Default=bio" << std::endl;
        std::cout << "    -c: index canonical Kmers if type is bio." << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "    ./bin/findere_index -i \"data/ecoli2.fasta\",\"data/ecoli3.fasta\",\"data/Listeria phage.fasta\",\"data/Penicillium chrysogenum.fasta\" -o indexedFastas -K 31 -z 3 -b 10000000 -t bio" << std::endl;
        exit(0);
    }

    // mandatory args
    std::vector<std::string> input_filenames = getOneArg<std::vector<std::string>>(arguments, json, "i");
    std::string output = getOneArg<std::string>(arguments, json, "o");
    const unsigned long long b = getOneArg<unsigned long long>(arguments, json, "b");

    // optional args
    const unsigned long long K = getOneArgOptional<unsigned long long>(arguments, json, "K", 31);
    const unsigned long long z = getOneArgOptional<unsigned long long>(arguments, json, "z", 3);
    std::string typeInput = getOneArgOptional<std::string>(arguments, json, "type", "bio");
    const bool canonical = getOneArgOptional<bool>(arguments, json, "c", false);

    return {input_filenames, output, K, z, b, typeInput, canonical};
}

std::tuple<std::string, std::string, unsigned long long, unsigned long long, std::string, double, bool, bool, bool> getArgsQuerier(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    const bool displayHelp = getOneArg<bool>(arguments, json, "h");
    if (displayHelp) {
        std::cout << "findere_query: query Kmers using kmers (K>k) indexed in an Approximate Membership Query data structure (a Bloom filter in this implementation) stored on a disk." << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "    ./bin/findere_query -i <index> -q <queyFileName> [-K <K>] [-z <z>] -b <bits> [-t type] [-c]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -i: the input index you want to query, that you created with ./bin/index." << std::endl;
        std::cout << "    -q: the file you want to query against the index. May be gzipped." << std::endl;
        std::cout << "    -K: the value for K: size of the Kmers queried by findere_query. Default=what was used at indexation (findere remembers it)" << std::endl;
        std::cout << "    -z: the value for z. findere indexes kmers of size K-z. Default=what was used at indexation (findere remembers it)" << std::endl;
        std::cout << "    -t: type of data [bio/text]. Default=bio" << std::endl;
        std::cout << "    -c: index canonical Kmers if type of data is bio." << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "    ./bin/findere_query -i indexedFastas -q \"data/Listeria phage.fasta\" -K 31 -z 3 -t bio" << std::endl;
        exit(0);
    }

    bool isKdefaultValue = false;
    bool iszdefaultValue = false;
    bool iscanonicaldefaultValue = false;

    // mandatory args
    std::string input_filename = getOneArg<std::string>(arguments, json, "i");
    std::string query_filename = getOneArg<std::string>(arguments, json, "q");

    // optional args
    const unsigned long long K = getOneArgOptional<unsigned long long>(arguments, json, "K", 31, isKdefaultValue);
    const unsigned long long z = getOneArgOptional<unsigned long long>(arguments, json, "z", 3, iszdefaultValue);
    const bool canonical = getOneArgOptional<bool>(arguments, json, "c", false, iscanonicaldefaultValue);

    if (isKdefaultValue != iszdefaultValue) {
        std::cerr << "You must pass either (K and z) or nothing" << std::endl;
        exit(1);
    }
    const double threshold = getOneArgOptional<double>(arguments, json, "threshold", 80);
    std::string typeInput = getOneArgOptional<std::string>(arguments, json, "type", "bio");

    return {input_filename, query_filename, K, z, typeInput, threshold, canonical, !isKdefaultValue, !iscanonicaldefaultValue};
}

void printArgs(std::vector<std::string> input_filenames, std::string queryFile, unsigned long long k, unsigned long long z, int epsilon) {
    printVector(input_filenames);
    std::cout
        << queryFile << std::endl
        << k << std::endl
        << z << std::endl
        << epsilon << std::endl;
}