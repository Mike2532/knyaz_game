#!/bin/bash

set -e

clear
mkdir -p build
cd ./build
cmake ..
cmake --build .
./src/mainGame