
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
modification: determine the first byte that will cut off the path to the exit.


idea: brute force
- for every byte, add the barrier.
- run dijkstra's and check if I can reach the exit from the start.

*/
using Item = std::pair<pr, int>;

int main(int argc, const char *argv[]) {
  long ans = 0;
  const int ROW = 70;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  matrix<char> m;
  for (int i = 0; i <= ROW; ++i) {
    vector<char> row;
    row.resize(ROW + 1, '.');
    m.emplace_back(row);
  }
  pr start({0, 0});
  pr dest({ROW, ROW});
  const int UNTOUCHED = 1000000000;
  // reversed because i'm representing the coordinates as [y][x]
  const vector<const pr> directions({
      {0, 1},  // down
      {1, 0},  // right
      {0, -1}, // up
      {-1, 0}  // left
  });
  if (test_case.is_open()) {
    int i = 0;
    while (getline(test_case, line)) {
      vector<int> coords = user_defined::split_int(line, ",");
      m[coords[1]][coords[0]] = '#';

      unordered_map<pr, int, pair_hash> dist(8, pair_hash(m.size()));

      auto cmp = [](Item &left, Item &right) {
        return left.second > right.second;
      };
      std::priority_queue<Item, std::vector<Item>, decltype(cmp)> queue(cmp);
      for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
          dist[pr({i, j})] = UNTOUCHED;
        }
      }
      dist[start] = 0;
      unordered_set<pr, pair_hash> encountered(8, pair_hash(m.size()));
      queue.push(Item({start, 0}));

      while (!queue.empty()) {
        auto [u, d] = queue.top();
        if (encountered.count(u) == 0) {
          encountered.insert(u);
          for (auto &dir : directions) {
            pr n = u + dir;
            pr neighbour({n.second, n.first});
            if (m.in_bounds(neighbour) && m[neighbour] != '#') {
              long alt = dist[u] + 1;
              if (alt < dist[n]) {
                dist[n] = alt;
                queue.push(Item({n, alt}));
              }
            }
          }
        }
        queue.pop();
      }

      if (dist[dest] == UNTOUCHED) {
        cout << fixed << coords[0] << "," << coords[1] << endl;
        return 0;
      }
    }
  }
  return 0;
}
