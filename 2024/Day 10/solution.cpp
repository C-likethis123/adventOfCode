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

Graph qn:
- start from 0, then keep traversing until I reach 9.
- maybe can use DFS.

subtle bug:
- a reference to an element using queue.front()
- if memory is reallocated after adding an element to queue, all previous
references becomes invalid

 possible improvements:
 - there are some duplicate elements processed in the queue, it can be removed
 */

using namespace std;

bool in_bounds(vector<vector<int>> &matrix, int x, int y) {
  return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
}

long compute_trailhead_score(vector<vector<int>> &matrix, int i, int j) {
  // put encountered trailheads here
  auto hash = [&matrix](const user_defined::pair<int> &p) {
    int size = matrix.size();
    return p.first * size + p.second;
  };
  unordered_set<user_defined::pair<int>, decltype(hash)> encountered(8, hash);

  vector<std::pair<int, int>> directions({
      {1, 0},  // up
      {0, 1},  // right
      {-1, 0}, // down
      {0, -1}  // left
  });

  vector<user_defined::pair<int>> queue({user_defined::pair<int>({i, j})});
  while (!queue.empty()) {
    auto [x, y] = queue.front();
    auto value = matrix[x][y];

    if (value == 9) {
      // if it is 9, and has not been encountered before, add it to the
      encountered.insert({x, y});
    } else {
      // go in all directions

      for (const auto &direction : directions) {
        int new_x = x + direction.first;
        int new_y = y + direction.second;

        // "encountered" set check if in bounds + can traverse ( has to be +1
        // than the current element). then put it inside the queue.
        if (in_bounds(matrix, new_x, new_y)) {
          if ((matrix[new_x][new_y] - value) == 1) {
            queue.emplace_back(user_defined::pair<int>({new_x, new_y}));
          }
        }
      }
    }
    // pop front element
    queue.erase(queue.begin());
  }
  return encountered.size();
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
          ans += compute_trailhead_score(matrix, i, j);
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}