#include <cxxopts.hpp>
#include <nlohmann/json.hpp>

#include "utils.hpp"

nlohmann::json loadJson(const std::string& filename) {
    std::ifstream myfile(filename);
    nlohmann::json j;
    myfile >> j;
    return j;
}

cxxopts::ParseResult parseArgv(int argc, char* argv[]) {
    cxxopts::Options options("index", "indexer of multifilter");
    options.add_options()                                                           //
        ("i,input", "txt input files", cxxopts::value<std::vector<std::string>>())  //
        // ("o,output", "output directory", cxxopts::value<std::string>())                            //
        ("q,query", "fasta file containing the query", cxxopts::value<std::string>())                 // use fastq.gz
        ("k", "length of k-mers", cxxopts::value<unsigned long long>())                               //
        ("z", "number of sub-k-mers per kmer", cxxopts::value<unsigned long long>())                  //
        ("epsilonpercent", "false positive rate of original Bloom filter", cxxopts::value<double>())  //
        ("s,scenario", "JSON parameter file", cxxopts::value<std::string>())                          //
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
            exit(-1);
        }
    }
}

std::tuple<std::vector<std::string>, std::string, unsigned long long, unsigned long long, int> getArgs(const cxxopts::ParseResult& arguments) {
    nlohmann::json json;
    try {
        std::string jsonPath = arguments["s"].as<std::string>();
        json = loadJson(jsonPath);
    } catch (const std::domain_error& e) {
        // do nothing
        // } catch (const cxxopts::option_has_no_value_exception& e) {
        //     //do nothing
    } catch (const nlohmann::detail::parse_error& e) {
        // the file do not exists
    }

    std::vector<std::string> input_filenames = getOneArg<std::vector<std::string>>(arguments, json, "i");
    // std::string output = getOneArg<std::string>(arguments, json, "o");
    std::string queryFile = getOneArg<std::string>(arguments, json, "q");
    const unsigned long long k = getOneArg<unsigned long long>(arguments, json, "k");
    const unsigned long long z = getOneArg<unsigned long long>(arguments, json, "z");
    const double epsilon = getOneArg<double>(arguments, json, "epsilonpercent");

    // return {input_filenames, output, queryFile, k, z, epsilon};
    return {input_filenames, queryFile, k, z, epsilon};
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