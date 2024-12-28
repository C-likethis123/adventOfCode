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

long transform(long number) {
  long mult = number * 64;
  number ^= mult;
  number %= 16777216;
  long div = number / 32;
  number ^= div;
  number %= 16777216;
  long mult2048 = number * 2048;
  number ^= mult2048;
  number %= 16777216;
  return number;
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
    while (getline(test_case, line)) {
      long number = stol(line);
      for (int i = 0; i < 2000; i++) {
        number = transform(number);
      }
      debug << number << endl;
      ans += number;
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
