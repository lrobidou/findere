mkdir -p build
cd build
cmake ..
make -j4
cd ..
mkdir -p bin
cp build/src/paper bin/paper
cp build/src/paperFixedSize bin/paperFixedSize
cp build/src/query bin/query
cp build/src/index bin/index