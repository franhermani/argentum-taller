#!/usr/bash

echo "Creating build directory... OK"
rm -rf build
mkdir -p build

echo "Switching to build directory... OK"
cd build

echo "Building project..."
cmake ..

echo "Building targets..."
make