cmake_minimum_required(VERSION 3.8)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/constants.h src/main.cpp src/cuckoo.h src/vector_table.h src/file_reader.h)
add_executable(bioinf ${SOURCE_FILES})