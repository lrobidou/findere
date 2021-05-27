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
        ("q,query", "fasta file containing the query", cxxopts::value<std::string>())                 // use fastq.gz
        ("K", "length of K-mers", cxxopts::value<unsigned long long>())                               //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                  //
        ("epsilonpercent", "false positive rate of original Bloom filter", cxxopts::value<double>())  //
        ("s,scenario", "JSON parameter file", cxxopts::value<std::string>())                          //
        ("t,type", "txt input files", cxxopts::value<std::string>())                                  //
        ("b,bits", "size of the filter", cxxopts::value<unsigned long long>())                        //
        ("c,canonical", "do you want to index cannonical kmers ?", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
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
        ("c,canonical", "do you want to index cannonical kmers ?", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
    return options.parse(argc, argv);
}

cxxopts::ParseResult parseArgvQuerier(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                                                        //
        ("i,input", "index input files", cxxopts::value<std::string>())                                          //
        ("q,query", "fasta file containing the query", cxxopts::value<std::string>())                            // use fastq.gz
        ("K", "length of K-mers", cxxopts::value<unsigned long long>())                                          //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                             //
        ("h,help", "display this help", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))  //
        ("t,type", "txt input files", cxxopts::value<std::string>()->default_value("fastq"))                     //
        ("c,canonical", "do you want to index cannonical kmers ?", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
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
    const unsigned long long k = getOneArg<unsigned long long>(arguments, json, "K");
    const unsigned long long z = getOneArg<unsigned long long>(arguments, json, "z");
    const double epsilon = getOneArg<double>(arguments, json, "epsilonpercent");
    const bool canonical = getOneArg<bool>(arguments, json, "c");

    std::string typeInput = getOneArgOptional<std::string>(arguments, json, "type", "fastq");
    unsigned long long bits = getOneArgOptional<unsigned long long>(arguments, json, "b", 0);
    return {input_filenames, queryFile, k, z, epsilon, canonical, typeInput, bits};
}

std::tuple<std::vector<std::string>, std::string, unsigned long long, unsigned long long, double, std::string, bool> getArgsIndexer(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    const bool displayHelp = getOneArg<bool>(arguments, json, "h");
    if (displayHelp) {
        std::cout << "Welcome." << std::endl;
        std::cout << "I, this executable, can be used to index an AMQ using findere." << std::endl;
        std::cout << "You can execute me like this:" << std::endl;
        std::cout << "./bin/index -i <inputFiles> -o <index> -K <K> -z <z> --epsilonpercent <espilonInPercent> [-t type] [-c]" << std::endl;
        std::cout << "My options are:" << std::endl;
        std::cout << "-i: the input files you want to index;" << std::endl;
        std::cout << "-o: my output. Where should I place the resulting index?" << std::endl;
        std::cout << "-K: the value for K;" << std::endl;
        std::cout << "-z: the value for z. Beware: I will actually index K-z mers;" << std::endl;
        std::cout << "--epsilonpercent: the value for epsilon the index will have if you query it without findere" << std::endl;
        std::cout << "-t: the type of data you want to index. Can be \"fasta\", \"text\" or \"fastq\"." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "If you are a biologist, you may want to to index canonical Kmers. just add -c at the end of the command to do that." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Here is an exemple:" << std::endl;
        std::cout << "./bin/index -i \"data/ecoli2.fasta\",\"data/ecoli3.fasta\",\"data/Listeria phage.fasta\",\"data/Penicillium chrysogenum.fasta\" -o indexedFastas -K 31 -z 3 --epsilonpercent 5 -t fasta" << std::endl;
        exit(0);
    }

    std::vector<std::string> input_filenames = getOneArg<std::vector<std::string>>(arguments, json, "i");
    std::string output = getOneArg<std::string>(arguments, json, "o");
    const unsigned long long K = getOneArgOptional<unsigned long long>(arguments, json, "K", 31);
    const unsigned long long z = getOneArgOptional<unsigned long long>(arguments, json, "z", 3);
    const double epsilon = getOneArg<double>(arguments, json, "epsilonpercent");
    std::string typeInput;
    if (arguments.count("type")) {
        typeInput = arguments["type"].as<std::string>();
    } else {
        typeInput = "fastq";
    }
    const bool canonical = getOneArg<bool>(arguments, json, "c");

    return {input_filenames, output, K, z, epsilon, typeInput, canonical};
}

std::tuple<std::string, std::string, unsigned long long, unsigned long long, std::string, bool> getArgsQuerier(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    const bool displayHelp = getOneArg<bool>(arguments, json, "h");
    if (displayHelp) {
        std::cout << "Welcome." << std::endl;
        std::cout << "I, this executable, can be used to query an AMQ using findere." << std::endl;
        std::cout << "You can execute me like this:" << std::endl;
        std::cout << "./bin/query -i <index> -q <queryFile> -K <K> -z <z> [-t type] [-c]" << std::endl;
        std::cout << "My options are:" << std::endl;
        std::cout << "-i: the input index, that you created with ./bin/index;" << std::endl;
        std::cout << "-q: the file you want to query against the index;" << std::endl;
        std::cout << "-K: the value for K;" << std::endl;
        std::cout << "-z: the value for z. Beware: I will actually query K-z mers;" << std::endl;
        std::cout << "-t: the type of data you want to query. Can be \"fasta\", \"text\" or \"fastq\"." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "If you are a biologist, you may want to tquery canonical Kmers. just add -c at the end of the command to do that." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Here is an exemple:" << std::endl;
        std::cout << "./bin/query -i indexedFastas -q data/Listeria\\ phage.fasta -K 31 -z 3 -t fasta" << std::endl;
        exit(0);
    }
    std::string input_filename = getOneArg<std::string>(arguments, json, "i");
    std::string query_filename = getOneArg<std::string>(arguments, json, "q");
    const unsigned long long K = getOneArgOptional<unsigned long long>(arguments, json, "K", 31);
    const unsigned long long z = getOneArgOptional<unsigned long long>(arguments, json, "z", 3);
    std::string typeInput = "";
    if (arguments.count("type")) {
        typeInput = arguments["type"].as<std::string>();
    } else {
        typeInput = "fastq";
    }

    const bool canonical = getOneArg<bool>(arguments, json, "c");

    return {input_filename, query_filename, K, z, typeInput, canonical};
}

void printArgs(std::vector<std::string> input_filenames, std::string queryFile, unsigned long long k, unsigned long long z, int epsilon) {
    printVector(input_filenames);
    std::cout
        // << output << std::endl
        << queryFile << std::endl
        << k << std::endl
        << z << std::endl
        << epsilon << std::endl;
}