project(compiler_project)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)

# Source files
add_subdirectory(src)
add_subdirectory(exe)

if(EXISTS ${PROJECT_SOURCE_DIR}/test)
    add_subdirectory(test)
endif(EXISTS ${PROJECT_SOURCE_DIR}/test)



