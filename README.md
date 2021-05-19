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
Exemple:
```
./build/src/index -i data/texts/contemplations.txt,data/texts/Horace.txt,data/texts/Le_Cid.txt,data/texts/Maastricht.txt,data/texts/Othon.txt,data/texts/Lettres_persanes.txt -o poesie.bin -k 31 -z 5 --epsilonpercent 8 -t text
./build/src/query -i poesie.bin -q data/texts/AndromaqueAndHorace.txt -k 31 -z 5 -t text
```


