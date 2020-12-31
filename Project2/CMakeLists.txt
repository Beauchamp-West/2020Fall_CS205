cmake_minimum_required(VERSION 3.17)
project(Project2)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)

IF(APPLE)
    set(OPENMP_LIBRARIES "/usr/local/Cellar/libomp/11.0.0/lib")
    set(OPENMP_INCLUDES "/usr/local/Cellar/libomp/11.0.0/include")

    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")

    set(CMAKE_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument -O3")
ELSEIF(LINUX)
    set(CMAKE_CXX_FLAGS "-O3 ${OpenMP_CXX_FLAGS}")
ENDIF()

add_executable(Project2 test_conv.cpp cnn.cpp)
target_link_libraries(Project2 ${OpenCV_LIBS})