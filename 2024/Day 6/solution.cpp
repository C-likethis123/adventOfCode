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

pr find_position(const matrix<char> &m) {
  size_t row_size = m.size();
  size_t col_size = m[0].size();
  for (size_t i = 0; i < row_size; i++) {
    for (size_t j = 0; j < col_size; j++) {
      if (m[i][j] == '^') {
        return pr({(int)i, (int)j});
      }
    }
  }
  return pr({-1, -1});
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  long ans = 0;
  string line;
  ifstream test_case(argv[1]);
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    matrix<char> m;
    while (getline(test_case, line)) {
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      m.emplace_back(row);
    }
    vector<pr> directions({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});

    // very bad example, don't do this
    pr curr = find_position(m);
    int curr_dir = 0;
    while (true) {
      if (m[curr] != 'X') {
        ans += 1;
        m[curr] = 'X';
      }
      auto forward_pos = curr + directions[curr_dir];

      if (!m.in_bounds(forward_pos)) {
        break;
      }
      while (m[forward_pos] == '#') {
        curr_dir = (curr_dir + 1) % 4;
        forward_pos = curr + directions[curr_dir];
      }
      curr = forward_pos;
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
