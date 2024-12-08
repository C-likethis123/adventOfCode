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

void find_position(const std::vector<std::vector<char>> &matrix, size_t &curr_x,
                   size_t &curr_y) {
  size_t row_size = matrix.size();
  size_t col_size = matrix[0].size();
  for (size_t i = 0; i < row_size; i++) {
    for (size_t j = 0; j < col_size; j++) {
      if (matrix[i][j] == '^') {
        curr_x = i;
        curr_y = j;
        return;
      }
    }
  }
}

inline bool in_bounds(const std::vector<std::vector<char>> &matrix, int x,
                      int y) {
  return x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size();
}

/**

part 2: get the guard stuck in a loop by adding a single new obstruction.

1. brute force:
- iterate through all positions and place the obstacles
- go through one round until I meet an encountered obstacle at the same
direction.
 */
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
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    vector<vector<char>> matrix;
    while (getline(test_case, line)) {
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      matrix.emplace_back(row);
    }
    vector<pair<int, int>> directions({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});

    size_t x = 0;
    size_t y = 0;
    find_position(matrix, x, y);

    // very bad example, don't do this
    for (size_t pos_x = 0; pos_x < matrix.size(); pos_x++) {
      for (size_t pos_y = 0; pos_y < matrix.size(); pos_y++) {
        if (matrix[pos_x][pos_y] == '#' || matrix[pos_x][pos_y] == '^') {
          continue;
        }
        int curr_x = x;
        int curr_y = y;
        int curr = 0;
        matrix[pos_x][pos_y] = 'O';
        unordered_map<flattened_index, unordered_set<direction>> encountered;
        bool is_stuck = true;
        while (true) {
          if (matrix[curr_x][curr_y] != 'X') {
            matrix[curr_x][curr_y] = 'X';
          }
          if (encountered[curr_x * matrix.size() + curr_y].count(curr)) {
            break;
          }
          encountered[curr_x * matrix.size() + curr_y].insert(curr);
          int forward_position_x = curr_x + directions[curr].first;
          int forward_position_y = curr_y + directions[curr].second;

          if (!in_bounds(matrix, forward_position_x, forward_position_y)) {
            is_stuck = false;
            break;
          }
          while (matrix[forward_position_x][forward_position_y] == '#' ||
                 matrix[forward_position_x][forward_position_y] == 'O') {
            curr = (curr + 1) % 4;
            forward_position_x = curr_x + directions[curr].first;
            forward_position_y = curr_y + directions[curr].second;
          }
          curr_x = forward_position_x;
          curr_y = forward_position_y;
        }

        matrix[pos_x][pos_y] = 'X';
        if (is_stuck) {
          ans += 1;
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
