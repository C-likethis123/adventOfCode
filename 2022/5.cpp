#include <algorithm>
#include <fstream>
#include <iostream>
#include <scn/scan.h>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream test_case("input_5.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_5.txt" << endl;
    return 1;
  }

  string line;
  vector<vector<char>> stacks_part_1(9);
  vector<vector<char>> stacks_part_2(9);

  while (getline(test_case, line) && !line.empty()) {
    for (size_t i = 1; i < line.size(); i += 4) {
      char crate = line[i];
      if (crate >= 'A' && crate <= 'Z') {
        stacks_part_1[i / 4].push_back(crate);
        stacks_part_2[i / 4].push_back(crate);
      }
    }
  }

  for (auto &stack : stacks_part_1) {
    reverse(stack.begin(), stack.end());
  }
  for (auto &stack : stacks_part_2) {
    reverse(stack.begin(), stack.end());
  }

  auto process_part_1 = [](int count, int from, int to,
                           vector<vector<char>> &stacks) {
    auto start = stacks[from].end() - count;
    auto end = stacks[from].end();
    stacks[to].insert(stacks[to].end(), reverse_iterator(end),
                      reverse_iterator(start));
    stacks[from].erase(start, end);
  };

  auto process_part_2 = [](int count, int from, int to,
                           vector<vector<char>> &stacks) {
    auto start = stacks[from].end() - count;
    auto end = stacks[from].end();
    stacks[to].insert(stacks[to].end(), start, end);
    stacks[from].erase(start, end);
  };

  while (getline(test_case, line)) {
    if (auto result = scn::scan<int, int, int>(line, "move {} from {} to {}")) {
      auto [count, from, to] = result->values();
      process_part_1(count, from - 1, to - 1, stacks_part_1);
      process_part_2(count, from - 1, to - 1, stacks_part_2);
    }
  }

  cout << "Part 1: ";
  for (const auto &stack : stacks_part_1) {
    if (!stack.empty()) {
      cout << stack.back();
    }
  }
  cout << endl;

  cout << "Part 2: ";
  for (const auto &stack : stacks_part_2) {
    if (!stack.empty()) {
      cout << stack.back();
    }
  }
  cout << endl;

  return 0;
}
