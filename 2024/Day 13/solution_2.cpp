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
using pr = user_defined::pair<long long>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

int main(int argc, const char *argv[]) {
  long long ans = 0;
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
      long long X;
      long long Y;
      if (std::regex_search(line, matches, buttonA)) {
        buttonAPresses.first = stoll(matches[1]);
        buttonAPresses.second = stoll(matches[2]);
      }
      getline(test_case, line);
      if (std::regex_search(line, matches, buttonB)) {
        buttonBPresses.first = stoll(matches[1]);
        buttonBPresses.second = stoll(matches[2]);
      }
      getline(test_case, line);
      if (std::regex_search(line, matches, prizes)) {
        X = 10000000000000 + stoll(matches[1]);
        Y = 10000000000000 + stoll(matches[2]);
      }
      getline(test_case, line);

      // use simultaneous equations
      long long factor = buttonAPresses.first * buttonBPresses.second -
                         buttonAPresses.second * buttonBPresses.first;
      long long total = Y * buttonAPresses.first - X * buttonAPresses.second;
      if (total % factor == 0) {
        // possible, so figure out the coins I need
        long long b = total / factor;
        long long totalA = (X - buttonBPresses.first * b);
        if (totalA % buttonAPresses.first == 0) {
          long long a = totalA / buttonAPresses.first;
          if (a >= 0 && b >= 0) {
            ans += a * 3 + b;
          }
        }
      }

    }
  }

  cout << fixed << ans << endl;
  return 0;
}
