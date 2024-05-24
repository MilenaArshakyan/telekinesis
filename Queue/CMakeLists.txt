cmake_minimum_required(VERSION 3.10)
project(queue)
set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

add_executable(queue ../src/main.cpp)