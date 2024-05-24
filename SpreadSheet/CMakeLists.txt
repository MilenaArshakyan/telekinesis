cmake_minimum_required(VERSION 3.10)
project(spreadSheet)
set(CMAKE_CXX_STANDARD 20)

include_directories(header)

add_executable(spreadsheet ../src/cell.cpp ../src/spreadSheet.cpp ../src/main.cpp)