# findere

findere source repository

# Installation and execution
## Installation
You must first install zlib. It is likely to be already installed, if not you can try:
```
sudo apt update
sudo apt-cache search zlib
sudo apt-get install zlib # or wathever you found with apt-cache search
```

```
git clone --recursive https://github.com/lrobidou/findere
cd findere
git submodule update --init --recursive
chmod +x build.sh
./build.sh
```
## Execution
```
./build/src/index -i <lists of files to index> -o <index output> -k <k> -z <z> --epsilonpercent <epsilon in percent> -t <type of data you want to index>
./build/src/query -i <the index> -q <your query file> -k <k> -z <z> -t <type of data you indexed>
```
### Exemple on texts:
```
./build/src/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -k 31 -z 5 --epsilonpercent 8 -t text
./build/src/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -k 31 -z 5 -t text
```

### Execution on fastas:
```
./bin/index -i "data/ecoli2.fasta","data/ecoli3.fasta","data/Listeria phage.fasta","data/Penicillium chrysogenum.fasta" -o indexFastas -K 31 -z 3 --epsilonpercent 5 -t fasta
./bin/query -i indexFastas -q data/Listeria\ phage.fasta -K 31 -z 3 -t fasta
```


## Sweet, but I already have a great data structure. How can I use `findere` to query it ?

If you want to use `findere` on another data structure (say, cuckoo filter), here is how you can do it:

In `src/libraries/utils/customAMQ.hpp`, you can find the class:
```
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

Any class that inherits `customAMQ` can be use with `findere`.Just wrap your data structure in it, and you are done. An exemple can be find in the file `src/query.cpp`. Let's break it down:

You have to inherit customAMQ, so:
```
class bfAMQ : public customAMQ {
```
As a private member, place your data structure. If I want to wrap a bloom filter, I would do:
```
   private:
    // juste one inner variable: the AMQ we are wrapping
    // (change this type depending on the data structure you want to use)
    bf::basic_bloom_filter* _bf;
```
Then, pass the data struture to your new object via the constructor:
```
   public:
    // pass the bloom filter to our constructor so wa can copy it and just store it
    bfAMQ(bf::basic_bloom_filter* bf) : _bf(bf) {
        //do nothing more
    }
```
Finally, expose a method `contains`, that takes a string as a parameter. This string is the kmer you'll want to query later:
```
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
```
std::vector<bool> response = QTF::query(myFilterThatFindereDontKnowAnythingAboutfilter, querySeq, k, z);//findere can't handle it!
```
Do:
```
bfAMQ myAMQ = bfAMQ(myFilterThatFindereDontKnowAnythingAboutfilter);
std::vector<bool> response = QTF::query(myAMQ, querySeq, k, z);
```
