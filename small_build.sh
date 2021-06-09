
cd build

make -j4
cd ..

cp build/src/paper bin/paper 2>/dev/null || :
cp build/src/paperFixedSize bin/paperFixedSize 2>/dev/null || :
cp build/src/paperKVariation bin/paperKVariation 2>/dev/null || :
cp build/src/paperFixedSize bin/paperFixedSize 2>/dev/null || :
cp build/src/paperNaturalText bin/paperNaturalText 2>/dev/null || :
cp build/src/paperNaturalTextTime bin/paperNaturalTextTime 2>/dev/null || :
cp build/src/query bin/findere_query
cp build/src/index bin/findere_index