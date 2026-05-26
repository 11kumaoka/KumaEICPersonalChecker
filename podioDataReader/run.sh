rm -rf build/*
mkdir -p build
cd build
cmake ..
make -j 8
./EventAna $1 $2
mv *.root ../output
cd ..