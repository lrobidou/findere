# Usability of `findere` on natural language. 

Here, we show that `findere` works not only on genomic sequences, but also on natural language.

We propose to index some french poems along with the Maastricht Treaty (because poems are a bit short, so the index would be ridiculously small without the Treaty).
We propose to index those files with K=31 and z=5.

As a query, we propose another poem (`Andromaque`), in which we inserted some lines of a poem we index (namely `Horace`). Then , we let `findere` query (`Andromaque`) and retrieve common sequence with the index (i.e. the verse of `Horace`).

The poems come from wikisource (https://fr.wikisource.org).

The result on natural language was obtained at the commit: 1dead79779c3dc61c803f51509f1d85aa9828555


# Steps to reproduce:
## install findere at the right commit:
```
git clone --recursive https://github.com/lrobidou/findere
cd findere

git checkout 1dead79779c3dc61c803f51509f1d85aa9828555  # important

git submodule update --init --recursive  # also impotant (even if you already did it before), as git won't update the submodule when you checkout
chmod +x build.sh
./build.sh
```


## use findere to reproduce the result
### index and save the index on your disk
```
./bin/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -K 31 -z 5 --epsilonpercent 8 -t text
```
### query the saved index
```
./bin/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -K 31 -z 5
```
This will print the following:
```
"TP": 1188,
"TN": 99318,
"FP": 3,
"FN": 0,

"FPR": 0.00302051,
"FNR": 0
```

You can disable findere by choosing z=0:
```
./bin/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -K 31 -z 0 --epsilonpercent 8 -t text
./bin/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -K 31 -z 0
```
Expected output:
```
"TP": 1188,
"TN": 91429,
"FP": 7892,
"FN": 0,

"FPR": 7.94595,
"FNR": 0
```
This way, the FPR goes close to epsilonpercent.
