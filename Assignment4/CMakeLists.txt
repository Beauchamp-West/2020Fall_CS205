cmake_minimum_required(VERSION 3.17)
project(Assignment4)

set(CMAKE_CXX_STANDARD 14)

IF(APPLE)
    set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc/10.2.0/bin/g++-10)
    set(CMAKE_CXX_FLAGS "-std=c++11 -mavx2 -fopenmp -O3")
ELSEIF(LINUX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -fopenmp -mfpu=neon")
ENDIF()

add_executable(Project main.cpp matrix.cpp matrix.hpp)