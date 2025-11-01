#include "user_defined.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
time:
./a.out input.txt  0.33s user 0.01s system 37% cpu 0.878 total
*/

void transform(long x, std::vector<long> &res) {
  if (x == 0) {
    res.push_back(1);
  } else {
    // Count digits
    long temp = x;
    int digits = 0;
    while (temp) {
      digits++;
      temp /= 10;
    }

    if (digits % 2 == 0) {
      long pow10 = 1;
      for (int i = 0; i < digits / 2; ++i)
        pow10 *= 10;
      res.push_back(x / pow10);
      res.push_back(x % pow10);
    } else {
      res.push_back(x * 2024);
    }
  }
}

using namespace std;
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
    getline(test_case, line);
    vector<long> stones = user_defined::split_int<long>(line, " ");

    for (int i = 0; i < 25; i++) {
      vector<long> res;
      res.reserve(stones.size() * 2); // heuristic
      for (long &s : stones) {
        transform(s, res); // not much difference whether it's moved?
      }
      std::swap(stones, res);
    }
    ans = stones.size();
  }

  cout << fixed << ans << endl;
  return 0;
}
