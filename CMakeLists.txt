cmake_minimum_required(VERSION 3.11)

project(LuaTest)

# C++ VERSION

# Exprot compile commmands for visual studio code and for nvim 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# seting the binary output dir to .\build
set(CMAKE_BINARY_DIR ./build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory("libs")
add_subdirectory("src")
