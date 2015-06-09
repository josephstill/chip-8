#!/bin/bash

cmake --version

if [ $? -ne 0 ]; then
    echo -e "CMake is required to build the project."
    exit 1
fi

cd build

echo "Creating build artifacts."
cmake ../source

if [ $? -ne 0 ]; then
   echo -e "There was an error executing CMake"
   exit 1 
fi

echo -e "Starting build."
make
