#!/bin/bash

mkdir -p cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=debug -DCXX_COMPILER=g++ -G "CodeBlocks - Unix Makefiles" ..

cd ..
mkdir -p cmake-build-release-clang
cd cmake-build-release-clang
cmake -DCMAKE_BUILD_TYPE=release-clang -DCXX_COMPILER=clang++ -G "CodeBlocks - Unix Makefiles" ..

cd ..
mkdir -p cmake-build-release-gcc
cd cmake-build-release-gcc
cmake -DCMAKE_BUILD_TYPE=release-gcc -DCXX_COMPILER=g++ -G "CodeBlocks - Unix Makefiles" ..

