cmake_minimum_required(VERSION 3.5)
project(RTWeekend
        VERSION 0.1
        DESCRIPTION "A RT in C"
        LANGUAGES C)
add_executable(RTWeekend code/main.c)
set (CMAKE_C_FLAGS "-lX11")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER clang)