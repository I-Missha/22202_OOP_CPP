cmake_minimum_required(VERSION 3.26)
project(lab0)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab0 main.cpp
        fileReader.cpp
        fileReader.h
        fileWriter.cpp
        fileWriter.h
        staticData.cpp
        staticData.h
        parser.cpp
        parser.h)
