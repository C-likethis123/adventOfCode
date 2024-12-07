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
should find two MAS in the shape of an X.
within the X, each MAS can be written forwards or backwards.

0.008-0.011

inlining it: performance is about the same, with a slight increase
*/
#define N 140

using namespace std;

inline bool in_bounds(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

bool is_valid_diagonal(vector<vector<char>> &matrix, std::pair<int, int> &first,
                       std::pair<int, int> &second) {
  return in_bounds(first.first, first.second) &&
         in_bounds(second.first, second.second) &&
         ((matrix[first.first][first.second] == 'S' &&
           matrix[second.first][second.second] == 'M') ||
          (matrix[first.first][first.second] == 'M' &&
           matrix[second.first][second.second] == 'S'));
}
int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  vector<vector<char>> matrix(N);
  // ofstream debug("output.txt");

  if (test_case.is_open()) {
    for (int r = 0; r < N; r++) {
      getline(test_case, line);
      vector<char> row(N);
      for (int i = 0; i < N; i++) {
        row[i] = line[i];
      }
      matrix[r] = row;
    }

    // do something here
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // find an 'A'
        if (matrix[i][j] == 'A') {
          // check if diagonals are valid
          std::pair<int, int> top_left({i - 1, j - 1});
          std::pair<int, int> bottom_right({i + 1, j + 1});
          std::pair<int, int> top_right({i - 1, j + 1});
          std::pair<int, int> bottom_left({i + 1, j - 1});
          bool is_valid_left_diagonal =
              is_valid_diagonal(matrix, top_left, bottom_right);
          bool is_valid_right_diagonal =
              is_valid_diagonal(matrix, top_right, bottom_left);
          ans += is_valid_left_diagonal && is_valid_right_diagonal;
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
