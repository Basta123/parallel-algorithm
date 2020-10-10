cmake_minimum_required(VERSION 3.16)
project(OpenMp_Tree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
add_executable(OpenMp_Tree main.cpp TreeFunctions.cpp cmake-build-debug/TreeFunctions.h TreeFunctions.h)