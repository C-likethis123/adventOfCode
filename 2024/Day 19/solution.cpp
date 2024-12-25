#include "ud_matrix.h"
#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;
/**
backtracking problem.

1. store all patterns
2. get the design:
- if they start with a pattern, try using this.
- if I can't find a pattern with this, try some other pattern.

dynamic programming?
- can(brwrr) = any{
  has(br) && can(wrr),
  has(....) && can(.....)
}

has(br) if it's available in the sets

 */

bool is_possible(vector<string> &patterns, string design) {
  if (design.empty()) {
    return true;
  }
  for (const string &pattern : patterns) {
    if (design.rfind(pattern, 0) == 0) {
      if (is_possible(patterns, design.substr(pattern.size()))) {
        return true;
      }
    }
  }
  return false;
}

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  if (test_case.is_open()) {
    getline(test_case, line);
    vector<string> patterns = user_defined::split(line, ", ");

    getline(test_case, line); // empty line

    while (getline(test_case, line)) {
      // check
      if (is_possible(patterns, line)) {
        ans += 1;
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
