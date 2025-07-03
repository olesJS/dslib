cmake_minimum_required(VERSION 3.29)
project(dslib C)

set(CMAKE_C_STANDARD 11)

add_executable(dslib main.c
        ds_stack.c
        ds_stack.h
)
