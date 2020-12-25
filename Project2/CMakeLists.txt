cmake_minimum_required(VERSION 3.17)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)

IF(APPLE)
#    set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/11.0.0/bin/clang-11")
    set(OPENMP_LIBRARIES "/usr/local/Cellar/libomp/11.0.0/lib")
    set(OPENMP_INCLUDES "/usr/local/Cellar/libomp/11.0.0/include")

    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
#    set(CMAKE_CXX_COMPILER /usr/local/Cellar/gcc/10.2.0/bin/g++-10)
    set(CMAKE_CXX_FLAGS "-Xpreprocessor -fopenmp -lomp -Wno-unused-command-line-argument -O3")
ELSEIF(LINUX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -O3 ${OpenMP_CXX_FLAGS} -mfpu=neon")
ENDIF()

add_executable(Project2 main.cpp cnn.cpp)
target_link_libraries(Project2 ${OpenCV_LIBS})