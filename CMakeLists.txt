cmake_minimum_required(VERSION 3.19)
project(monopoly_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(monopoly_cpp
        functions.h
        globals.h
        macros.h
        objects.h
        main.cpp
        user-interface.cpp
        while-loop.cpp)
