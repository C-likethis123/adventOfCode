
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

using pr = user_defined::pair<int>;

template <typename Hash>
long compute_cost(vector<vector<char>> &matrix,
                  unordered_set<pr, Hash> &encountered, int i,
                  int j) {
  long area = 0;
  long perimeter = 0;
  std::vector<pr> queue({pr({i, j})});
  const pr UP({1, 0});
  const pr RIGHT({0, 1});
  const pr LEFT({0, -1});
  const pr DOWN({-1, 0});

  const std::vector<pr> directions({
      UP,    // up
      DOWN,  // down
      RIGHT, // right
      LEFT,  // left
  });

  const std::vector<std::vector<pr>> corners({
      {UP, LEFT},   // top left
      {UP, RIGHT},  // top right
      {DOWN, LEFT}, // bottom left
      {DOWN, RIGHT} // bottom right
  });

  while (!queue.empty()) {
    auto p = queue.front();
    auto [x, y] = p;
    char value = matrix[x][y];
    if (encountered.count(p) == 0) {
      encountered.insert(p);
      area += 1;
      for (auto &direction : directions) {
        auto [new_x, new_y] = p + direction;
        if (in_bounds(matrix, new_x, new_y) && matrix[new_x][new_y] == value) {
          queue.emplace_back(pr({new_x, new_y}));
        }
      }
      for (auto &corner : corners) {
        auto [first_x, first_y] = p + corner[0];
        auto [second_x, second_y] = p + corner[1];
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
    auto hashfn = [&matrix](const pr &p) {
      int size = matrix.size();
      return p.first * size + p.second;
    };
    unordered_set<pr, decltype(hashfn)> encountered(8, hashfn);
    while (getline(test_case, line)) {
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      matrix.emplace_back(row);
    }

    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[0].size(); j++) {
        if (encountered.count(pr({i, j})) == 0) {
          ans += compute_cost(matrix, encountered, i, j);
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
