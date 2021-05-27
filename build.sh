mkdir -p build
cd build
cmake ..
make -j4
cd ..
mkdir -p bin
cp build/src/paper bin/paper
cp build/src/paperFixedSize bin/paperFixedSize
cp build/src/paperKVariation bin/paperKVariation
cp build/src/paperFixedSize bin/paperFixedSize
cp build/src/paperNaturalText bin/paperNaturalText
cp build/src/paperNaturalTextTime bin/paperNaturalTextTime
cp build/src/query bin/findere_query
cp build/src/index bin/findere_index