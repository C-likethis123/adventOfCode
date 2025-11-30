cmake_minimum_required(VERSION 3.14)
project(AdventOfCode2022 CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Release by default (with -O3 for performance)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Enable aggressive optimizations for Advent of Code
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-march=native)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    add_compile_options(-ffast-math)
    add_compile_options(-funroll-loops)
    message(STATUS "Aggressive optimizations enabled: -march=native -flto -ffast-math")
endif()

# Include FetchContent module for downloading scnlib
include(FetchContent)

# Fetch scnlib from GitHub
FetchContent_Declare(
  scn
  GIT_REPOSITORY https://github.com/eliaskosunen/scnlib.git
  GIT_TAG        v2.0.2
)

# Make scnlib available
FetchContent_MakeAvailable(scn)

# Add custom include directory
include_directories(${CMAKE_SOURCE_DIR}/../include)

# Add executable for Day 1
add_executable(day1 1.cpp)
target_link_libraries(day1 PRIVATE scn::scn)
set_target_properties(day1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add executable for Day 2
add_executable(day2 2.cpp)
target_link_libraries(day2 PRIVATE scn::scn)
set_target_properties(day2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Add executable for Day 3
add_executable(day3 3.cpp)
set_target_properties(day3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

