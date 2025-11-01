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

/**
idea: use dijkstra's?

- a mapping of tiles to scores.
- start from 'S', facing EAST
each position has 4 edges with the weights of:
- current direction: 1
- left/right: 91
- 180 degreees: 181
- my endgoal is when I reach 'E'

bugs:
- once distance is more than 4, distance calculation goes haywire - need to
update distances
- cannot handle turns

how to handle turns:
- the queue starts off with invalid turns - should not add invalid directions.
- also the PQ can have stale entries, use a visited set to avoid this

 */
using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

pr find_position(matrix<char> &m, char pos) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[0].size(); j++) {
      if (m[i][j] == pos) {
        return pr({i, j});
      }
    }
  }
  return pr({0, 0});
}

/**
first Item: coordinate
second item: direction
third item: distance
 */
using Item = std::tuple<pr, pr, int>;

const vector<pr> directions({
    {1, 0},  // up
    {0, 1},  // right
    {-1, 0}, // down
    {0, -1}  // left
});

const vector<std::pair<pr, int>> down_neighbours({{pr({1, 0}), 1},
                                                  {pr({0, 1}), 1001},
                                                  {pr({-1, 0}), 2001},
                                                  {pr({0, -1}), 1001}});
std::vector<std::pair<pr, int>> right_neighbours({{pr({1, 0}), 1001},
                                                  {pr({0, 1}), 1},
                                                  {pr({-1, 0}), 1001},
                                                  {pr({0, -1}), 2001}});
std::vector<std::pair<pr, int>> left_neighbours({{pr({1, 0}), 2001},
                                                 {pr({0, 1}), 1001},
                                                 {pr({-1, 0}), 1},
                                                 {pr({0, -1}), 1001}});
std::vector<std::pair<pr, int>> up_neighbours({{pr({1, 0}), 1001},
                                               {pr({0, 1}), 2001},
                                               {pr({-1, 0}), 1001},
                                               {pr({0, -1}), 1}});
std::vector<std::pair<pr, int>> derive_neighbours(const pr &direction) {
  if (direction == pr({1, 0})) {
    return down_neighbours;
  } else if (direction == pr({0, 1})) {
    return right_neighbours;
  } else if (direction == pr({-1, 0})) {
    return left_neighbours;
  } else {
    return up_neighbours;
  }
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
    while (getline(test_case, line)) {
      m.emplace_back(line.begin(), line.end());
    }

    pr start = find_position(m, 'S');
    pr dest = find_position(m, 'E');
    unordered_map<pr, int, pair_hash> dist(8, pair_hash{});
    auto cmp = [](Item &left, Item &right) {
      return std::get<2>(left) > std::get<2>(right);
    };
    std::priority_queue<Item, std::vector<Item>, decltype(cmp)> queue(cmp);
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m[0].size(); j++) {
        dist[pr({i, j})] = 1000000000;
      }
    }
    dist[start] = 0;
    unordered_set<pr, pair_hash> encountered(8, pair_hash{});
    // queue items need to be updated
    queue.push(std::tuple<pr, pr, int>({start, pr(0, 1), 0}));

    // why isn't the first item the one of least distance?
    while (!queue.empty()) {
      auto [u, direction, d] = queue.top();
      if (encountered.count(u) == 0) {
        encountered.insert(u);
        auto neighbours = derive_neighbours(direction);
        for (auto [dir, distance] : neighbours) {
          pr neighbour = u + dir;
          if (m[neighbour] != '#') {
            long alt = dist[u] + distance;
            if (alt < dist[neighbour]) {
              dist[neighbour] = alt;
              queue.push(std::tuple<pr, pr, int>({neighbour, dir, alt}));
            }
          }
        }
      }
      queue.pop();
    }
    ans = dist[dest];
  }

  cout << fixed << ans << endl;
  return 0;
}
