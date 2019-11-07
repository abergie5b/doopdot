cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(COMMON)
include_directories(include)

file(GLOB 
     SOURCES 
     "*.cpp"
)

add_library(COMMON ${SOURCES})

