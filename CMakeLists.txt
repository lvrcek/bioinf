cmake_minimum_required(VERSION 2.8)
project(bioinf)

#set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/cuckoo.h src/vector_table.h src/file_reader.h)


set (Cuckoo_M "(1<<19)")
set (Cuckoo_B 8)
set (Cuckoo_N 1000000)
set (Cuckoo_F 8)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/constants.h.in"
	"${PROJECT_BINARY_DIR}/src/constants.h"
)


add_executable(test_file examples/example_file.cpp)
add_executable(test_int examples/example.cpp)

add_library(cuckoo_lib src/constants.h src/main.cpp src/cuckoo.h src/vector_table.h src/file_reader.h)

target_link_libraries(test_int cuckoo_lib)
target_link_libraries(test_file cuckoo_lib)
