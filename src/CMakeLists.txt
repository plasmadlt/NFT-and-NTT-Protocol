cmake_minimum_required(VERSION 3.5)
project(tassets VERSION 0.0.1 LANGUAGES CXX)

find_package(ion.cdt CONFIG REQUIRED)
message("Found CDT package at: ${ION_CDT_ROOT}")

include_directories(${ION_CDT_ROOT}/include/ionlib/capi/)
include_directories(${ION_CDT_ROOT}/include/ionlib/contracts/)
include_directories(${ION_CDT_ROOT}/include/ionlib/core/)
include_directories(${ION_CDT_ROOT}/include/ionlib/native/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Generate the wasm and abi
add_contract(tassets tassets tassets.hpp tassets.cpp)
