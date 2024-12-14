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

/**

idea:
- iterate through the whole map, group the coordinates into different groups
- area: take the size of each group as the area
- perimeter:
  - iterate through each element in the group:
    - go in all four directions
    - if it is the last element in that direction, add 1.

"plants of the same type can appear in multiple regions"
- instead of grouping coordinates by the same icon, try the number of islands
technique where we take a coordinate, and find all reachable coordinates within
it.

 */

bool in_bounds(vector<vector<char>> &matrix, int x, int y) {
  return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
}


// TIL: to pass in an unordered set with a custom hash, the best way is to template it.
template <typename Hash>
long compute_cost(vector<vector<char>> &matrix,
                  unordered_set<pair<int, int>, Hash> &encountered, int i,
                  int j) {
  long area = 0;
  long perimeter = 0;
  std::vector<pair<int, int>> queue({std::pair<int, int>({i, j})});
  const std::vector<std::pair<int, int>> directions({
      {1, 0},  // up
      {0, 1},  // right
      {-1, 0}, // down
      {0, -1}  // left
  });
  while (!queue.empty()) {
    auto [x, y] = queue.front();
    char value = matrix[x][y];
    if (encountered.count(pair<int, int>({x, y})) == 0) {
      encountered.insert(pair<int, int>({x, y}));
      area += 1;
      for (auto &direction : directions) {
        int new_x = x + direction.first;
        int new_y = y + direction.second;
        if (in_bounds(matrix, new_x, new_y) && matrix[new_x][new_y] == value) {
          queue.emplace_back(pair<int, int>({new_x, new_y}));
        } else {
          perimeter += 1;
        }
      }
    }
    queue.erase(queue.begin());
  }
  return area * perimeter;
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
    vector<vector<char>> matrix;
    auto hashfn = [&matrix](const std::pair<int, int> &p) {
      int size = matrix.size();
      return p.first * size + p.second;
    };
    unordered_set<pair<int, int>, decltype(hashfn)> encountered(8, hashfn);
    while (getline(test_case, line)) {
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      matrix.emplace_back(row);
    }

    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[0].size(); j++) {
        if (encountered.count(pair<int, int>({i, j})) == 0) {
          ans += compute_cost(matrix, encountered, i, j);
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
