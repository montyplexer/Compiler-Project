#!/bin/bash

# Cleans the compiler project of non-source files.

# Remove cache in ./
rm -r "CMakeFiles"
rm "cmake_install.cmake"
rm "Makefile"
rm "CMakeCache.txt"

# Remove cache and library in ./src
rm -r "src/CMakeFiles"
rm "src/cmake_install.cmake"
rm "src/Makefile"
rm src/*.a

# Remove cache and exe's in ./exe
rm -r "exe/CMakeFiles"
rm "exe/cmake_install.cmake"
rm "exe/Makefile"
rm exe/*.exe

echo "Done!"
