cmake_minimum_required(VERSION 3.8)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src src/main.cpp src/CuckooFilter.cpp src/CuckooFilter.h src/Table.cpp src/Table.h src/FileReader.cpp src/FileReader.h)
add_executable(bioinf ${SOURCE_FILES})