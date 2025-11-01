#!/bin/bash

# Check if a day is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <day>"
  exit 1
fi

# Variables
DAY=$1
FOLDER_NAME="Day $DAY"
CPP_TEMPLATE='#include "user_defined.h"
#include "ud_matrix.h"
// #include <scn/scan.h>  // Uncomment to use scnlib for parsing
#include <algorithm>
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
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T>
using matrix = user_defined::matrix<T>;

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  if (test_case.is_open()) {
     getline(test_case, line);
     
     // Example scnlib usage (uncomment if using scnlib):
     // int a, b;
     // if (auto result = scn::scan(line, "{} {}", a, b)) {
     //     cout << "Parsed: " << a << ", " << b << endl;
     // }
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
