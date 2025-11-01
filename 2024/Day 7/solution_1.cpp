#include "user_defined.h"
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;
/**
Before optimization:
real    0m1.283s
user    0m0.998s
sys     0m0.013s

After optimizations:
1038838357795

real    0m0.517s
user    0m0.349s
sys     0m0.005s
 */

bool can_form_target(const vector<long> &nums, long target, size_t i,
                     long acc) {
  if (i == nums.size())
    return acc == target;

  long next = nums[i];

  // Try '+'
  if (can_form_target(nums, target, i + 1, acc + next))
    return true;

  // Try '*'
  if (can_form_target(nums, target, i + 1, acc * next))
    return true;

  return false;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "supply filename";
    return -1;
  }
  long ans = 0;
  string line;
  ifstream test_case(argv[1]);
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      // parsing logic has no issues
      string_view curr_line = std::string_view(line);
      size_t start = 0;
      size_t end = curr_line.find(':', start);
      // find first item
      long first;
      std::string_view token = curr_line.substr(start, end);
      {
        auto [ptr, ec] =
            std::from_chars(token.data(), token.data() + token.size(), first);
        if (ec != std::errc()) {
          continue;
        }
      }
      std::string_view remaining = curr_line.substr(end + 1);
      std::vector<long> numbers = user_defined::split_int<long>(remaining, " ");

      if (can_form_target(numbers, first, 1, 0)) {
        ans += first;
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
