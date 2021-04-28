cmake_minimum_required(VERSION 3.17)
project(duckdb_rl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

MESSAGE(STATUS ${SRC_LIST})

include_directories(${CMAKE_SOURCE_DIR}/dependencies/libduckdb-src) # duckdb - be able to use #include "duckdb.hpp"

add_executable(duckdb_rl main.cpp dependencies/libduckdb-src/duckdb.cpp imdb_constants.hpp timer.cpp)