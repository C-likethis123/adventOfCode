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

/**
should find two MAS in the shape of an X.
within the X, each MAS can be written forwards or backwards.

*/

using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;
template <typename T> using matrix = user_defined::matrix<T>;

#define N 140

using namespace std;

inline bool is_valid_diagonal(matrix<char> &m, const pr &first,
                              const pr &second) {
  return m.in_bounds(first) && m.in_bounds(second) &&
         ((m[first] == 'S' && m[second] == 'M') ||
          (m[first] == 'M' && m[second] == 'S'));
}

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  matrix<char> m;
  // ofstream debug("output.txt");

  if (test_case.is_open()) {
    for (int r = 0; r < N; r++) {
      getline(test_case, line);
      m.emplace_back(line.begin(), line.end());
    }

    // do something here
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // find an 'A'
        if (m[i][j] == 'A') {
          // check if diagonals are valid
          bool is_valid_left_diagonal =
              is_valid_diagonal(m, pr({i - 1, j - 1}), pr({i + 1, j + 1}));
          bool is_valid_right_diagonal =
              is_valid_diagonal(m, pr({i - 1, j + 1}), pr({i + 1, j - 1}));
          if (is_valid_left_diagonal && is_valid_right_diagonal) {
            ans += 1;
          }
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
