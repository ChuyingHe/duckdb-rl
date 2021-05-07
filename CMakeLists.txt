cmake_minimum_required(VERSION 3.16)
project(duckdb_rl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

MESSAGE(STATUS ${SRC_LIST})

include_directories(${CMAKE_SOURCE_DIR}/dependencies/libduckdb-src) # duckdb - be able to use #include "duckdb.hpp"

add_executable(duckdb_rl main.cpp dependencies/libduckdb-src/duckdb.cpp imdb_constants.hpp)

# find threads library
find_package(Threads REQUIRED)
target_link_libraries(duckdb_rl PRIVATE Threads::Threads)

