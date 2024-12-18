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
  if (test_case.is_open()) {
    std::regex buttonA("Button A: X\\+(\\d+), Y\\+(\\d+)");
    std::regex buttonB("Button B: X\\+(\\d+), Y\\+(\\d+)");
    std::regex prizes("Prize: X=(\\d+), Y=(\\d+)");

    std::smatch matches;
    while (getline(test_case, line)) {
      // get button A stuff
      pr buttonAPresses({0, 0});
      pr buttonBPresses({0, 0});
      long X;
      long Y;
      if (std::regex_search(line, matches, buttonA)) {
        buttonAPresses.first = stol(matches[1]);
        buttonAPresses.second = stol(matches[2]);
      }
      getline(test_case, line);
      if (std::regex_search(line, matches, buttonB)) {
        buttonBPresses.first = stol(matches[1]);
        buttonBPresses.second = stol(matches[2]);
      }
      getline(test_case, line);
      if (std::regex_search(line, matches, prizes)) {
        X = stol(matches[1]);
        Y = stol(matches[2]);
      }
      getline(test_case, line);

      // use simultaneous equations
      long factor = buttonAPresses.first * buttonBPresses.second -
                    buttonAPresses.second * buttonBPresses.first;
      long total = Y * buttonAPresses.first - X * buttonAPresses.second;
      if (total % factor == 0) {
        // possible, so figure out the coins I need
        long b = total / factor;
        long a = (X - buttonBPresses.first * b) / buttonAPresses.first;
        ans += a * 3 + b;
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
