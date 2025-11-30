#!/bin/bash

# CMake Build Script for Advent of Code Solutions
# Usage: ./cmake_build.sh <year> <day> <part> [run]

set -e  # Exit on error

YEAR=$1
DAY=$2
PART=$3
RUN=$4

if [ -z "$YEAR" ] || [ -z "$DAY" ] || [ -z "$PART" ]; then
    echo "Usage: $0 <year> <day> <part> [run]"
    echo "Example: $0 2024 1 1"
    echo "Example: $0 2024 1 1 run  (to build and run)"
    exit 1
fi

# Determine paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
YEAR_DIR="$SCRIPT_DIR/$YEAR"
BUILD_DIR="$YEAR_DIR/build"
DAY_DIR="$YEAR_DIR/Day $DAY"
TARGET="day${DAY}_part${PART}"
INPUT_FILE="$DAY_DIR/input_test.txt"

# Check if year directory exists
if [ ! -d "$YEAR_DIR" ]; then
    echo "Error: Year directory $YEAR_DIR does not exist"
    exit 1
fi

# Check if CMakeLists.txt exists
if [ ! -f "$YEAR_DIR/CMakeLists.txt" ]; then
    echo "Error: CMakeLists.txt not found in $YEAR_DIR"
    exit 1
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Run CMake if needed
if [ ! -f "Makefile" ] && [ ! -f "build.ninja" ]; then
    echo "Running CMake configuration..."
    cmake ..
fi

# Build the target
echo "Building $TARGET..."
cmake --build . --target "$TARGET"

if [ $? -eq 0 ]; then
    echo "✓ Build successful!"
    
    # Run if requested
    if [ "$RUN" == "run" ]; then
        EXECUTABLE="$DAY_DIR/$TARGET"
        if [ -f "$EXECUTABLE" ]; then
            echo ""
            echo "Running $TARGET with input file: $INPUT_FILE"
            echo "==================== OUTPUT ===================="
            time "$EXECUTABLE" "$INPUT_FILE"
            echo "==============================================="
        else
            echo "Error: Executable not found at $EXECUTABLE"
            exit 1
        fi
    else
        echo ""
        echo "To run the solution:"
        echo "  cd \"$DAY_DIR\""
        echo "  ./$TARGET input.txt"
    fi
else
    echo "✗ Build failed!"
    exit 1
fi


