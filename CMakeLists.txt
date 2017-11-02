cmake_minimum_required(VERSION 3.10)

project(ext-d VERSION 0.0.2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(config.h.in config.h)

add_executable(ext-d main.cpp config.h.in commandHandler.h commandHandler.cpp)