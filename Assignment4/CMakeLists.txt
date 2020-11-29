cmake_minimum_required(VERSION 3.17)
project(Assignment4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc/10.2.0/bin/g++-10)
set(CMAKE_CXX_FLAGS "-mavx2 -fopenmp -O3")

add_executable(Project main.cpp matrix.cpp matrix.hpp)