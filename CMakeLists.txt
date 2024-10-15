cmake_minimum_required(VERSION 3.7)

project(LuaTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR ./build)

add_subdirectory("libs")
add_subdirectory("src")
