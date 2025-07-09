cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME Glad)
project(${PROJECT_NAME})

add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)