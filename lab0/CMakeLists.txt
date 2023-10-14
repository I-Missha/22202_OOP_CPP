cmake_minimum_required(VERSION 3.26)
project(lab0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Google_tests)

add_executable(lab0 main.cpp
        FileReader.h
        FileReader.cpp
        FileWriter.h
        FileWriter.cpp
        Parser.cpp
        Parser.cpp
        StaticData.cpp)
