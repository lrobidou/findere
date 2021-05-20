# Usability of `findere` on natural language. 

Here, we show that `findere` works not only on genomic sequences, but also on natural language.

We propose to index some french poems along with the Maastricht Treaty (because poems are a bit short, so the index would be ridiculously small without the Treaty).
We propose to index those files with K=31 and z=5.

As a query, we propose another poem (`Andromaque`), in which we inserted some lines of a poem we index (namely `Horace`). Then , we let `findere` query (`Andromaque`) and retrieve common sequence with the index (i.e. the verse of `Horace`).

The poems come from wikisource (https://fr.wikisource.org).

The result on natural language was obtained at the commit: adc5d037c0be76c75cba0ed2a8f2e613f03a4182


## Steps to reproduce:
### Install findere using a specific commit, dedicated to FPrate computation

```
git clone --recursive https://github.com/lrobidou/findere
cd findere

git checkout 1dead79779c3dc61c803f51509f1d85aa9828555  # important

git submodule update --init --recursive  # also impotant (even if you already did it before), as git won't update the submodule when you checkout
chmod +x build.sh
./build.sh
```


### Tests on small datasets (included in the git repository)
##### index and save the index on your disk
```
./bin/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -K 31 -z 3 --epsilonpercent 5 -t text
```
##### query the saved index
```
./bin/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -K 31 -z 3
```
Result: XXX

"TP": 1490,
"TN": 99018,
"FP": 1,
"FN": 0,
"FPR": 0.00100991,
"FNR": 0

#### Same tests with classical bloom filter (equivalent to z=0)

```
./bin/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -K 31 -z 0 --epsilonpercent 5 -t text
./bin/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -K 31 -z 0
```
Results:  

"TP": 1490,
"TN": 94157,
"FP": 4862,
"FN": 0,
"FPR": 4.91017,
"FNR": 0

This way, the FPR goes close to epsilonpercent.



## Tests on larger corpus.

We propose a test based on a larger corpus composed of a subset of wikipedia data. 

#### Get the data

We followed instruction indicated here: https://www.kdnuggets.com/2017/11/building-wikipedia-text-corpus-nlp.html

Here are the full commands:

```bash
# Download xml file
wget https://dumps.wikimedia.org/enwiki/latest/enwiki-latest-pages-articles1.xml-p1p41242.bz2
# Generate a .txt file
python make_corpus.py enwiki-latest-pages-articles1.xml-p1p41242.bz2 enwiki-latest-pages-articles1.txt # stopped after generating 250 MB of data
# Generate a first subset of the first 100M from the so created file: 
head -c 104857600 enwiki-latest-pages-articles1.txt > enwiki-latest-pages-articles1_head100M.txt
# Generage a second subset of 100M from the file with an overlap of 10M with enwiki-latest-pages-articles1_head100M.txt
head -c 199715200 enwiki-latest-pages-articles1.txt |tail -c 104857600 > enwiki-latest-pages-articles1_next100M.txt
```

#### Result from a classical bloom filter (using z=0):

```bash
./bin/index -i enwiki-latest-pages-articles1_head100M.txt -o enwiki-latest-pages-articles1_head100M_z0.bin -K 31 -z 0 --epsilonpercent 5 -t text
./bin/query -i enwiki-latest-pages-articles1_head100M_z0.bin -q enwiki-latest-pages-articles1_next100M.txt -K 31 -z 0		
```

​      "TP": 12026785,

​      "TN": 88182952,

​      "FP": 4642949,

​      "FN": 0,

​      "FPR": 5.00178,

​      "FNR": 0

#### Result with findere (using z=3):

```bash

./bin/index -i enwiki-latest-pages-articles1_head100M.txt -o enwiki-latest-pages-articles1_head100M.bin -K 31 -z 3 --epsilonpercent 5 -t text
./bin/query -i enwiki-latest-pages-articles1_head100M.bin -q enwiki-latest-pages-articles1_next100M.txt -K 31 -z 3
```

​      "TP": 12026785,

​      "TN": 92745136,

​      "FP": 80765,

​      "FN": 0,

​      "FPR": 0.087007,

​      "FNR": 0

