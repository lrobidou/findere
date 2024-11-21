# findere

[![License](http://img.shields.io/:license-affero-blue.svg)](http://www.gnu.org/licenses/agpl-3.0.en.html)



`findere` is a simple strategy for speeding up queries and for reducing false positive calls from any Approximate Membership Query data structure (AMQ). With no drawbacks (in particular no false positive), queries are two times faster with two orders of magnitudes less false positive calls.

<img src="paper_companion/HMP_analyses/fpr_wrt_z/fpr_simple.png" alt="fpr" width="600"/>

The `findere` implementation proposed here uses a Bloom filter as AMQ. It proposes a way to index and query Kmers from biological sequences (fastq or fasta, gzipped or not, possibly considering only canonical Kmers) or from any textual data. 

A library is proposed, hence `findere` can be easily adapted to any other AMQ, for any usage.

## Table of content
- [Install](#install)
  - [Dependencies](#dependencies)
  - [Install findere](#install-findere)
  - [Reproduce paper results](#reproduce-paper-results)
- [Running](#running)
  - [Overview](#overview)
  - [Exemple on natural text file](#exemple-on-natural-text-file)
  - [Usage on genomic data (fastq or fasta file)](#usage-on-genomic-data-fastq-or-fasta-file)
- [Using findere with a personnal Approximate Membership Query datastructure](#using-findere-with-a-personnal-approximate-membership-query-datastructure)
- [Contacts](#contacts)
- [Citation](#citation)
# Install

## Dependencies

You must first install zlib. It is likely to be already installed, if not you can try:
```bash
sudo apt update
sudo apt-cache search zlib # This is zlib1g-dev on Ubuntu 20.04.
sudo apt-get install zlib # or wathever you found with apt-cache search
```

## Install findere

```bash
git clone --recursive https://github.com/lrobidou/findere
cd findere
git submodule update --init --recursive
chmod +x build.sh
./build.sh
```

## Reproduce paper results
The paper results can be reproduced on the branch `paper`. 
Use only this branch (`git checkout paper` and latter `git submodule update --init --recursive`) in order to reproduce these results. Please use the `paper` branch only for this purpose as recent developments do not impact this branch.

# Running

**WARNING NOTE**: 
To date, the last version of the library we use for our Bloom filters has an unsolved bug (cf this [link](https://github.com/mavam/libbf/blob/5478275d8a4e9a5cc163b44c34517c515bd898ec/src/hash.cpp#L13)).

For a high value of K, the hash function of Bloom filters crash. Thus, we experienced problems with a value of k > 36. Be carefull that K-z must be <= 36. If (K, z) is (37, 0) or (38, 1), findere_index will throw an exception. If (K, z) is (37, 1) or (38, 2), everything will be fine. 

## Overview
```bash
# indexing files
./bin/findere_index -i <lists of files to index> -o <index_name> -b <size in bits> [ -K <K> -z <z> -t <type of data {bio/text}> -c ]

# querying a file
./bin/findere_query -i <index_name> -q <your query file> [ -t <{bio/text}> -c --threshold <threshold> ]
```

Type `./bin/findere_index -h` or `./bin/findere_query -h` for full list of options and default values.
## Exemple on natural text file
```bash
# indexing some texts
./bin/findere_index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.idx -K 31 -z 3 -b 10000000 -t text

# querying a text
./bin/findere_query -i poesie.idx -q data/texts/AndromaqueAndHorace.txt -t text
```

This outputs simply the number of shared K-mers.
```bash
File data/texts/AndromaqueAndHorace.txt shares 1509 31-mer(s) among 100509 with the indexed bank (poesie.idx)
```

The code may be modified in order to make further analyses using these shared K-mers.

## Usage on genomic data (fastq or fasta file)
We propose a simple use case of `findere` on any genomic data stored in `fasta` or `fastq` files (gzipped or not). Please consider this feature as a demonstrator of the `findere` potential application.

From a bank composed of a file or a set of files, each K-mer is indexed. No counting is made, and all K-mers are indexed, even those occurring only once. It is possible to consider the canonical version of the K-mers.

Once the index is created it can be queried with any `fasta` or `fastq` file (one unique file, gzipped or not). For each sequence (each read in the case of sequencing data), the percentage of positions of the sequence covered by at least one K-mer indexed in the bank is output. It is possible to output only sequences for which this percentage is higher than a user defined threshold (80% by default)

```bash
# Index a set of genomes in a ~120 Mo bloom filter.
./bin/findere_index -i "data/ecoli2.fasta","data/ecoli3.fasta","data/Listeria phage.fasta","data/Penicillium chrysogenum.fasta" -o indexFastas.idx -b 1000000000

# Query "reads_hmp.fasta"
./bin/findere_query -i indexFastas.idx -q data/reads_hmp.fasta --threshold 30
```

This Outputs the header of reads whose percentage of positions of the sequence covered by at least one shared K-mer is higher than the given threshold.

```
>HWUSI-EAS712_103029392:3:100:11031:6837/1
34 over 100 :34%
>HWUSI-EAS712_103029392:3:100:11077:11965/1
36 over 100 :36%
>HWUSI-EAS712_103029392:3:100:11315:8086/1
33 over 100 :33%
```

# Using findere with a personnal Approximate Membership Query datastructure

If you want to use `findere` on another data structure (say, cuckoo filter), here is how you can do it:

In `src/libraries/utils/customAMQ.hpp`, you can find the class:
```c++
class customAMQ {
   public:
    customAMQ() = default;
    virtual ~customAMQ() = default;

    virtual bool contains(const std::string& x) const {
        std::cerr << "Should never be called." << std::endl;
        exit(1);
        return false;
    };
}
```

Any class that inherits `customAMQ` can be use with `findere`. Just wrap your data structure in it, and you are done. An exemple can be find in the file `src/query.cpp`. Let's break it down:

You have to inherit customAMQ, so:
```c++
class bfAMQ : public customAMQ {
```
As a private member, place your data structure. If I want to wrap a bloom filter, I would do:
```c++
   private:
    // juste one inner variable: the AMQ we are wrapping
    // (change this type depending on the data structure you want to use)
    bf::basic_bloom_filter* _bf;
```
Then, pass the data struture to your new object via the constructor:
```c++
   public:
    // pass the bloom filter to our constructor so wa can copy it and just store it
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
        //do nothing more
    }
```
Finally, expose a method `contains`, that takes a string as a parameter. This string is the kmer you'll want to query later:
```c++
    // finally, map the contains method to whatever the name of the method of our inner bloom filter
    bool contains(const std::string& x) const {
        // just pass the parameter to your amq
        return _bf->lookup(x);
    }

    //that's all folks
};
```
Done !

Now, before using `findere`, wrap your data structure.
Dont do:

```c++
std::vector<bool> response = findere::query(myFilterThatFindereDontKnowAnythingAboutfilter, querySeq, k, z);//findere can't handle it!
```
Do:
```c++
bfAMQ myAMQ = bfAMQ(myFilterThatFindereDontKnowAnythingAboutfilter);
std::vector<bool> response = findere::query(myAMQ, querySeq, k, z);
```

# Contacts

Lucas Robidou: lucas.robidou@inria.fr

Pierre Peterlongo: pierre.peterlongo@inria.fr

# Citation
Robidou, L., & Peterlongo, P. (2021). [findere: fast and precise approximate membership query](https://www.biorxiv.org/content/10.1101/2021.05.31.446182.full.pdf). In String Processing and Information Retrieval: 28th International Symposium, SPIRE 2021, Lille, France, October 4–6, 2021, Proceedings 28 (pp. 151-163). Springer International Publishing.

bibtex
```
@inproceedings{robidou2021findere,
  title={findere: fast and precise approximate membership query},
  author={Robidou, Lucas and Peterlongo, Pierre},
  booktitle={String Processing and Information Retrieval: 28th International Symposium, SPIRE 2021, Lille, France, October 4--6, 2021, Proceedings 28},
  pages={151--163},
  year={2021},
  organization={Springer}
}
```
