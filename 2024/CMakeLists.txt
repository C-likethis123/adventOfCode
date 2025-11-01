cmake_minimum_required(VERSION 3.14)
project(AdventOfCode2024 CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Release by default (with -O3 for performance)
# To use Debug mode (no optimization), run: cmake -DCMAKE_BUILD_TYPE=Debug ..
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Enable aggressive optimizations for Advent of Code
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Use CPU-specific instructions (AVX2, NEON, etc.)
    add_compile_options(-march=native)
    
    # Link-Time Optimization for cross-function inlining
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    
    # Additional performance flags
    add_compile_options(-ffast-math)  # Aggressive floating point
    add_compile_options(-funroll-loops)  # Unroll small loops
    
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

# Function to add a solution executable
function(add_day_solution DAY PART)
    set(TARGET_NAME "day${DAY}_part${PART}")
    set(SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Day ${DAY}/solution_${PART}.cpp")
    
    if(EXISTS ${SOURCE_FILE})
        add_executable(${TARGET_NAME} ${SOURCE_FILE})
        target_link_libraries(${TARGET_NAME} PRIVATE scn::scn)
        
        # Set output directory to the solution's directory
        set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Day ${DAY}"
        )
        
        message(STATUS "Added target: ${TARGET_NAME} from ${SOURCE_FILE}")
    endif()
endfunction()

# Automatically add all existing solutions
foreach(DAY RANGE 1 25)
    foreach(PART 1 2)
        add_day_solution(${DAY} ${PART})
    endforeach()
endforeach()

