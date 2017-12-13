cmake_minimum_required(VERSION 3.8)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src src/main.cpp)
add_executable(bioinf ${SOURCE_FILES})