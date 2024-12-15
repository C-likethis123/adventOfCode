
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

/**
How to amend the perimeter calculation from part 1?
- Observe that the total perimeter corresponds to the total number of edges.
- Outer edge: "protruding edges" - calculated by checking if two perpendicular sides are out of bounds
- Inner edges:
Let's say we have a concave edge like this:
RX
?R

At position X, if there are two items surrounding X (indicated by the two 'R's), but with a missing diagonal (indicated with a ?),
then we have a concave edge
 */

bool in_bounds(vector<vector<char>> &matrix, int x, int y) {
  return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
}

template <typename Hash>
long compute_cost(vector<vector<char>> &matrix,
                  unordered_set<pair<int, int>, Hash> &encountered, int i,
                  int j) {
  long area = 0;
  long perimeter = 0;
  std::vector<pair<int, int>> queue({std::pair<int, int>({i, j})});
  const std::pair<int, int> UP({1, 0});
  const std::pair<int, int> RIGHT({0, 1});
  const std::pair<int, int> LEFT({0, -1});
  const std::pair<int, int> DOWN({-1, 0});

  const std::vector<std::pair<int, int>> directions({
      UP,    // up
      DOWN,  // down
      RIGHT, // right
      LEFT,  // left
  });

  const std::vector<std::vector<std::pair<int, int>>> corners({
      {UP, LEFT},   // top left
      {UP, RIGHT},  // top right
      {DOWN, LEFT}, // bottom left
      {DOWN, RIGHT} // bottom right
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
        }
      }
      for (auto &corner : corners) {
        int first_x = x + corner[0].first;
        int first_y = y + corner[0].second;
        int second_x = x + corner[1].first;
        int second_y = y + corner[1].second;
        bool has_outer_corner = (!in_bounds(matrix, first_x, first_y) ||
                           matrix[first_x][first_y] != value) &&
                          (!in_bounds(matrix, second_x, second_y) ||
                           matrix[second_x][second_y] != value);
        bool has_inner_corner = (in_bounds(matrix, first_x, first_y) &&
                                 matrix[first_x][first_y] == value) &&
                                (in_bounds(matrix, second_x, second_y) &&
                                 matrix[second_x][second_y] == value) &&
                                (in_bounds(matrix, first_x, second_y) &&
                                 matrix[first_x][second_y] != value);
        if (has_outer_corner || has_inner_corner) {
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
