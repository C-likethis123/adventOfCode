
#include "stone.h"
#include "user_defined.h"
#include <pthread.h>
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

/*
time at n = 25:
./a.out input.txt  0.33s user 0.01s system 37% cpu 0.878 total

if I reused the same objects instead of creating new ones:
./a.out input.txt  0.22s user 0.00s system 31% cpu 0.707 total


at n = 35:
./a.out input.txt  14.01s user 0.15s system 97% cpu 14.539 total
n=35, with std::move:
./a.out input.txt  14.67s user 0.15s system 96% cpu 15.321 total


at n = 75, it got too long that I was witing even after seconds

// try:
only add if there is a new stone. don't move original stones.
n = 25
./a.out input.txt  0.10s user 0.00s system 16% cpu 0.643 total
n = 35
./a.out input.txt  6.40s user 0.06s system 93% cpu 6.904 total

// add if there are new stones + multithreading?
*/

using namespace std;

std::vector<long> split_long(std::string s, std::string delimiter) {
  std::vector<long> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(std::stol(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(std::stol(s));
  return v;
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
    getline(test_case, line);
    vector<Stone> stones;
    vector<long> temp = split_long(line, " ");
    for (long t : temp) {
      stones.emplace_back(t);
    }

    for (int i = 0; i < 35; i++) {
      vector<Stone> res;
      for (Stone &s : stones) {
        vector<Stone> transformed_stones = Stone::transform(s); 
        for (Stone &t : transformed_stones) {
          res.push_back(t);
        }
      }
      for (Stone &x : res) {
        stones.emplace_back(x);
      }
    }
    ans = stones.size();
  }

  cout << fixed << ans << endl;
  return 0;
}
