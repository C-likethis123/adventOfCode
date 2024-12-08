#!/bin/bash

# Check if a day is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <day>"
  exit 1
fi

# Variables
DAY=$1
FOLDER_NAME="Day $DAY"
CPP_TEMPLATE='#include <algorithm>
#include <bitset>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
     getline(test_case, line);
  }

  cout << fixed << ans << endl;
  return 0;
}
'

# Create the folder
mkdir -p "../$FOLDER_NAME"

# Generate .cpp files with content
echo "$CPP_TEMPLATE" > "../$FOLDER_NAME/solution.cpp"
echo "" > "../$FOLDER_NAME/solution_2.cpp"

# Print success message
echo "Folder '$FOLDER_NAME' created with solution.cpp and solution_2.cpp"
