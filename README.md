# qtf

Query-Time Filtration source repository

# Installation

<!-- ## install CRoaring
git clone https://github.com/RoaringBitmap/CRoaring
cd CRoaring
mkdir build
cd build
cmake ..
make
sudo make install


## install sdsl
git clone https://github.com/simongog/sdsl-lite.git
cd sdsl-lite
sudo ./install.sh /usr/local/ -->
```
git submodule add https://github.com/jarro2783/cxxopts thirdparty/cxxopts
git submodule add https://github.com/martinus/robin-hood-hashing thirdparty/robinHoodHashing
```


## install libbf
```
git clone https://github.com/mavam/libbf
git checkout v1.0.0
./configure
make
sudo make install
```




## install QTF
### build QTF
```
git clone --recursive https://gitlab.inria.fr/lrobidou/qtf
cd qtf
chmod +x build.sh
./build.sh
```

### execute QTF
```
./build/src/main
```


