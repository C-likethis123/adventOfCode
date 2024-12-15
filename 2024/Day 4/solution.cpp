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
need to find: horizontal, vertical, diagonal, written backwards, or overlapping
with other words.

brute force:
- there are 8 directions that an 'X' can go.
- for each direction, check if I can form an 'XMAS'

horizontal: 5
vertical: 3
diagonal: 10

*/
#define N 140
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;
template <typename T> using matrix = user_defined::matrix<T>;
using namespace std;

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  matrix<char> m;
  // ofstream debug("output.txt");

  vector<pr> directions(
      {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}});
  std::array<char, 4> words({'X', 'M', 'A', 'S'});
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      vector<char> row;
      for (int i = 0; i < N; i++) {
        row.emplace_back(line[i]);
      }
      m.emplace_back(row);
    }

    // do something here
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // go into all 8 directions
        for (auto &direction : directions) {
          pr curr_pt({i, j});
          int curr = 0;
          // check if I can find 'XMAS'
          while (curr < 4 && m.in_bounds(curr_pt) && m[curr_pt] == words[curr]) {
            curr_pt += direction;
            curr += 1;
          }

          // if succeed, increment by 1
          if (curr == 4) {
            ans += 1;
          }
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
