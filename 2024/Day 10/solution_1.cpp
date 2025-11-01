#include "ud_matrix.h"
#include "user_defined.h"
#include <fstream>
#include <iostream>
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
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

const vector<pr> directions({
    {1, 0},  // up
    {0, 1},  // right
    {-1, 0}, // down
    {0, -1}  // left
});
long compute_trailhead_score(matrix<int> &m, pr &s) {
  // put encountered trailheads here
  unordered_set<pr, pair_hash> encountered(8, pair_hash{});
  deque<pr> queue({s});

  while (!queue.empty()) {
    auto p = queue.front();
    auto value = m[p];

    if (value == 9) {
      // if it is 9, and has not been encountered before, add it to the
      encountered.insert(p);
    } else {
      // go in all directions
      for (const auto &direction : directions) {
        auto new_p = p + direction;
        // "encountered" set check if in bounds + can traverse ( has to be +1
        // than the current element). then put it inside the queue.
        if (m.in_bounds(new_p)) {
          if ((m[new_p] - value) == 1) {
            queue.emplace_back(new_p);
          }
        }
      }
    }
    // pop front element
    queue.pop_front();
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
    matrix<int> m;
    while (getline(test_case, line)) {
      vector<int> row;
      for (char &c : line) {
        row.emplace_back(c - '0');
      }
      m.emplace_back(row);
    }
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m.size(); j++) {
        pr curr({i, j});
        if (m[curr] == 0) {
          ans += compute_trailhead_score(m, curr);
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
