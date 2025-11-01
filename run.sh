#!/bin/bash

# Check if a day is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <day>"
  exit 1
fi
g++ -std=c++17 -I../include -I/path/to/scnlib/include template_scnlib.cpp -o solution
# Variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
YEAR=$1
DAY=$2
PART=$3
FILE="input.txt"
FOLDER="/Users/chowjiaying/adventOfCode/$YEAR/Day $DAY"

# Compile the solution
g++ -std=c++17  -I/Users/chowjiaying/adventOfCode/include/ "$FOLDER/solution_$PART.cpp" -o test

# Run from the Day directory so relative paths work
cd "$FOLDER"
time "$SCRIPT_DIR/test" "$FILE"
