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

/**

find number of cheats.

assumption: there is only one path.

a cheat is an "edge".
because I only have 2 picoseconds of cheats, I can only go through one layer of
walls.

maybe an idea:
- while I go through the path, keep track of the distance between two points.
- assumption is that there is only one path, the path is denoted by '.', so i
can freely traverse without needing to keep track of dead ends or alternative
paths
- i can make a map of points vs index.
- iterate through the matrix and keep track of 'cheats'. a cheat takes 2 steps.
- if the distance between the points - 2 is 100, increment the count

- i can use bfs/dfs?
- store the nodes in a map with the order.
- iterate through the list of cheats
  - note to self: (s, e) and (e,s) is the same cheat.
  - cheat saving time is the distance between the two points on that path.


- cheats: only vertical and horizontal cheats
  - iterate through the matrix, if there is '#', check the four directions

 */
using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

using Cheat = std::pair<pr, pr>;

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
      vector<char> row;
      for (char c : line) {
        row.emplace_back(c);
      }
      m.emplace_back(row);
    }

    vector<Cheat> cheats;
    unordered_map<pr, long, pair_hash> distances(8, pair_hash(m.size()));
    pr start = m.find_position('S');
    vector<pr> queue({start});
    distances[start] = 0;
    long dist = 0;

    // store distances
    while (!queue.empty()) {
      auto u = queue.front();
      for (const pr &dir : user_defined:: directions) {
        pr neighbour = u + dir;
        if (m.in_bounds(neighbour) && m[neighbour] != '#' &&
            distances.count(neighbour) == 0) {
          distances[neighbour] = dist++;
          queue.push_back(neighbour);
        }
      }
      queue.erase(queue.begin());
    }

    for (int i = 0; i < m.size(); ++i) {
      for (int j = 0; j < m[0].size(); ++j) {
        if (m[i][j] == '#') {
          pr pos = pr({i, j});
          pr left = pos + pr({0, -1});
          pr right = pos + pr({0, 1});
          pr up = pos + pr({-1, 0});
          pr down = pos + pr({1, 0});
          if (m.in_bounds(left) && m[left] != '#' && m.in_bounds(right) &&
              m[right] != '#') {
            cheats.emplace_back(std::make_pair(left, right));
          }
          if (m.in_bounds(up) && m[up] != '#' && m.in_bounds(down) &&
              m[down] != '#') {
            cheats.emplace_back(std::make_pair(up, down));
          }
        }
      }
    }

    for (const auto &[left, right] : cheats) {
      debug << abs(distances[left] - distances[right]) << endl;
      if (abs(distances[left] - distances[right]) >= 102) {
        ans += 1;
      }
    }

    cout << fixed << ans << endl;
    debug << "cheats number: " << cheats.size() << endl;
    return 0;
  }
}

/**

debugging:
- wrong at 10 picoseconds: should be 4, not 5
- no cheat at 66 seconds, but there's a cheat for 65 seconds

there are only 44 cheats, but my solution provided 63 cheats - wrong bounds checking + didn't account for start and end
 */