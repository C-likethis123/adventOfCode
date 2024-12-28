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
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**

the first price has no associated change
need to determine which sequence of 4 changes will give you the most bananas
overall.

easy to determine for one secret number

but the same sequence has to apply for multiple secret numbers....

brute force:
- for every sequence of secret numbers, store the sequence of 4 items in a map +
number
- after every sequence is generated, update the "main" sequence

- iterate through the main sequence and find the maximum number.




 */

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

using Sequence = vector<int>;
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

/**
how to hash a tuple with positive and negative numbers.....

 */
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
    auto hash = [](const Sequence &s1) {
      size_t h = 0;
      for (int i : s1) {
        h = h * 31 + std::hash<int>{}(i);
      }
      return h;
    };
    unordered_map<Sequence, long, decltype(hash)> total_bananas(8, hash);
    while (getline(test_case, line)) {
      long number = stol(line);
      int ones = number % 10;
      Sequence seq;
      unordered_set<Sequence, decltype(hash)> current_sequence(8, hash);
      for (int i = 0; i < 2000; ++i) {
        long new_number = transform(number);
        int new_ones = new_number % 10;
        seq.push_back(new_ones - ones);
        if (seq.size() > 4) {
          seq.erase(seq.begin());
        }
        if (seq.size() == 4 &&current_sequence.count(seq) == 0) {
            current_sequence.insert(seq);
            total_bananas[seq] += new_ones;
        }
        number = new_number;
        ones = new_ones;
      }
    }
    for (auto &[_, total] : total_bananas) {
      if (total > ans) {
        ans = total;
      }
    }
  }
  cout << fixed << ans << endl;
  return 0;
}
