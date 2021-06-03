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

#ifndef __FASTQ_FILE_H__
#define __FASTQ_FILE_H__

#include "read_file.hpp"

#include <fstream>
#include <zlib.h>

////////////////////////////////////////////////////////////
// This class is used to read a FASTQ file
//
class FastqFile : public ReadFile
{
private:
	std::ifstream infile;
	std::string tmp_str;
public:
	
	////////////////////////////////////////////////////////////
	// Open the file, count reads and set boolean vector to 1
	//
	explicit FastqFile (const std::string & file_name)
	{
		//std::cerr << "Open FASTQ\n";
		fname = file_name;
		// Open the file
		infile.open (file_name.c_str());
		if (!infile.good()) {
			std::cerr << "Error: Cannot open Fastq File " << file_name << "\n";
			exit(1);
		}
		// Count reads
		//const clock_t begin_time = clock();
		nb_reads = 0;
		while (infile.good()) {
			getline (infile, tmp_str);
			if (!tmp_str.empty()) {
				nb_reads++;
			}
		}
		nb_reads = nb_reads / 4;
		rewind();
		//std::cerr << "Count " << nb_reads << " reads in " << float( clock () - begin_time ) / CLOCKS_PER_SEC << " s\n";
		// Set boolean vector to 1
		current_read_pos = 0;

		first_read = true;
	}
	
	
	
	////////////////////////////////////////////////////////////
	// Destructor only closes the file
	//
	~FastqFile () {
		infile.close();
	}
	
	
	////////////////////////////////////////////////////////////
	// get_next_read returns the next read in the file
	// OR an empty string if no more read is available
	//
	std::string & get_next_read () {
		// clear data and increment the position
		if (!first_read) {
			current_read_pos++;
		} else {
			first_read = false;
		}
		current_read_data.clear();
		current_read_seq.clear();
		
			// The current read is 1 in the boolean vector
			// Or current_read_pos >= nb_reads -> end of file
			if (current_read_pos < nb_reads) {
				// Read the first line of FASTQ entry -> "@sequence comment"
				if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
					getline (infile, tmp_str);
					while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
						getline (infile, tmp_str);
					}
					current_read_data += tmp_str + "\n";
				} else {
					return current_read_seq;
				}
				// Read the second line of FASTQ entry -> sequence of the read
				if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
					getline (infile, current_read_seq);
					while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
						getline (infile, tmp_str);
					}
					current_read_data += current_read_seq + "\n";
				} else {
					return current_read_seq;
				}
				// Read the third line of FASTQ entry -> "+quality comment"
				if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
					getline (infile, tmp_str);
					while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
						getline (infile, tmp_str);
					}
					if (tmp_str[0] != '+') {
						std::cerr << "Error\n";
					}
					current_read_data += tmp_str + "\n";
				} else {
					current_read_seq.clear();
					current_read_data.clear();
					return current_read_seq;
				}
				// Read the fourth line of FASTQ entry -> "quality sequence"
				if (infile.good()) {
					getline (infile, tmp_str);
					while (tmp_str.empty() && infile.good()) {
						getline (infile, tmp_str);
					}
					current_read_data += tmp_str + "\n";
				} else {
					current_read_seq.clear();
					current_read_data.clear();
				}
			}
		
		return current_read_seq;
	}
	
	
	////////////////////////////////////////////////////////////
	// Just read the next four lines without storing them
	//
	void flush_next_read () {
		current_read_data.clear();
		current_read_seq.clear();
		if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
			getline (infile, tmp_str);
			while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
				getline (infile, tmp_str);
			}
		}
		if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
			getline (infile, tmp_str);
			while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
				getline (infile, tmp_str);
			}
		}
		if (infile.good() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
			getline (infile, tmp_str);
			while (tmp_str.empty() && infile.peek() != (int) std::char_traits<wchar_t>::eof()) {
				getline (infile, tmp_str);
			}
		}
		if (infile.good()) {
			getline (infile, tmp_str);
			while (tmp_str.empty() && infile.good()) {
				getline (infile, tmp_str);
			}
		}
	}
	
	
	////////////////////////////////////////////////////////////
	// Return the full FASTQ entry of the current read
	//
	const std::string & get_data() const
	{
		return current_read_data;
	}
	
	
	////////////////////////////////////////////////////////////
	// Return the sequence of the current read
	//
	const std::string & get_read() const
	{
		return current_read_seq;
	}
	
	
	
	
	////////////////////////////////////////////////////////////
	// Go to the beginning of the file -> current_read_pos = -1
	// because no read has been read
	//
	void rewind () {
		infile.clear();
		infile.seekg(0);
		current_read_pos = 0;
		first_read = true;
	};
	
	
	////////////////////////////////////////////////////////////
	// Save the selected reads in a given file name
	//
	void save (const std::string & directory, const std::string & suffix) {
		std::string output_file_name = directory + "/" + fname.substr(fname.rfind("/") + 1)  + "_in_" + suffix+ ".fq";
		rewind();
		std::ofstream outfile;
		outfile.open (output_file_name.c_str());
		if (!outfile.good()) {
			std::cerr << "Cannot write on file " << output_file_name << "\n";
			exit(1);
		}
		std::string & current_read = get_next_read();
		while (!current_read.empty()) {
			outfile << get_data();
			current_read = get_next_read();
		}
		outfile.close();
	}
};

class GzFastqFile : public ReadFile  {
private:
	gzFile infile;
	static const int NORMALSIZEREAD = 1048576;
	char tmp_str[NORMALSIZEREAD];
public:
	////////////////////////////////////////////////////////////
	// Open the file, count reads and set boolean vector to 1
	//
	explicit GzFastqFile (const std::string & file_name)
	{
		//std::cerr << "Add Gzip Fastq File " << file_name << "\n";
		fname = file_name;
		// Open the file
		infile = (gzFile) gzopen (file_name.c_str(), "r");
		if (infile == NULL) {
			std::cerr << "Error: Cannot open Fasta File " << file_name << "\n";
			exit(1);
		}
		// Count reads
		//const clock_t begin_time = clock();
		nb_reads = 0;
		while (gzgets(infile, tmp_str, NORMALSIZEREAD) != NULL) {
			if (tmp_str[0] != '\0') {
				nb_reads++;
			}
		}
		nb_reads = nb_reads / 4;
		rewind();
		//std::cerr << "Count " << nb_reads << " reads in " << float( clock () - begin_time ) / CLOCKS_PER_SEC << " s\n";
		// Set boolean vector to 1
		current_read_pos = 0;
		
		first_read = true;
		
	}
	
		
	
	////////////////////////////////////////////////////////////
	// Destructor only closes the file
	//
	~GzFastqFile () {
		gzclose(infile);
	}
	
	
	////////////////////////////////////////////////////////////
	// get_next_read returns the next read in the file
	// OR an empty string if no more read is available
	//
	std::string & get_next_read () {
		// clear data and increment the position
		if (!first_read) {
			current_read_pos++;
		} else {
			first_read = false;
		}
		current_read_data.clear();
		current_read_seq.clear();
		
			
			// The current read is 1 in the boolean vector
			// Or current_read_pos >= nb_reads -> end of file
			if (current_read_pos < nb_reads) {
				// Read the first line of FASTQ entry -> "@sequence comment"
				if (!gzeof(infile)) {
					gzgets(infile, tmp_str, NORMALSIZEREAD);
					while (tmp_str[0] == '\0' && !gzeof(infile)) {
						gzgets(infile, tmp_str, NORMALSIZEREAD);
					}
					current_read_data += std::string(tmp_str);
					if (current_read_data[current_read_data.size() - 1] != '\n') {
						current_read_data += '\n';
					}
				} else {
					return current_read_seq;
				}
				// Read the second line of FASTQ entry -> sequence of the read
				if (!gzeof(infile)) {
					gzgets(infile, tmp_str, NORMALSIZEREAD);
					while (tmp_str[0] == '\0' && !gzeof(infile)) {
						gzgets(infile, tmp_str, NORMALSIZEREAD);
					}
					current_read_seq = tmp_str;
					current_read_seq = current_read_seq.substr(0, current_read_seq.size() - 1);
					current_read_data += current_read_seq;
					if (current_read_data[current_read_data.size() - 1] != '\n') {
						current_read_data += '\n';
					}
				} else {
					return current_read_seq;
				}
				// Read the third line of FASTQ entry -> "+quality comment"
				if (!gzeof(infile)) {
					gzgets(infile, tmp_str, NORMALSIZEREAD);
					while (tmp_str[0] == '\0' && !gzeof(infile)) {
						gzgets(infile, tmp_str, NORMALSIZEREAD);
					}
					current_read_data += std::string(tmp_str);
					if (current_read_data[current_read_data.size() - 1] != '\n') {
						current_read_data += '\n';
					}
				} else {
					current_read_seq.clear();
					current_read_data.clear();
					return current_read_seq;
				}
				// Read the fourth line of FASTQ entry -> "quality sequence"
				if (!gzeof(infile)) {
					gzgets(infile, tmp_str, NORMALSIZEREAD);
					while (tmp_str[0] == '\0' && !gzeof(infile)) {
						gzgets(infile, tmp_str, NORMALSIZEREAD);
					}
					current_read_data += std::string(tmp_str);
					if (current_read_data[current_read_data.size() - 1] != '\n') {
						current_read_data += '\n';
					}
				} else {
					current_read_seq.clear();
					current_read_data.clear();
				}
			}
		
		return current_read_seq;
	}
	
	
	////////////////////////////////////////////////////////////
	// Just read the next four lines without storing them
	//
	void flush_next_read () {
		current_read_data.clear();
		current_read_seq.clear();
		if (!gzeof(infile)) {
			gzgets(infile, tmp_str, NORMALSIZEREAD);
			while (tmp_str[0] == '\0' && !gzeof(infile)) {
				gzgets(infile, tmp_str, NORMALSIZEREAD);
			}
		}
		if (!gzeof(infile)) {
			gzgets(infile, tmp_str, NORMALSIZEREAD);
			while (tmp_str[0] == '\0' && !gzeof(infile)) {
				gzgets(infile, tmp_str, NORMALSIZEREAD);
			}
		}
		if (!gzeof(infile)) {
			gzgets(infile, tmp_str, NORMALSIZEREAD);
			while (tmp_str[0] == '\0' && !gzeof(infile)) {
				gzgets(infile, tmp_str, NORMALSIZEREAD);
			}
		}
		if (!gzeof(infile)) {
			gzgets(infile, tmp_str, NORMALSIZEREAD);
			while (tmp_str[0] == '\0' && !gzeof(infile)) {
				gzgets(infile, tmp_str, NORMALSIZEREAD);
			}
		}
	}
	
	
	////////////////////////////////////////////////////////////
	// Return the full FASTQ entry of the current read
	//
	const std::string & get_data() const
	{
		return current_read_data;
	}
	
	
	////////////////////////////////////////////////////////////
	// Return the sequence of the current read
	//
	const std::string & get_read() const
	{
		return current_read_seq;
	}
	
	
	////////////////////////////////////////////////////////////
	// Go to the beginning of the file -> current_read_pos = -1
	// because no read has been read
	//
	void rewind () {
		gzclose(infile);
		infile = (gzFile) gzopen (fname.c_str(), "r");
		if (infile == NULL) {
			std::cerr << "Error: Cannot open Fasta File " << fname << "\n";
			exit(1);
		}
		current_read_pos = 0;
		first_read = true;
	};
	
	

};

#endif
