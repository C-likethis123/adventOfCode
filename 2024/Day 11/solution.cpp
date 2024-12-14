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
#include <unordered_set>
#include <vector>

/*
time: 
./a.out input.txt  0.33s user 0.01s system 37% cpu 0.878 total
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

    for (int i = 0; i < 25; i++) {
      vector<Stone> res;
      for (Stone& s : stones) {
        vector<Stone> transformed_stones = Stone::transform(s); // not much difference whether it's moved?
        for (Stone t : transformed_stones) {
          res.push_back(t);
        }
      }
      stones = res; // not much difference using std::move
    }
    ans = stones.size();
  }

  cout << fixed << ans << endl;
  return 0;
}
