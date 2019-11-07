cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(doopdot)

add_subdirectory(src/common)
add_subdirectory(src/algorithms)

file(GLOB 
     SOURCES 
     "src/main.cpp" 
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_executable(doopdot ${SOURCES})

target_link_libraries(doopdot COMMON)
target_link_libraries(doopdot ALGORITHMS)
target_link_libraries(doopdot -ljpeg)

