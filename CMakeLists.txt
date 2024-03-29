cmake_minimum_required(VERSION 3.27)
project(CDataframeL1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CDataframeL1
        cdataframe.c
        cdataframe.h
        column.c
        column.h
        main.c)
