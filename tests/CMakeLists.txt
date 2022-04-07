cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

add_library(Catch2 INTERFACE)
add_library(Catch2::Test ALIAS Catch2)
target_include_directories(Catch2 INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(tests.o tests.cpp)