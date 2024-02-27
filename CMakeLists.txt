cmake_minimum_required(VERSION 3.21)
project(braidDNA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(include)
add_executable(braid src/main.cpp src/angle_adjust.cpp src/math_braid.cpp)
add_executable(test unit_test/test_math.cpp src/math_braid.cpp)
