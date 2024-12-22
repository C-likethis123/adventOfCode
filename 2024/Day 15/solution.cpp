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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

/**
retrieve the matrix
retrieve the moves.


- attempt to move forward.
- iterate in the direction the robot attempts to move in. if there is a space,
move all affected stuff into a space. if it hits a wall, nothing moves.
- move all affected stuff in the column/line.

- iterate through the matrix and attempt to compute the sum.
- if I have a box of (x, y): 100 * x + y
 */

pr find_starting_position(matrix<char> &m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[0].size(); j++) {
      if (m[i][j] == '@') {
        return pr({i, j});
      }
    }
  }
  return pr({0, 0});
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
    matrix<char> m;

    while (getline(test_case, line) && !line.empty()) {

      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      m.emplace_back(row);
    }
    pr start = find_starting_position(m);
    while (getline(test_case, line)) {

      for (char &move : line) {

        pr direction({0, 0});
        switch (move) {
        case '>':
          direction = pr({0, 1});
          break;
        case '^':
          direction = pr({-1, 0});
          break;
        case 'v':
          direction = pr({1, 0});
          break;
        default:
          direction = pr({0, -1});
        }
        pr current = start;
        current += direction;
        while (m[current] != '.' && m[current] != '#') {
          current += direction;
        }

        // get a stopping point, shift everything if I can
        if (m[current] == '.') {
          pr prev = current - direction;
          while (current != start) {
            m[current] = m[prev];
            current = prev;
            prev = prev - direction;
          }
          m[start] = '.';

          // once everything is shifted, change 'start'
          start += direction;
        }
      }
    }

    // once everything is calculated, iterate through the matrix and compute GPS
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m[0].size(); j++) {
        if (m[i][j] == 'O') {
          ans += 100 * i + j;
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
