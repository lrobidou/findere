# qtf

Query-Time Filtration source repository

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
./build/src/main
```


