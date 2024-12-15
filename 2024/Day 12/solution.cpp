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

// TIL: to pass in an unordered set with a custom hash, the best way is to
// template it.

long compute_cost(matrix<char> &m, unordered_set<pr, pair_hash> &encountered,
                  const pr &s) {
  long area = 0;
  long perimeter = 0;
  std::vector<pr> queue({s});
  const std::vector<pr> directions({
      {1, 0},  // up
      {0, 1},  // right
      {-1, 0}, // down
      {0, -1}  // left
  });
  while (!queue.empty()) {
    auto p = queue.front();
    char value = m[p];
    if (encountered.count(p) == 0) {
      encountered.insert(p);
      area += 1;
      for (auto &direction : directions) {
        auto new_p = p + direction;
        if (m.in_bounds(new_p) && m[new_p] == value) {
          queue.emplace_back(new_p);
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
    matrix<char> m;

    unordered_set<pr, pair_hash> encountered(8, pair_hash(m.size()));
    while (getline(test_case, line)) {
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      m.emplace_back(row);
    }

    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m[0].size(); j++) {
        if (encountered.count(pr({i, j})) == 0) {
          ans += compute_cost(m, encountered, pr({i, j}));
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
