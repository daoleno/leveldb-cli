cmake_minimum_required(VERSION 3.10)
project(leveldb-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(leveldb-cli
    src/db.h
    src/db.cc
    src/util.h
    src/util.cc
    src/leveldb_cli.cc
)
target_compile_options(leveldb-cli PRIVATE -Wall)

find_library(libleveldb leveldb /usr/local/lib)
target_link_libraries(leveldb-cli ${libleveldb})
