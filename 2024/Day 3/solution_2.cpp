#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

int main() {
  long ans = 0;
  std::ifstream test_case("input.txt");
  if (!test_case.is_open()) {
    std::cerr << "Failed to open file\n";
    return 1;
  }

  std::string all_lines((std::istreambuf_iterator<char>(test_case)),
                        std::istreambuf_iterator<char>());
  std::string_view lines(all_lines);

  bool enabled = true;
  size_t pos = 0;

  while (pos < lines.size()) {
    // Check for control instructions
    if (lines.compare(pos, 7, "don't()") == 0) {
      enabled = false;
      pos += 7;
      continue;
    }
    if (lines.compare(pos, 4, "do()") == 0) {
      enabled = true;
      pos += 4;
      continue;
    }

    // Look for "mul("
    if (lines.compare(pos, 4, "mul(") == 0) {
      size_t p = pos + 4;
      size_t end = p;
      while (end < lines.size() && isdigit(lines[end]))
        end++;
      int a;
      auto [ptr1, ec1] =
          std::from_chars(lines.data() + p, lines.data() + end, a);
      if (ec1 != std::errc()) {
        pos++;
        continue;
      }

      if (end >= lines.size() || lines[end] != ',') {
        pos++;
        continue;
      }
      size_t p2 = end + 1;
      size_t end2 = p2;
      while (end2 < lines.size() && isdigit(lines[end2]))
        end2++;
      int b;
      auto [ptr2, ec2] =
          std::from_chars(lines.data() + p2, lines.data() + end2, b);
      if (ec2 != std::errc()) {
        pos++;
        continue;
      }

      if (end2 >= lines.size() || lines[end2] != ')') {
        pos++;
        continue;
      }

      if (enabled)
        ans += a * b;
      pos = end2 + 1;
      continue;
    }

    pos++;
  }

  std::cout << ans << "\n";
  return 0;
}
