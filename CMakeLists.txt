cmake_minimum_required(VERSION 3.28)
project(vape-compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(vape-compiler ./main.cpp ./src/heap.cpp)
target_include_directories(vape-compiler PUBLIC ./include)
