cmake_minimum_required(VERSION 3.21)
project(braidDNA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable target
add_executable(braidDNA main.cpp angle_adjust.cpp braid_math.cpp)