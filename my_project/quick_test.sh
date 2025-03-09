#!/bin/bash

# Check if the app exists
if [ ! -d "build/tests/MyTests" ]; then
    ./build/tests/MyTests
else echo ”tests not built yet“
fi



