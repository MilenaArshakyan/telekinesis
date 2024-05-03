cmake_minimum_required(VERSION 3.10)
project(spreadSheet)
set(CMAKE_CXX_STANDARD 20)
add_executable(spreadSheet ../src/cell.cpp ../src/spreadSheet.cpp ../src/main.cpp)