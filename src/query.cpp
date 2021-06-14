#include <robin_hood.h>
#include <stdio.h>

#include <chrono>
#include <cxxopts.hpp>
#include <findere_lib/customAMQ.hpp>
#include <findere_lib/customResponse.hpp>
#include <findere_lib/querier.hpp>
#include <findere_lib/utils.hpp>
#include <string>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/utils/argsUtils.hpp"

// magic trick to use findere with your own AMQ
// exemple with a bloom filter:
class bfAMQ : public customAMQ {
   private:
    // juste one inner variable: the AMQ we are wrapping
    // (change this type depending on the data structure you want to use)
    bf::basic_bloom_filter* _bf;

   public:
    // pass the bloom filter to our constructor so wa can copy it and just store it
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
        //do nothing more
    }

    // finally, map the contains method to whatever the name of the method of our inner bloom filter
    bool contains(const std::string& x, const bool& canonical) const {
        // just pass the parameter to your amq
        if (canonical) {
            return _bf->lookup(make_canonical(x));
        }
        return _bf->lookup(x);
    }

    //that's all folks
};

class BioPrinter : public customResponse {
   private:
    double _threshold;

   public:
    BioPrinter(double threshold) : _threshold(threshold) {}

    void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) {
        long long nb_positions_covered = findere::get_nb_positions_covered(res, K);
        float ratio = (100 * nb_positions_covered) / float(current_read.length());
        if (ratio > _threshold) {
            std::cout << current_header
                      << "\n"
                      << nb_positions_covered
                      << " over "
                      << current_read.length()
                      << " :"
                      << ratio
                      << "%"
                      << std::endl;
        }
    }
};

class NaturalPrinter : public customResponse {
   private:
    std::string _queryFilename;
    std::string _filterFilenameName;

   public:
    NaturalPrinter(const std::string& query_filename, const std::string& filterFilenameName) : _queryFilename(query_filename), _filterFilenameName(filterFilenameName) {}

    void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) {
        // long long nb_positions_covered = findere::get_nb_positions_covered(res, K);
        // float ratio = (100 * nb_positions_covered) / float(current_read.length());
        std::cout << "File " << _queryFilename
                  << " shares " << std::count(res.begin(), res.end(), true)
                  << " " << K << "-mer(s) among "
                  << res.size()
                  << " with the indexed bank ("
                  << _filterFilenameName << ")"
                  << std::endl;
    }
};

int main(int argc, char* argv[]) {
    const unsigned numHashes = 1;  // number of hash functions
    std::string querySeq;
    cxxopts::ParseResult arguments = parseArgvQuerier(argc, argv);
    unsigned long long K;
    unsigned long long z;
    bool canonical;
    const auto& [filterFilenameName, query_filename, Kuser, zuser, typeInput, threshold, canonicaluser, hasUserProvidedKandzvalue, hasUserProvidedCanonical] = getArgsQuerier(arguments);
    unsigned long long Kinfilter = 0;
    unsigned long long zinfilter = 0;
    bool canonicalinfilter = false;
    bool filterhasKzandcanonicalvalues = false;

    bf::basic_bloom_filter* filter = new bf::basic_bloom_filter(bf::make_hasher(numHashes), filterFilenameName, filterhasKzandcanonicalvalues, Kinfilter, zinfilter, canonicalinfilter);
    if (hasUserProvidedKandzvalue) {
        K = Kuser;
        z = zuser;
        if (filterhasKzandcanonicalvalues && ((Kuser - zuser) != (Kinfilter - zinfilter))) {
            std::cout << "You passed K = " << Kuser << " and z = " << zuser << " (K - z = " << Kuser - zuser << ")" << std::endl;
            std::cout << "The filter contains K = " << Kinfilter << " and z = " << zinfilter << " (K - z = " << Kinfilter - zinfilter << ")" << std::endl;
            std::cout << "The behavior of findere is undefined." << std::endl;
        }
    } else {
        if (filterhasKzandcanonicalvalues) {
            K = Kinfilter;
            z = zinfilter;
        } else {
            std::cerr << "No value for K and z (not in filter neither in user's parameters)." << std::endl;
            exit(1);
        }
    }

    if (hasUserProvidedCanonical) {
        canonical = canonicaluser;
        if (filterhasKzandcanonicalvalues && (canonicaluser != canonicalinfilter)) {
            std::cerr << "You passed canonical = " << canonicaluser << " but the filter contains " << canonicalinfilter << ". The behavior of findere is undefined." << std::endl;
        }
    } else {
        if (filterhasKzandcanonicalvalues) {
            canonical = canonicalinfilter;
        } else {
            std::cerr << "No value for canonical (not in filter neither in user's parameters)." << std::endl;
            exit(1);
        }
    }

    // arg, we have a bf::basic_bloom_filter * now
    // but what if you want to query something else in your own program ?
    // how can you exectute findere::query on your own data structure ?
    // look no further, there we go:
    bfAMQ myAMQ = bfAMQ(filter);
    // the end.

    if (typeInput == "bio") {
        BioPrinter bioPrinter = BioPrinter(threshold);
        findere::query_all(query_filename, myAMQ, K, z, canonical, bioPrinter);
    } else if (typeInput == "text") {
        NaturalPrinter naturalPrinter = NaturalPrinter(query_filename, filterFilenameName);
        findere::query_text(query_filename, myAMQ, K, z, canonical, naturalPrinter);
    } else {
        std::cerr << "The given type of input input '" << typeInput << "' is not recognised." << std::endl;
        exit(1);
    }
    delete filter;
    return 0;
}