# Quick Start Guide - Using CMake with scnlib

## What Was Set Up

I've created a complete CMake build system for your 2024 Advent of Code solutions with **scnlib** integration.

### Files Created:
- `CMakeLists.txt` (root level)
- `2024/CMakeLists.txt` (for all 2024 solutions)
- `cmake_build.sh` (convenient build script)
- `template_scnlib.cpp` (example using scnlib)
- `CMAKE_SETUP.md` (detailed documentation)

## Quick Start - 3 Steps

### Option 1: Using the Build Script (Easiest)

```bash
# Build Day 1 Part 1
./cmake_build.sh 2024 1 1

# Build and run Day 1 Part 1
./cmake_build.sh 2024 1 1 run

# Build and run Day 13 Part 2
./cmake_build.sh 2024 13 2 run
```

### Option 2: Using CMake Directly

```bash
# One-time setup
cd /Users/chowjiaying/adventOfCode/2024
mkdir build
cd build
cmake ..

# Build a specific day
cmake --build . --target day1_part1

# Run it
cd "../Day 1"
./day1_part1 input.txt
```

## Using scnlib in Your Solutions

### Simple Example - Parsing Two Integers

```cpp
#include <scn/scan.h>
#include <string>

std::string line = "123 456";
int a, b;

if (auto result = scn::scan(line, "{} {}", a, b)) {
    // a = 123, b = 456
    std::cout << "Parsed: " << a << ", " << b << std::endl;
}
```

### Real Example - Day 1 Style Input

```cpp
#include "user_defined.h"
#include <scn/scan.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream test_case(argv[1]);
    string line;
    vector<int> left, right;
    
    while (getline(test_case, line)) {
        int a, b;
        if (auto result = scn::scan(line, "{} {}", a, b)) {
            left.push_back(a);
            right.push_back(b);
        }
    }
    
    // Process your data
    long ans = 0;
    cout << ans << endl;
    return 0;
}
```

### Advanced - Parse Unknown Number of Integers

```cpp
#include <scn/scan.h>
#include <string>
#include <vector>

std::vector<int> parse_all_ints(const std::string& line) {
    std::vector<int> numbers;
    auto range = scn::ranges::subrange(line);
    
    while (true) {
        int num;
        auto result = scn::scan(range, "{}", num);
        if (!result) break;
        
        numbers.push_back(num);
        range = result.range();
    }
    
    return numbers;
}
```

## Why scnlib?

### Before (manual parsing):
```cpp
string line = "x=123, y=456";
// Multiple lines of string manipulation...
int x = stoi(line.substr(...));
int y = stoi(line.substr(...));
```

### After (with scnlib):
```cpp
string line = "x=123, y=456";
int x, y;
scn::scan(line, "x={}, y={}", x, y);
```

## Benefits

✅ **Type-safe** - Compile-time format checking  
✅ **Clean** - No manual string manipulation  
✅ **Fast** - Often faster than traditional parsing  
✅ **Easy** - Intuitive scanf-like syntax  
✅ **Safe** - Better error handling than scanf  

## Troubleshooting

### "scn/scan.h: No such file or directory"
- Make sure you're building with CMake, not g++ directly
- The first build will download scnlib (requires internet)

### Want to use g++ instead of CMake?
You can still use your existing `run.sh` script for solutions that don't need scnlib:
```bash
./run.sh 2024 1 1
```

### Build is slow the first time
- Normal! CMake downloads and builds scnlib on first run
- Subsequent builds are fast

## Next Steps

1. Try building an existing solution:
   ```bash
   ./cmake_build.sh 2024 1 1 run
   ```

2. Look at `template_scnlib.cpp` for more examples

3. Read `CMAKE_SETUP.md` for detailed documentation

4. When creating new solutions, uncomment the scnlib include in your template

## Comparison with Your Current Workflow

| Old Workflow | New Workflow (CMake + scnlib) |
|--------------|-------------------------------|
| `./run.sh 2024 1 1` | `./cmake_build.sh 2024 1 1 run` |
| Manual string parsing | `scn::scan(line, "{} {}", a, b)` |
| Compile each time | Only recompile when changed |
| Header-only includes | Full library support |

Both workflows can coexist! Use whichever you prefer.

