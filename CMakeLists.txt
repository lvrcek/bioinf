cmake_minimum_required(VERSION 3.8)
project(bioinf)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/constants.h src/cuckoo.h src/vector_table.h src/file_reader.h)

add_executable(test_file examples/example_file.cpp)
add_executable(test_int examples/example.cpp)

add_library(cuckoo_lib src/constants.h src/main.cpp src/cuckoo.h src/vector_table.h src/file_reader.h)

target_link_libraries(test_int cuckoo_lib)
target_link_libraries(test_file cuckoo_lib)