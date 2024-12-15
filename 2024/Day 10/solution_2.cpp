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

ratings: distinct hiking trails = number of different paths that begin there.
- if a path diverges, but ends at the same spot, they are still considered 2
different paths
- easy modification: remove the "encountered" hashmap that tracks duplicates
 */

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

bool in_bounds(vector<vector<int>> &matrix, int x, int y) {
  return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
}

long compute_trailhead_ratings(vector<vector<int>> &matrix, int i, int j) {
  vector<pr> directions({
      {1, 0},  // up
      {0, 1},  // right
      {-1, 0}, // down
      {0, -1}  // left
  });
  long ans = 0;

  vector<pr> queue({pr({i, j})});
  while (!queue.empty()) {
    auto p = queue.front();
    auto [x, y] = p;
    auto value = matrix[x][y];

    if (value == 9) {
      ans += 1;
    } else {
      // go in all directions
      for (const auto &direction : directions) {
        auto [new_x, new_y] = p + direction;
        // "encountered" set check if in bounds + can traverse ( has to be +1
        // than the current element). then put it inside the queue.
        if (in_bounds(matrix, new_x, new_y)) {
          if ((matrix[new_x][new_y] - value) == 1) {
            queue.emplace_back(pr({new_x, new_y}));
          }
        }
      }
    }
    // pop front element
    queue.erase(queue.begin());
  }
  return ans;
}

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    vector<vector<int>> matrix;
    while (getline(test_case, line)) {
      vector<int> row;
      for (char &c : line) {
        row.emplace_back(c - '0');
      }
      matrix.emplace_back(row);
    }
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix.size(); j++) {
        if (matrix[i][j] == 0) {
          ans += compute_trailhead_ratings(matrix, i, j);
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
