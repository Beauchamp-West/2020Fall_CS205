cmake_minimum_required(VERSION 3.17)
project(Assignments)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR /usr/local/Cellar/openblas/0.3.10_1/include)
set(LINK_DIR /usr/local/Cellar/openblas/0.3.10_1/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(openblas)

add_executable(Assignments
        dotProduct.cpp)
target_link_libraries(Assignments openblas)
