#!/bin/sh

rm -rf ./build

 . /opt/fsl-imx-x11/4.1.15-2.0.0/environment-setup-cortexa7hf-neon-poky-linux-gnueabi

#export CC=/usr/bin/gcc
#export CFLAGS="-O3 -fno-omit-frame-pointer"
#export CXX=/usr/bin/g++
#export CXXFLAGS="-O3 -fno-omit-frame-pointer -felide-constructors -fno-exceptions -fno-rtti"

mkdir build/
mkdir build/bin
mkdir build/lib
cd build && cmake ../ && make
cd ../
