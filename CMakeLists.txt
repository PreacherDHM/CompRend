cmake_minimum_required(VERSION 3.7)

project(LuaTest)

# C++ VERSION
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Exprot compile commmands for visual studio code and for nvim 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# seting the binary output dir to .\build
set(CMAKE_BINARY_DIR ./build)

add_subdirectory("libs")
add_subdirectory("src")
