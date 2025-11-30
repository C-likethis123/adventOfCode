#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <scn/scan.h>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream test_case("input_1.txt");
  if (!test_case.is_open()) {
    return 1;
  }

  string line;
  long calories = 0;
  vector<long> top_3_calories;

  auto update_top_3_calories = [&](long total) {
    if (top_3_calories.size() < 3) {
      top_3_calories.push_back(total);
      push_heap(top_3_calories.begin(), top_3_calories.end(), greater<>{});
    } else if (total > top_3_calories.front()) {
      pop_heap(top_3_calories.begin(), top_3_calories.end(), greater<>{});
      top_3_calories.back() = total;
      push_heap(top_3_calories.begin(), top_3_calories.end(), greater<>{});
    }
  };

  while (getline(test_case, line)) {
    if (line.empty()) {
      update_top_3_calories(calories);
      calories = 0;
    } else if (auto result = scn::scan<long>(line, "{}")) {
      calories += result->value();
    }
  }
  update_top_3_calories(calories);

  cout << "part 1: "
       << *max_element(top_3_calories.begin(), top_3_calories.end()) << endl;
  cout << "part 2: "
       << accumulate(top_3_calories.begin(), top_3_calories.end(), 0L) << endl;

  return 0;
}
