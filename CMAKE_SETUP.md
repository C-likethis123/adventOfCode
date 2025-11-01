# CMake Setup for Advent of Code with scnlib

## What is scnlib?

[scnlib](https://github.com/eliaskosunen/scnlib) is a modern C++ library for scanf-like input parsing. It provides a safer and more convenient alternative to scanf/sscanf with modern C++ features.

## Setup Instructions

### Building 2024 Solutions

1. Navigate to the 2024 directory:
```bash
cd /Users/chowjiaying/adventOfCode/2024
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Run CMake to generate build files:
```bash
cmake ..
```

4. Build all solutions:
```bash
cmake --build .
```

Or build a specific solution:
```bash
cmake --build . --target day1_part1
cmake --build . --target day1_part2
```

5. Run the executable:
```bash
cd "../Day 1"
./day1_part1 input.txt
```

### Building from Root Directory

Alternatively, from the root directory:
```bash
cd /Users/chowjiaying/adventOfCode
mkdir build
cd build
cmake ..
```

## Using scnlib in Your Solutions

### Basic Example

```cpp
#include <scn/scan.h>
#include <iostream>
#include <string>

int main() {
    std::string input = "123 456";
    int a, b;
    
    // Scan two integers
    auto result = scn::scan(input, "{} {}", a, b);
    
    if (result) {
        std::cout << "a = " << a << ", b = " << b << std::endl;
    }
    
    return 0;
}
```

### Reading from File

```cpp
#include <scn/scan.h>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    std::string line;
    
    while (std::getline(file, line)) {
        int num1, num2;
        
        // Parse two numbers from the line
        if (auto result = scn::scan(line, "{} {}", num1, num2)) {
            std::cout << "Parsed: " << num1 << " and " << num2 << std::endl;
        }
    }
    
    return 0;
}
```

### Advanced Parsing

```cpp
#include <scn/scan.h>
#include <string>
#include <vector>

// Parse multiple integers from a line
std::vector<int> parse_integers(const std::string& line) {
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

// Parse with specific format (e.g., "x=123, y=456")
struct Point {
    int x, y;
};

Point parse_point(const std::string& line) {
    Point p;
    scn::scan(line, "x={}, y={}", p.x, p.y);
    return p;
}
```

## Comparison: Before and After scnlib

### Before (using string splitting):
```cpp
std::string line = "123 456 789";
std::vector<int> nums = user_defined::split_int<int>(line, " ");
```

### After (using scnlib):
```cpp
std::string line = "123 456 789";
int a, b, c;
scn::scan(line, "{} {} {}", a, b, c);
```

## Additional Features

- **Type safety**: Compile-time format string checking
- **Error handling**: Returns result objects that can be checked
- **Performance**: Often faster than traditional parsing methods
- **Range support**: Works with C++20 ranges
- **Locale-independent**: Predictable behavior across systems

## Troubleshooting

### If CMake can't find scnlib
The CMakeLists.txt uses FetchContent to automatically download scnlib, so you need an internet connection the first time you build.

### If you get compilation errors
Make sure you're using C++17 or later:
```bash
cmake -DCMAKE_CXX_STANDARD=17 ..
```

### Clean rebuild
```bash
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

## Links

- [scnlib GitHub](https://github.com/eliaskosunen/scnlib)
- [scnlib Documentation](https://scnlib.dev/)

