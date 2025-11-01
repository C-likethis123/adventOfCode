# CMake + scnlib Setup Complete! 🎄

## What Was Created

### Core CMake Files
1. **`CMakeLists.txt`** (root) - Main CMake configuration
2. **`2024/CMakeLists.txt`** - Automatically builds all 2024 solutions
3. **`cmake_build.sh`** - Convenient build script (executable)

### Documentation
4. **`QUICKSTART_CMAKE.md`** - Quick reference guide (START HERE!)
5. **`CMAKE_SETUP.md`** - Detailed setup instructions and examples
6. **`CMAKE_AND_SCNLIB_SUMMARY.md`** - This file

### Templates & Examples
7. **`template_scnlib.cpp`** - Example code using scnlib
8. **`template.sh`** - Updated with scnlib comment hints

### Configuration
9. **`.gitignore`** - Updated to ignore CMake build files

## How to Use - Quick Reference

### Build and Run a Solution
```bash
# From the project root directory
./cmake_build.sh 2024 1 1 run
./cmake_build.sh 2024 13 2 run
```

### Just Build (Don't Run)
```bash
./cmake_build.sh 2024 1 1
```

### Manual CMake (Alternative)
```bash
cd 2024
mkdir build && cd build
cmake ..
cmake --build . --target day1_part1
```

## What is scnlib?

**scnlib** is a modern C++ library that makes input parsing much easier and safer than traditional methods.

### Before scnlib:
```cpp
string line = "x=123, y=456";
size_t xpos = line.find("x=") + 2;
size_t comma = line.find(",");
int x = stoi(line.substr(xpos, comma - xpos));
// ... more string manipulation
```

### With scnlib:
```cpp
string line = "x=123, y=456";
int x, y;
scn::scan(line, "x={}, y={}", x, y);
```

## Key Features

✅ **Automatic Download** - scnlib is fetched automatically by CMake (internet required on first build)  
✅ **Type Safe** - Compile-time format checking  
✅ **Fast** - Often faster than manual parsing  
✅ **Easy** - scanf-like syntax, but safe  
✅ **Compatible** - Works with your existing code  

## Integration with Your Existing Workflow

Your current `run.sh` script still works! You now have **two options**:

| Method | Command | When to Use |
|--------|---------|-------------|
| Old (g++) | `./run.sh 2024 1 1` | Quick testing, no scnlib needed |
| New (CMake) | `./cmake_build.sh 2024 1 1 run` | Want to use scnlib features |

## Common scnlib Patterns for Advent of Code

### 1. Parse Two Integers
```cpp
string line = "123 456";
int a, b;
scn::scan(line, "{} {}", a, b);
```

### 2. Parse Formatted Data
```cpp
string line = "Button A: X+94, Y+34";
int x, y;
scn::scan(line, "Button A: X+{}, Y+{}", x, y);
```

### 3. Parse Multiple Unknown Numbers
```cpp
vector<int> numbers;
auto range = scn::ranges::subrange(line);
while (true) {
    int num;
    auto result = scn::scan(range, "{}", num);
    if (!result) break;
    numbers.push_back(num);
    range = result.range();
}
```

### 4. Parse with Your Existing Code
```cpp
#include "user_defined.h"
#include <scn/scan.h>

// You can mix scnlib with your custom utilities
vector<int> nums1 = user_defined::split_int<int>(line, " ");  // Old way
int a, b;
scn::scan(line, "{} {}", a, b);  // New way
```

## Example: Complete Solution with scnlib

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
    
    ifstream input(argv[1]);
    string line;
    long ans = 0;
    
    while (getline(input, line)) {
        int x, y;
        // Parse each line with scnlib
        if (auto result = scn::scan(line, "{} {}", x, y)) {
            ans += x * y;  // or whatever your logic is
        }
    }
    
    cout << ans << endl;
    return 0;
}
```

## Next Steps

1. **Read the Quick Start**: Open `QUICKSTART_CMAKE.md`
2. **Try It Out**: Run `./cmake_build.sh 2024 1 1 run`
3. **See Examples**: Check `template_scnlib.cpp` for more patterns
4. **Detailed Docs**: Read `CMAKE_SETUP.md` when you want to go deeper

## Troubleshooting

### Build fails with "scn/scan.h: No such file or directory"
→ Make sure you're using CMake, not compiling with g++ directly

### First build is slow
→ Normal! CMake is downloading and building scnlib (requires internet)

### Want to use g++ instead?
→ Your old `run.sh` script still works for solutions that don't need scnlib

### Need to rebuild from scratch?
```bash
cd 2024
rm -rf build
./cmake_build.sh 2024 1 1
```

## Files Summary

```
adventOfCode/
├── CMakeLists.txt              # Root CMake config
├── cmake_build.sh              # Easy build script ⭐
├── QUICKSTART_CMAKE.md         # Quick reference ⭐
├── CMAKE_SETUP.md              # Detailed docs
├── template_scnlib.cpp         # Code examples
├── 2024/
│   ├── CMakeLists.txt          # 2024 solutions config
│   └── Day X/
│       ├── solution_1.cpp      # Your code
│       ├── solution_2.cpp      # Your code
│       └── input.txt           # Input data
└── include/                    # Your custom headers
    ├── user_defined.h
    ├── ud_matrix.h
    └── ud_unordered_map.h
```

## Questions?

- **What version of scnlib?** v2.0.2 (can be changed in CMakeLists.txt)
- **C++ Standard?** C++17 (same as before)
- **Internet required?** Only for first build to download scnlib
- **Can I still use my old workflow?** Yes! `run.sh` still works

## Resources

- [scnlib GitHub](https://github.com/eliaskosunen/scnlib)
- [scnlib Documentation](https://scnlib.dev/)
- CMake Documentation: Built-in comments in CMakeLists.txt files

---

**TL;DR**: Run `./cmake_build.sh 2024 1 1 run` to build and test a solution with scnlib support!

