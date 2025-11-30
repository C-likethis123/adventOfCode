#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

int get_priority(char c) { return (c >= 'a') ? (c - 'a' + 1) : (c - 'A' + 27); }

long compute_priority(string &line) {
  long part1 = 0;
  unordered_set<char> first_half;
  for (size_t i = 0; i < line.length() / 2; i++) {
    first_half.insert(line[i]);
  }
  unordered_set<char> common_items;
  for (size_t i = line.length() / 2; i < line.length(); i++) {
    if (first_half.count(line[i])) {
      common_items.insert(line[i]);
    }
  }
  for (char c : common_items) {
    part1 += get_priority(c);
  }
  return part1;
}

int main() {
  ifstream test_case("input_3.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_3.txt" << endl;
    return 1;
  }

  string line;
  long part1 = 0;
  long part2 = 0;
  std::vector<string> group;
  while (getline(test_case, line)) {
    part1 += compute_priority(line);

    // group into 3 lines
    // find common item for all 3 lines - this is the badge
    group.push_back(line);
    if (group.size() == 3) {
      unordered_map<char, int> frequencies;
      for (string &rucksack : group) {
        unordered_set<char> seen;
        for (char c : rucksack) {
          if (seen.count(c) == 0) {
            seen.insert(c);
            frequencies[c]++;
          }
        }
      }
      for (auto &[c, freq] : frequencies) {
        if (freq == 3) {
          //   std::cout << "Badge: " << c << endl;
          part2 += get_priority(c);
          break;
        }
      }
      group.clear();
    }
  }
  std::cout << "Part 1: " << part1 << endl;
  std::cout << "Part 2: " << part2 << endl;
  return 0;
}