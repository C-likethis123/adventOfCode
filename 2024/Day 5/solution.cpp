#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
option 2:
- for each item in the list, i take the list of "forbidden" numbers for that
item and add it to a set.
- then check in that set.

- O(n) to construct set of forbidden numbers
- O(1) to check if current number is in the set of forbidden numbers
- time complexity: O(n), where n is the forbidden list length
*/

std::vector<int> split(string s, string delimiter) {
  size_t pos = 0;
  std::string token;
  std::vector<int> v;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(stoi(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(stoi(s));
  return v;
}

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    // get section ordering rules
    unordered_map<int, unordered_set<int>> orderings;
    while (getline(test_case, line) && !line.empty()) {
      vector<int> ordering = split(line, "|");
      orderings[ordering[1]].insert(ordering[0]);
    }

    while (getline(test_case, line)) {
      vector<int> numbers = split(line, ",");
      unordered_set<int> forbidden;
      bool is_safe = true;
      for (int num : numbers) {
        if (forbidden.count(num)) {
          is_safe = false;
          break;
        }
        // using .merge method does not work because it will splice orderings[num]
        auto &set_to_merge = orderings[num];
        for (auto &item : set_to_merge) {

          forbidden.insert(item);
        }
      }
      if (is_safe) {
        ans += numbers[numbers.size() / 2];
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
