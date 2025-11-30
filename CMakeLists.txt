cmake_minimum_required(VERSION 3.14)
project(AdventOfCode CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include FetchContent module for downloading scnlib
include(FetchContent)

# Fetch scnlib from GitHub
FetchContent_Declare(
  scn
  GIT_REPOSITORY https://github.com/eliaskosunen/scnlib.git
  GIT_TAG        v2.0.2  # You can change this to the version you want
)

# Make scnlib available
FetchContent_MakeAvailable(scn)

# Add your custom include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Function to add an Advent of Code solution executable
function(add_aoc_solution YEAR DAY PART)
    set(TARGET_NAME "aoc_${YEAR}_day${DAY}_part${PART}")
    set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/${YEAR}/Day ${DAY}/solution_${PART}.cpp")
    
    if(EXISTS ${SOURCE_FILE})
        add_executable(${TARGET_NAME} ${SOURCE_FILE})
        target_link_libraries(${TARGET_NAME} PRIVATE scn::scn)
        
        # Set output directory to the solution's directory
        set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${YEAR}/Day ${DAY}"
        )
    endif()
endfunction()

# Optionally, you can manually add specific solutions
# Example: add_aoc_solution(2024 1 1)
# Example: add_aoc_solution(2024 1 2)

# Or add all 2024 solutions (uncomment if you want to build all at once)
# foreach(DAY RANGE 1 25)
#     add_aoc_solution(2024 ${DAY} 1)
#     add_aoc_solution(2024 ${DAY} 2)
# endforeach()


