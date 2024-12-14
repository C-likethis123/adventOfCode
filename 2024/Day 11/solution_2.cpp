#include "stone.h"
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
Some observations:
1. the list will only increase in length if the stones are split. Otherwise, it
stays the same.
2. What if I computed the number of times it transformed before it split,
followed by how much it split to?

Looks like i'm not so good at memoisation after all. I tried to do a twisted form of memoisation
where I stored the number of times a stone stays as 1 before it gets split into 2, but I wasn't very successful.
The trick is that if there is X amount of stones with the same number and they get split, the total number of stones increases by X. 
This is much more effective than adding the stones up one by one.

actual memoisation: 
- ./a.out input.txt  0.01s user 0.00s system 2% cpu 0.294 total

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
    unordered_map<long, vector<long>> previous;
    vector<long> stones = split_long(line, " ");
    unordered_map<long, long> counts;
    for (auto &x : stones) {
      counts[x] += 1;
    }

    for (int i = 0; i < 25; i++) {
      unordered_map<long, long> next_counts;
      for (auto &[stone, count] : counts) {
        if (previous.count(stone) > 0) {
          auto &vec = previous[stone];
          for (const auto &x : vec) {
            next_counts[x] += count;
          }
        } else {
          vector<long> t = Stone::transform(stone);
          for (const auto &x : t) {
            next_counts[x] += count;
          }
          previous[stone] = t;
        }
      }
      counts = next_counts;
    }
    for (auto &[stone, count] : counts) {
        ans += count;
    }
  }
  cout << fixed << ans << endl;
  return 0;
}
