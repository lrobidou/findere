#pragma once
#include <robin_hood.h>

#include <bf/all.hpp>
#include <vector>

#include "../utils/customAMQ.hpp"
#include "../utils/utils.hpp"
#include "../utils/file_manager.hpp"

template <typename T>
inline std::vector<bool> queryFilterOrTruth(const T& filterOrTruth, const std::string& s, const unsigned int& K, const unsigned int& z, unsigned long long& nbStretch) {
    const unsigned int k = K - z;
    unsigned long long size = s.size();
    std::vector<bool> response(size - K + 1, false);
    // unsigned long long i = 0;              // index of the response vector
    unsigned long long stretchLength = 0;  // number of consecutive positives kmers
    unsigned long long j = 0;              // index of the query vector
    bool extending_stretch = true;
    while (j < size - k + 1) {
        if (oneQuery(filterOrTruth, s.substr(j, k))){            
            stretchLength++;
            if (extending_stretch) j++;
            else {
                extending_stretch = true;
                j = j - z;
                nbStretch++;
            }
        }
        else{
            if (stretchLength >= z){
                for (unsigned long long t = j - stretchLength; t < j - z; t++) response[t] = true;
            }
            stretchLength = 0;
            extending_stretch = false;
            j = j + z + 1;
            
        }    
    }
    // Last values: 
    if (stretchLength >= z){
        for (unsigned long long t = size - k + 1 - stretchLength; t < size - K + 1; t++) response[t] = true;
    }

    return response;
}


unsigned long long get_nb_positions_covered(std::vector<bool> bv, const unsigned int k){
    long long nb_positions_covered = 0; // NB pos covered by at least one shared K-mer
    long long last_covered_position = -1; 
    long long  pos = 0;
    for (auto shared : bv) {
        if (shared){
            if (last_covered_position < pos){
                nb_positions_covered += k;
            }
            else{
                nb_positions_covered += pos - last_covered_position + k - 1;
            }
            
            last_covered_position = pos + k - 1;
            
        } 
        pos++;
    }
    return nb_positions_covered;
        
}
namespace findere {


std::vector<bool> inline query_one_sequence(const std::string& filename, const customAMQ& amq, const unsigned int& K, const unsigned long long& z) {
    
    unsigned long long dontCare = 0;
    FileManager read_files = FileManager ();

    read_files.addFile(filename);
    std::string & current_read = read_files.get_next_read();
    return queryFilterOrTruth(amq, current_read, K, z, dontCare);
}

void query_all(const std::string& filename, const customAMQ& amq, const unsigned int& K, const unsigned long long& z) {
    unsigned long long dontCare = 0;
    FileManager read_files = FileManager ();
    read_files.addFile(filename);
    
    std::string  current_read = read_files.get_next_read();


    while (!current_read.empty()) {
        std::string   current_data = read_files.get_data();
        std::string  current_header = current_data.substr(0,current_data.find('\n'));
        // Analyse the result of each query
        std::vector<bool> res = queryFilterOrTruth(amq, current_read, K, z, dontCare);
        long long nb_positions_covered = get_nb_positions_covered(res, K);
        float ratio = (100*nb_positions_covered)/float(current_read.length());
        if (ratio > 50){
            std::cout << current_header << "\n" << nb_positions_covered << " over "<<current_read.length()<<" :"<<ratio<<"%"<<std::endl;
        }
        current_read = read_files.get_next_read();
    } 
}



}  // namespace findere