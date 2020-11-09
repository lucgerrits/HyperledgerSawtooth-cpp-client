#!/bin/bash

git submodule update --init --recursive


echo "Start: Make Secp256k1"
cd secp256k1/
./autogen.sh
./configure
make
cd ..
echo "Done: Make Secp256k1"


echo "Start: Make cryptopp"
cd cryptopp/
make
cd ..
echo "Done: Make cryptopp"

echo "Start: Make protobuf"
cd protobuf/
git submodule update --init --recursive
./autogen.sh
./configure --prefix=$(pwd)/.libs/ --disable-shared
make
make install
cd ..
echo "Done: Make protobuf"
