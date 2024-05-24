cmake_minimum_required(VERSION 3.10)
project(spreadSheet)
set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

add_executable(stack ../src/main.cpp)