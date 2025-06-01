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

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  std::regex reg_exp("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
  const int SECONDS = 100;
  const int ROWS = 103;
  const int COLS = 101;
  matrix<int> m;
  for (int i = 0; i < ROWS; i++) {
    vector<int> rows;
    rows.resize(COLS, 0);
    m.emplace_back(rows);
  }
  vector<pr> points;
  vector<pr> velocity;
  if (test_case.is_open()) {
    std::smatch matches;

    while (getline(test_case, line)) {
      if (std::regex_search(line, matches, reg_exp)) {
        int x = stoi(matches[1]);
        int y = stoi(matches[2]);
        m[x][y] += 1;
        points.emplace_back(pr({x, y}));
        int x_velocity = stoi(matches[3]);
        int y_velocity = stoi(matches[4]);
        velocity.emplace_back(pr({x_velocity, y_velocity}));
      }
    }
    while (ans < 10000) {
      vector<pr> new_points;
      for (int i = 0; i < points.size(); i++) {
        auto [x_velocity, y_velocity] = velocity[i];
        auto p = points[i];
        m[p] -= 1;
        int x = p.first + x_velocity;
        int y = p.second + y_velocity;
        if (x < 0) {
          x = COLS + x;
        } else if (x >= COLS) {
          x = x % COLS;
        }
        if (y < 0) {
          y = ROWS + y;
        } else if (y >= ROWS) {
          y = y % ROWS;
        }
        new_points.emplace_back(pr({x, y}));
        m[x][y] += 1;
      }
      ans += 1;
      points = new_points;
      // check if it's a christmas tree
      // for (int i = 0; i < COLS; i++) {
      //   int longest_window = 0;
      //   int idx = 0;
      //   for (int j = 0; j < ROWS; j++) {
      //     if (m[j][x] > 0) {
      //       longest_window = max(longest_window, j - idx + 1);
      //     } else {
      //       idx = j;
      //     }
      //   }
      // }
      debug << ans << endl;

      for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
          if (m[i][j] > 0) {
            debug << '*';
          } else {
            debug << ".";
          }
        }
        debug << endl;
      }
      debug << endl;
    }

    cout << fixed << ans << endl;
  }

  return 0;
}
