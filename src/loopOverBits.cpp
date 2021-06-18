// #include <robin_hood.h>
#include <findere_lib/customResponse.hpp>
#include <findere_lib/indexer.hpp>
#include <findere_lib/querier.hpp>

#include "libraries/evaluation/evaluation.hpp"
#include "libraries/evaluation/indexer.hpp"
#include "libraries/evaluation/querier.hpp"

class bfAMQ : public customAMQ {
   private:
    bf::basic_bloom_filter* _bf;

   public:
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        if (canonical) {
            return _bf->lookup(make_canonical(x));
        }
        return _bf->lookup(x);
    }
};

class truthAMQ : public customAMQ {
   private:
    robin_hood::unordered_set<std::string> _t;

   public:
    truthAMQ(const robin_hood::unordered_set<std::string>& t) : _t(t) {
    }

    bool contains(const std::string& x, const bool& canonical) const {
        if (canonical) {
            return _t.contains(make_canonical(x));
        }
        return _t.contains(x);
    }
};

class ResultGetter : public customResponse {
   private:
    std::vector<bool> entireResponse;

   public:
    ResultGetter() {}
    void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) {
        entireResponse.insert(std::end(entireResponse), std::begin(res), std::end(res));
    }
    std::vector<bool> getResult() {
        return entireResponse;
    }
};

int main() {
    std::vector<unsigned long long> bits = {100000, 7410526, 15410526, 36410526, 66410526, 126410526, 226410526, 526410526, 1052721052, 1579031578, 2105342105, 2631652631, 3157963157, 3684273684, 4210584210, 4736894736, 5263205263, 5789515789, 6315826315, 6842136842, 7368447368, 7894757894, 8421068421, 8947378947, 9473689473, 10000000000};
    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string query_filename = "data/ecoli1.fasta";
    const unsigned int K = 31;
    const unsigned int z = 3;
    const bool canonical = false;

    robin_hood::unordered_set<std::string> truth = truth::indexBio(input_filenames, K, canonical);
    unsigned long long numberOfUniqueElements = truth.size();
    std::vector<bool> truthQuery = truth::query_all(query_filename, truthAMQ(truth), K);

    /////////// hash: 1
    // findere: one hash function
    std::ofstream myfile;
    myfile.open("findere1.txt");
    std::size_t numberOfHashFunctions = 1;
    for (unsigned long long bit : bits) {
        const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexBioGivenBits(input_filenames, numberOfHashFunctions, K, z, bit, canonical);
        ResultGetter getter = ResultGetter();
        findere::query_all(query_filename, bfAMQ(filter), K, z, false, getter);
        std::vector<bool> responseQuery = getter.getResult();
        delete filter;

        const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
        double fpr = (double)(100 * FP) / (double)(FP + TN);
        double fnr = (double)(100 * FN) / (double)(FN + TP);
        myfile << numberOfUniqueElements << " " << bit << " " << fpr << " " << fnr << std::endl;
    }
    myfile.close();

    // BF: one hash function
    myfile.open("bf1.txt");
    for (unsigned long long bit : bits) {
        const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexBioGivenBits(input_filenames, numberOfHashFunctions, K, 0, bit, canonical);
        ResultGetter getter = ResultGetter();
        findere::query_all(query_filename, bfAMQ(filter), K, 0, false, getter);
        std::vector<bool> responseQuery = getter.getResult();
        delete filter;

        const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
        double fpr = (double)(100 * FP) / (double)(FP + TN);
        double fnr = (double)(100 * FN) / (double)(FN + TP);
        myfile << numberOfUniqueElements << " " << bit << " " << fpr << " " << fnr << std::endl;
    }
    myfile.close();

    // /////////// hash: optimal
    // // findere: optimal hash function
    // bits = {100000, 12011080, 23922160, 35833240, 47744321, 59655401, 71566481, 83477562, 95388642, 107299722, 119210803, 131121883, 143032963, 154944044, 166855124, 178766204, 190677285, 202588365, 214499445, 226410526};
    // myfile.open("findereopti.txt");
    // for (unsigned long long bit : bits) {
    //     size_t optimal_h = bf::basic_bloom_filter::k(bit, numberOfUniqueElements);
    //     const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexBioGivenBits(input_filenames, optimal_h, K, z, bit, canonical);
    //     ResultGetter getter = ResultGetter();
    //     findere::query_all(query_filename, bfAMQ(filter), K, z, false, getter);
    //     std::vector<bool> responseQuery = getter.getResult();
    //     delete filter;

    //     const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
    //     double fpr = (double)(100 * FP) / (double)(FP + TN);
    //     double fnr = (double)(100 * FN) / (double)(FN + TP);
    //     myfile << numberOfUniqueElements << " " << bit << " " << fpr << " " << fnr << std::endl;
    // }
    // myfile.close();

    // // BF: optimal hash function
    // myfile.open("bfopti.txt");
    // for (unsigned long long bit : bits) {
    //     size_t optimal_h = bf::basic_bloom_filter::k(bit, numberOfUniqueElements);
    //     const auto& [filter, timeTakenMs, sizeOfBloomFilter] = findere::indexBioGivenBits(input_filenames, optimal_h, K, 0, bit, canonical);
    //     ResultGetter getter = ResultGetter();
    //     findere::query_all(query_filename, bfAMQ(filter), K, 0, false, getter);
    //     std::vector<bool> responseQuery = getter.getResult();
    //     delete filter;

    //     const auto& [TP, TN, FP, FN] = findere_internal::getScore(truthQuery, responseQuery);
    //     double fpr = (double)(100 * FP) / (double)(FP + TN);
    //     double fnr = (double)(100 * FN) / (double)(FN + TP);
    //     myfile << numberOfUniqueElements << " " << bit << " " << fpr << " " << fnr << std::endl;
    // }
    // myfile.close();

    return 0;
}