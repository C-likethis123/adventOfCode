#include "ud_matrix.h"
#include "user_defined.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/**
to compile this: clang++ -I/(project root)/include solution.cpp && ./a.out
input2.txt

256

real    0m0.228s
user    0m0.003s
sys     0m0.003s
 */

using pr = user_defined::pair<int>;
using matrix = user_defined::matrix<char>;

matrix m;
vector<pr> get_possible_locations(pr &p1, pr &p2) {
  int horizontal_distance = p1.first - p2.first;
  int vertical_distance = p1.second - p2.second;

  return vector<pr>({
      {p1.first + horizontal_distance, p1.second + vertical_distance},
      {p2.first - horizontal_distance, p2.second - vertical_distance},
  });
}

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
    while (getline(test_case, line)) {
      m.emplace_back(line.begin(), line.end());
    }

    // get all antennas
    unordered_map<char, vector<pr>> antennas;
    for (size_t i = 0; i < m.size(); i++) {
      for (size_t j = 0; j < m[0].size(); j++) {
        if (m[i][j] != '.') {
          antennas[m[i][j]].emplace_back(pr(i, j));
        }
      }
    }

    // iterate through all antennas to get antinodes
    unordered_set<pr, user_defined::pair_hash<int>> antinodes(
        8, user_defined::pair_hash<int>{});
    for (auto &group : antennas) {
      vector<pr> group_antennas = group.second;
      for (size_t i = 0; i < group_antennas.size() - 1; i++) {
        for (size_t j = i + 1; j < group_antennas.size(); j++) {
          vector<pr> possible_locations =
              get_possible_locations(group_antennas[i], group_antennas[j]);
          // debug << "antenna 1: " << group_antennas[i] << endl;
          // debug << "antenna 2: " << group_antennas[j] << endl;
          for (auto &location : possible_locations) {
            if (m.in_bounds(location)) {
              // debug << "location: " << location << endl;
              antinodes.insert(location);
            }
          }
        }
      }
    }

    ans = antinodes.size();
  }

  cout << fixed << ans << endl;
  return 0;
}
