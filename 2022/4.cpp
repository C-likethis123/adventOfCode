#include <fstream>
#include <iostream>
#include <scn/scan.h>
using namespace std;

bool check_if_fully_contained(long a_start, long a_end, long b_start,
                              long b_end) {
  return (a_start <= b_start && a_end >= b_end) ||
         (b_start <= a_start && b_end >= a_end);
}

bool check_if_overlap(long a_start, long a_end, long b_start, long b_end) {
  return a_start <= b_end && b_start <= a_end;
}

int main() {
  string line;
  long part1{0};
  long part2{0};
  ifstream test_case("input_4.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_4.txt" << endl;
    return 1;
  }
  while (getline(test_case, line)) {
    if (auto result = scn::scan<long, long, long, long>(line, "{}-{},{}-{}")) {
      const auto [a, b, c, d] = result->values();
      part1 += check_if_fully_contained(a, b, c, d);
      part2 += check_if_overlap(a, b, c, d);
    }
  }
  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  return 0;
}