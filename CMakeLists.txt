cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
project(arraysubsets)
enable_testing()

add_subdirectory(tests)

include_directories(src)
add_subdirectory(src)

add_executable(arraysubsets.o src/main.cpp)