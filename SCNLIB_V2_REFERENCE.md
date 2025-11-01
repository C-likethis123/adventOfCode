# scnlib v2.x Quick Reference

## ⚠️ Important: API Changed from v1.x to v2.x

The CMakeLists.txt downloads **scnlib v2.0.2**, which has a **different API** than v1.x.

## Basic Syntax Comparison

### ❌ OLD (v1.x) - Don't use this:
```cpp
int a, b;
if (auto result = scn::scan(line, "{} {}", a, b)) {
    // use a and b
}
```

### ✅ NEW (v2.x) - Use this:
```cpp
if (auto result = scn::scan<int, int>(line, "{} {}")) {
    auto [a, b] = result->values();
    // use a and b
}
```

## Common Patterns for Advent of Code

### 1. Parse Two Integers
```cpp
std::string line = "123 456";
if (auto result = scn::scan<int, int>(line, "{} {}")) {
    auto [a, b] = result->values();
    std::cout << a << " " << b << std::endl;  // 123 456
}
```

### 2. Parse with Custom Format
```cpp
std::string line = "x=123, y=456";
if (auto result = scn::scan<int, int>(line, "x={}, y={}")) {
    auto [x, y] = result->values();
    std::cout << x << " " << y << std::endl;  // 123 456
}
```

### 3. Parse Multiple Numbers (Unknown Count)
```cpp
std::string line = "1 2 3 4 5";
std::vector<int> numbers;
std::string_view remaining = line;

while (!remaining.empty()) {
    auto result = scn::scan<int>(remaining, "{}");
    if (!result) break;
    
    numbers.push_back(std::get<0>(result->values()));
    remaining = result->range();
}
// numbers = {1, 2, 3, 4, 5}
```

### 4. Using std::get Instead of Structured Bindings
If you can't use structured bindings:
```cpp
if (auto result = scn::scan<int, int>(line, "{} {}")) {
    int a = std::get<0>(result->values());
    int b = std::get<1>(result->values());
}
```

### 5. Parse from File Stream
```cpp
std::ifstream file("input.txt");
std::string line;
while (std::getline(file, line)) {
    if (auto result = scn::scan<int, int>(line, "{} {}")) {
        auto [num1, num2] = result->values();
        // process num1 and num2
    }
}
```

### 6. Parse Different Types
```cpp
std::string line = "Count: 42 Value: 3.14 Name: foo";
if (auto result = scn::scan<int, double, std::string>(line, "Count: {} Value: {} Name: {}")) {
    auto [count, value, name] = result->values();
    // count = 42, value = 3.14, name = "foo"
}
```

## Key Differences from v1.x

| Feature | v1.x | v2.x |
|---------|------|------|
| Type specification | Inferred from output parameters | **Explicit template parameters** |
| Output | Parameters modified in place | **Returned via `.values()`** |
| Syntax | `scan(source, format, a, b)` | **`scan<int, int>(source, format)`** |
| Error checking | Returns bool-like | **Returns optional-like result** |

## Error Handling

```cpp
auto result = scn::scan<int, int>(line, "{} {}");
if (!result) {
    // Parsing failed
    std::cerr << "Parse error: " << result.error().msg() << std::endl;
} else {
    auto [a, b] = result->values();
    // Success
}
```

## Common Errors

### Error: "requires 2 arguments, but 4 were provided"
❌ **Wrong:**
```cpp
int a, b;
scn::scan(line, "{} {}", a, b);  // v1.x syntax
```

✅ **Correct:**
```cpp
auto result = scn::scan<int, int>(line, "{} {}");  // v2.x syntax
auto [a, b] = result->values();
```

### Error: "cannot deduce template arguments"
❌ **Wrong:**
```cpp
auto result = scn::scan(line, "{} {}");  // Missing type parameters
```

✅ **Correct:**
```cpp
auto result = scn::scan<int, int>(line, "{} {}");  // Specify types
```

## Resources

- [scnlib GitHub](https://github.com/eliaskosunen/scnlib)
- [scnlib v2.x Documentation](https://v2.scnlib.dev/)
- [Migration Guide](https://v2.scnlib.dev/2.0/migration-2.html)

## Quick Tip

For most Advent of Code problems, you'll use this pattern:

```cpp
#include <scn/scan.h>
#include <string>
#include <fstream>

std::ifstream input("input.txt");
std::string line;

while (std::getline(input, line)) {
    if (auto result = scn::scan<int, int>(line, "{} {}")) {
        auto [a, b] = result->values();
        // Solve the problem with a and b
    }
}
```

