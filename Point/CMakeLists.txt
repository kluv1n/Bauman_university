cmake_minimum_required(VERSION 3.23)

set(project "Point")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_HEADERS Point.h)

set(${project}_SOURCES Point.cpp)

set(${project}_SOURCE_LIST ${${project}_HEADERS} ${${project}_SOURCES})

add_library(${project} STATIC ${${project}_SOURCE_LIST})