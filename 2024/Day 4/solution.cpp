#include "ud_matrix.h"
#include "user_defined.h"
#include <fstream>
#include <iostream>
#include <string>
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
  constexpr std::array<char, 4> words({'X', 'M', 'A', 'S'});
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      // creates a vector<char> from a string and constructs it inplace
      m.emplace_back(line.begin(), line.end());
    }

    // do something here
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // go into all 8 directions
        for (const auto &direction : directions) {
          pr curr_pt({i, j});
          int curr = 0;
          // check if I can find 'XMAS'
          while (curr < 4 && m.in_bounds(curr_pt) &&
                 m[curr_pt] == words[curr]) {
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
