#include "user_defined.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");

  if (test_case.is_open()) {
    // parse into two lists
    vector<int> sequence;
    unordered_map<int, int> frequency_map;
    while (getline(test_case, line)) {
      vector<int> split_int = user_defined::split_int<int>(line, " ");
      sequence.emplace_back(split_int[0]);
      frequency_map[split_int[1]] += 1;
    }

    // get distance
    for (int num : sequence) {
      ans += num * frequency_map[num];
    }
    cout << fixed << ans << endl;
  }
  return 0;
}
