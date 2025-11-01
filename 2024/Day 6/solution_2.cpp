#include "ud_matrix.h"
#include "user_defined.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using pr = user_defined::pair<int>;
template <typename T> using matrix = user_defined::matrix<T>;

const std::vector<pr> directions = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};

pr find_position(const matrix<char> &m) {
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m[0].size(); j++) {
      if (m[i][j] == '^')
        return pr{(int)i, (int)j};
    }
  }
  return pr{-1, -1};
}

typedef int direction;
typedef int flattened_index;

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }

  long ans = 0;
  string line;
  ifstream test_case(argv[1]);

  if (!test_case.is_open()) {
    cerr << "cannot open file\n";
    return -1;
  }

  matrix<char> m;
  while (getline(test_case, line)) {
    m.emplace_back(line.begin(), line.end());
  }

  pr original_pos = find_position(m);
  unordered_set<pr, user_defined::pair_hash<int>> visited_cells;

  // Compute original path
  {
    pr curr_pos = original_pos;
    int curr_dir = 0;
    while (true) {
      if (!m.in_bounds(curr_pos))
        break;
      visited_cells.insert(curr_pos);

      pr next_pos = curr_pos + directions[curr_dir];
      if (!m.in_bounds(next_pos))
        break;

      if (m[next_pos] == '#')
        curr_dir = (curr_dir + 1) % 4;
      else
        curr_pos = next_pos;
    }
  }

  // Test only visited cells
  for (const auto &pos : visited_cells) {
    if (m[pos] == '#' || m[pos] == '^')
      continue;

    char old = m[pos];
    m[pos] = 'O';

    bool is_stuck = false;
    pr curr_pos = original_pos;
    int curr_dir = 0;
    unordered_map<flattened_index, unordered_set<direction>> encountered;

    while (true) {
      flattened_index key = curr_pos.first * m[0].size() + curr_pos.second;
      if (encountered[key].count(curr_dir)) {
        is_stuck = true;
        break;
      }
      encountered[key].insert(curr_dir);

      pr forward_position = curr_pos + directions[curr_dir];
      while (m.in_bounds(forward_position) &&
             (m[forward_position] == '#' || m[forward_position] == 'O')) {
        curr_dir = (curr_dir + 1) % 4;
        forward_position = curr_pos + directions[curr_dir];
      }

      if (!m.in_bounds(forward_position))
        break;
      curr_pos = forward_position;
    }

    if (is_stuck)
      ans++;

    m[pos] = old;
  }

  cout << fixed << ans << endl;
  return 0;
}
