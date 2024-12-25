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
modification:
- not just if there is one possible value, but every possible value.

dynamic programming:
num(patterns, design) = 1 if design is empty

num(patterns, design) = sum({
  num(pattern, design - pattern),.....
})
 */
unordered_map<string, long> memo;

long possible_ways(vector<string> &patterns, string design) {
  if (design.empty()) {
    return 1;
  }
  if (memo.count(design)) {
    return memo[design];
  }
  long ways = 0;
  for (const string &pattern : patterns) {
    if (design.rfind(pattern, 0) == 0) {
      ways += possible_ways(patterns, design.substr(pattern.size()));
    }
  }
  memo[design] = ways;
  return ways;
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
      ans += possible_ways(patterns, line);
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
