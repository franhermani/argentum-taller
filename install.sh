#!/usr/bash

echo "Installing libraries..."
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev

echo "Creating build directory... OK"
rm -rf build
mkdir -p build

echo "Switching to build directory... OK"
cd build

echo "Building project..."
cmake ..

echo "Building targets..."
make