cmake_minimum_required(VERSION 3.15)
project(data_mapping)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_executable(data_mapping 
    src/main.cpp
    src/utils.cpp
)