/*
 * Contributors :
 *   Pierre PETERLONGO, pierre.peterlongo@inria.fr [12/06/13]
 *   Nicolas MAILLET, nicolas.maillet@inria.fr     [12/06/13]
 *   Guillaume Collet, guillaume@gcollet.fr        [27/05/14]
 *
 * This software is a computer program whose purpose is to find all the
 * similar reads between two set of NGS reads. It also provide a similarity
 * score between the two samples.
 *
 * Copyright (C) 2014  INRIA
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "fasta_file.hpp"
#include "fastq_file.hpp"

class FileManager {
   protected:
    std::string nickname;
    std::string sum_of_file_names;
    std::vector<std::string> file_names;
    std::vector<ReadFile *> files;
    int current_file;
    unsigned long nb_seen_reads;  // Count the number of reads that have been returned by get_next_read
   public:
    // Constructor
    FileManager() {
        current_file = -1;
        nb_seen_reads = 0;
    }

    // Destructor
    virtual ~FileManager() {
        for (std::vector<ReadFile *>::iterator it = files.begin(); it != files.end(); it++) {
            delete *it;
        }
    }

    // Get the next read in the current file or try next file if no more read in current file
    // If no more file, return an empty read
    virtual std::string &get_next_read() {
        if (current_file >= (int)files.size()) {
            nb_seen_reads++;
            return files[current_file - 1]->get_next_read();
        }
        std::string &tmp_read = files[current_file]->get_next_read();
        while (tmp_read.empty()) {
            current_file++;
            if (current_file >= (int)files.size()) {
                break;
            }
            tmp_read = files[current_file]->get_next_read();
        }
        nb_seen_reads++;
        return tmp_read;
    }

    const unsigned long get_reads_seen() const { return nb_seen_reads; };

    // Add a file to the FileManager
    virtual void addFile(const std::string &file_name) {
        // Open the given file to check its type (fasta, fastq, gzip ?)
        std::ifstream infile;
        infile.open(file_name.c_str());
        if (!infile.good()) {
            std::cerr << "Cannot open file file " << file_name << " -> ignore\n";
        }
        // Check the first char
        char c = infile.get();
        // Fasta file
        if (c == '>') {
            infile.close();
            files.push_back(new FastaFile(file_name));
        }
        // Fastq file
        else if (c == '@') {
            infile.close();
            files.push_back(new FastqFile(file_name));
        }
        // Gzip file
        else {
            infile.close();
            gzFile tmp_gz_file = (gzFile)gzopen(file_name.c_str(), "r");
            if (!tmp_gz_file) {
                std::cerr << "Cannot open file " << file_name << " -> ignore\n";
                exit(1);
            }
            c = gzgetc(tmp_gz_file);
            // Fasta file
            if (c == '>') {
                gzclose(tmp_gz_file);
                files.push_back(new GzFastaFile(file_name));
            }
            // Fastq file
            else if (c == '@') {
                gzclose(tmp_gz_file);
                files.push_back(new GzFastqFile(file_name));
            } else {
                std::cerr << "Unknown format: " << file_name << " -> ignore\n";
            }
        }
        file_names.push_back(file_name);
        if (sum_of_file_names.empty()) {
            sum_of_file_names = file_name.substr(file_name.rfind("/") + 1);
        } else {
            sum_of_file_names += "-" + file_name.substr(file_name.rfind("/") + 1);
        }
        if (current_file < 0) {
            current_file = 0;
        }
    }

    bool is_empty() {
        return files.empty();
    }

    void set_nickname(const std::string &str) { nickname = str; }
    const std::string &get_nickname() const { return nickname; }

    virtual void rewind() {
        current_file = 0;
        nb_seen_reads = 0;
        for (std::vector<ReadFile *>::iterator it = files.begin(); it != files.end(); it++) {
            (*it)->rewind();
        }
    }

    const std::string &get_data() const { return files[current_file]->get_data(); }

    const std::string &get_sum_of_file_names() const { return sum_of_file_names; }

    const std::vector<std::string> &get_file_names() const { return file_names; }
};

#endif
