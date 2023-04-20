cmake_minimum_required(VERSION 3.24)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp")

add_executable(Chess ${SOURCES} main.cpp)
