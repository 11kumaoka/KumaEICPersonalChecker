rm -rf build/*
mkdir -p build
cd build
cmake ..
make -j 8
./EventAna $1 $2
if [ -n "$2" ]; then
    mv "$2" ../output
else
    mv test.root ../output
fi
cd ..