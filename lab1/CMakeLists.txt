cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Google_tests)
add_executable(lab1
        main.cpp
        BitArray.h
        BitArray.cpp
        Error.cpp)
