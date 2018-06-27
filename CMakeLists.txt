cmake_minimum_required(VERSION 3.10)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
add_executable(untitled2 main.c
        constant.c
        constant.h
        help_func.c
        help_func.h
        double_john.h
        double_john.c)