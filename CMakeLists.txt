cmake_minimum_required(VERSION 3.10)
project(run C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wextra")

include_directories(headers)

add_executable(run
        #---------------------------------------------------------------------------------------------------------------
        main.c
        #---------------------------------------------------------------------------------------------------------------
        j_core.h
        j_applied_functions.h
        j_double.h
        auto_type.h
        j_message.h
        j_commands.h
        #---------------------------------------------------------------------------------------------------------------
        j_applied_functions.c
        j_double.c
        j_core.c
        j_message.c
        j_commands.c)