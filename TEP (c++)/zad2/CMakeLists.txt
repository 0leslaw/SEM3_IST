cmake_minimum_required(VERSION 3.26)
project(zad2)

set(CMAKE_CXX_STANDARD 98)

add_executable(zad2 main.cpp
        CNumber.cpp
        CNumber.h
        IntToArrayService.cpp
        IntToArrayService.h
)
