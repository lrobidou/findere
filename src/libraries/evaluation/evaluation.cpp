#include <iostream>
#include <tuple>
#include <vector>

std::tuple<int, int, int, int> getScore(const std::vector<bool>& truth, const std::vector<bool>& queryResult) {
    if (truth.size() != queryResult.size()) {
        std::cerr << "The vectors do not have the same size" << std::endl;
        std::cerr << "truth.size()" << truth.size() << std::endl;
        std::cerr << "queryResult.size()" << queryResult.size() << std::endl;
        exit(1);
    }

    unsigned long long size = truth.size();
    unsigned long long TP = 0;
    unsigned long long TN = 0;
    unsigned long long FP = 0;
    unsigned long long FN = 0;

    for (unsigned long long i = 0; i < size; i++) {
        if (truth[i] == true) {
            if (queryResult[i] == true) {
                TP++;
            } else {
                FN++;
            }
        } else {  // truth[i] == false
            if (queryResult[i] == true) {
                FP++;
            } else {
                TN++;
            }
        }
    }

    return {TP, TN, FP, FN};
}