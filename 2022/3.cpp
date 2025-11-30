#include <bitset>
#include <fstream>
#include <iostream>

using namespace std;

int get_priority(char c) { return (c >= 'a') ? c - 'a' : c - 'A' + 26; }

/**
52 bytes is sufficient, but changed it to 64 to align with the cache lines.
*/
bitset<64> make_bitset_from_line(const string &line,
                                 std::string::const_iterator start,
                                 std::string::const_iterator end) {
  bitset<64> bitset;
  for (auto it = start; it != end; it++) {
    bitset.set(get_priority(*it));
  }
  return bitset;
}

long compute_priority(const string &line) {
  bitset<64> first_half = make_bitset_from_line(
      line, line.begin(), line.begin() + line.length() / 2);
  bitset<64> second_half =
      make_bitset_from_line(line, line.begin() + line.length() / 2, line.end());
  bitset<64> common_items = first_half & second_half;
  for (size_t i = 0; i < 64; i++) {
    if (common_items.test(i)) {
      return i + 1;
    }
  }
}

long compute_priority_for_group(vector<bitset<64>> &group) {
  bitset<64> common_items = group[0] & group[1] & group[2];
  for (size_t i = 0; i < 64; i++) {
    if (common_items.test(i)) {
      return i + 1;
    }
  }
}

int main() {
  constexpr int GROUP_SIZE = 3;
  ifstream test_case("input_3.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_3.txt" << endl;
    return 1;
  }

  string line;
  long part1 = 0;
  long part2 = 0;
  std::vector<bitset<64>> group;
  group.reserve(GROUP_SIZE);
  while (getline(test_case, line)) {
    part1 += compute_priority(line);

    group.push_back(make_bitset_from_line(line, line.begin(), line.end()));
    if (group.size() == GROUP_SIZE) {
      part2 += compute_priority_for_group(group);
      group.clear();
    }
  }
  std::cout << "Part 1: " << part1 << endl;
  std::cout << "Part 2: " << part2 << endl;
  return 0;
}