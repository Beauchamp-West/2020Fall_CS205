cmake_minimum_required(VERSION 3.17)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(Project2
        cnn.cpp
        main.cpp)

target_link_libraries(Project2 ${OpenCV_LIBS})