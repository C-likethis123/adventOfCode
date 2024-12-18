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

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  std::regex reg_exp("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
  long first_quart = 0;
  long second_quart = 0;
  long third_quart = 0;
  long fourth_quart = 0;
  const int SECONDS = 100;
  const int ROWS = 103;
  const int COLS = 101;
  int first_quart_x = (COLS - 1) / 2 - 1;
  int second_quart_x = (COLS - 1) / 2 + 1;
  int first_quart_y = (ROWS - 1) / 2 - 1;
  int second_quart_y = (ROWS - 1) / 2 + 1;

  if (test_case.is_open()) {
    std::smatch matches;
    
    while (getline(test_case, line)) {
      if (std::regex_search(line, matches, reg_exp)) {
        long x = stoi(matches[1]);
        long y = stoi(matches[2]);
        long x_velocity = stoi(matches[3]);
        long y_velocity = stoi(matches[4]);
        for (int i = 0; i < SECONDS; i++) {
          x += x_velocity;
          if (x < 0) {
            x = COLS + x;
          } else if (x >= COLS) {
            x = x % COLS;
          }
          y += y_velocity;
          if (y < 0) {
            y = ROWS + y;
          } else if (y >= ROWS) {
            y = y % ROWS;
          }
        }

        if (x <= first_quart_x ) {
          if (y <= first_quart_y) {
            first_quart += 1;
          } else if (y >= second_quart_y) {
            second_quart += 1;
          }
        } else if (x >= second_quart_x) {
          if (y <= first_quart_y) {
            third_quart += 1;
          } else if (y >= second_quart_y) {
            fourth_quart += 1;
          }
        }
      }
    }
  }

  ans = first_quart * second_quart * third_quart * fourth_quart;
  cout << fixed << ans << endl;
  return 0;
}
