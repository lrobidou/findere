#include <gtest/gtest.h>
#include <robin_hood.h>

#include <bf/all.hpp>
#include <findere_lib/indexer.hpp>
#include <findere_lib/querier.hpp>
#include <string>

#include "../src/libraries/evaluation/evaluation.hpp"
#include "../src/libraries/evaluation/indexer.hpp"
#include "../src/libraries/evaluation/querier.hpp"

/**
 * @brief get the number of jumps doable before getting to the next kmer that is likely to be positive.
 * @param filterOrTruth the amq wrapped within a customAMQ
 * @param s the sequence to be queried
 * @param k the value for (small) k
 * @param z the value for z
 * @param j the current position being queried in s
 * @return the number of jumps that can bo done. Each jump means that z position can be skipped.
 */
inline unsigned long long getNumberOfJumpBeforeTheNextPositiveKmerPositionInTheQuery(const customAMQ& filterOrTruth, const std::string& s, unsigned int k, const unsigned long long& z, unsigned long long j, const bool& canonical) {
    unsigned long long numberOfJumps = 0;
    unsigned long long size = s.size();
    do {
        numberOfJumps += 1;
    } while ((j + numberOfJumps * z < size - k + 1) && (filterOrTruth.contains(s.substr(j + numberOfJumps * z, k), canonical)) == false);
    numberOfJumps -= 1;
    return numberOfJumps;
}

inline std::vector<bool> queryFilterOrTrutOtherversion(const customAMQ& filterOrTruth, const std::string& s, const unsigned int& K, const unsigned int& z, const bool& canonical) {
    const unsigned int k = K - z;                     // small k, used to index
    unsigned long long size = s.size();               // size of the query
    std::vector<bool> response(size - K + 1, false);  // result of the query
    unsigned long long i = 0;                         // index of the response vector
    unsigned long long stretchLength = 0;             // number of consecutive positives kmers
    unsigned long long j = 0;                         // index of the query vector

    while (j < size - K + 1) {
        if (filterOrTruth.contains(s.substr(j, k), canonical)) {
            stretchLength++;
            j++;
        } else {
            if (stretchLength != 0) {
                if (stretchLength > z) {
                    for (unsigned long long t = 0; t < stretchLength - z; t++) {
                        response[i] = true;
                        i++;
                    }
                    for (unsigned long long t = 0; t < z; t++) {
                        response[i] = false;
                        i++;
                    }
                } else {
                    for (unsigned long long t = 0; t < stretchLength; t++) {
                        response[i] = false;
                        i++;
                    }
                }
                stretchLength = 0;
            }

            // skip queries between current position and the next positive kmer
            if (z > 0) {
                unsigned long long numberOfJumps = getNumberOfJumpBeforeTheNextPositiveKmerPositionInTheQuery(filterOrTruth, s, k, z, j, canonical);
                for (unsigned long long temp = 0; temp < z * numberOfJumps; temp++) {
                    response[i] = false;
                    i++;
                    j++;
                }
            }
            response[i] = 0;
            i++;
            j++;
        }
    }

    //reminder: from here, (j == size - K + 1)
    // check if stretchLength can be even bigger
    bool sameStretch = true;
    while ((sameStretch) && (j < size - k + 1)) {
        if (filterOrTruth.contains(s.substr(j, k), canonical)) {
            stretchLength++;
        } else {
            sameStretch = false;
        }
        j++;
    }

    if (stretchLength > z) {
        for (unsigned long long l = 0; l < stretchLength - z; l++) {
            response[i] = true;
            i++;
        }
    }
    stretchLength = 0;

    return response;
}

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

TEST(TestFindere, TestQueryFilterOrTruthIsSameAsInPaper) {
    robin_hood::unordered_set<std::string> truthPlusK;
    const unsigned K = 32;                // length of Kmer
    const unsigned int z = 3;             // z (see paper for more explanation)
    const unsigned numHashes = 1;         // number of hash functions
    unsigned long long bits = 284257904;  // size of the filter for a FPR of 5%
    std::vector<std::string> input_filenames = {"data/ecoli2.fasta", "data/ecoli3.fasta", "data/Listeria phage.fasta", "data/Penicillium chrysogenum.fasta"};
    std::string query_filename = "data/Salmonella enterica.fasta";

    const auto& [filtercomp, time, size] = findere::indexBioGivenBits(input_filenames, numHashes, K, z, bits);

    std::string content = extractContentFromText(query_filename);

    std::vector<bool> responseQueryl = findere_internal::queryFilterOrTruth(bfAMQ(filtercomp), content, K, z, false);
    std::vector<bool> responseQueryp = queryFilterOrTrutOtherversion(bfAMQ(filtercomp), content, K, z, false);

    ASSERT_EQ(responseQueryl.size(), responseQueryp.size());
    ASSERT_EQ(responseQueryp, responseQueryl);

    delete filtercomp;
}