#!/bin/bash

# Does a clean build of the compiler project.

# Remove cache (if built without this script)
./clean.sh

# Build project
cmake .
make all

echo "Done!"
