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
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../source
make 
