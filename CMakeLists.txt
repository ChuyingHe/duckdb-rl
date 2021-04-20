cmake_minimum_required(VERSION 3.17)
project(duckdb_rl)

set(CMAKE_CXX_STANDARD 17)
MESSAGE(STATUS ${SRC_LIST})

include_directories(${CMAKE_SOURCE_DIR}/dependencies/libduckdb-src) # duckdb

add_executable(duckdb_rl main.cpp dependencies/libduckdb-src/duckdb.cpp imdb_constants.hpp timer.cpp)