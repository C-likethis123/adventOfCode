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
    int curr_x = x;
    int curr_y = y;
    int curr = 0;
    while (true) {
      if (matrix[curr_x][curr_y] != 'X') {
        ans += 1;
        matrix[curr_x][curr_y] = 'X';
      }
      int forward_position_x = curr_x + directions[curr].first;
      int forward_position_y = curr_y + directions[curr].second;

      if (!in_bounds(matrix, forward_position_x, forward_position_y)) {
        break;
      }
      while (matrix[forward_position_x][forward_position_y] == '#') {
        curr = (curr + 1) % 4;
        forward_position_x = curr_x + directions[curr].first;
        forward_position_y = curr_y + directions[curr].second;
      }
      curr_x = forward_position_x;
      curr_y = forward_position_y;
    }
  }

  cout << fixed << ans << endl;
  return 0;
}