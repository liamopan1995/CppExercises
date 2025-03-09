#!/bin/bash

# Check if the 'build' directory exists
if [ ! -d "build" ]; then
    mkdir build  # Create build directory if it doesn't exist
fi

cd build

# Run cmake and make
cmake .. && make
