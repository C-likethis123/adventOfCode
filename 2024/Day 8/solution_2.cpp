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
using namespace std;

/**
to compile this: clang++ -I/(project root)/include solution.cpp && ./a.out
input2.txt
 */
vector<vector<char>> matrix;
bool in_bounds(user_defined::pair &p1) {
  return p1.first >= 0 && p1.first < matrix.size() && p1.second >= 0 &&
         p1.second < matrix[0].size();
}

vector<user_defined::pair> get_possible_locations(user_defined::pair &p1,
                                                  user_defined::pair &p2) {
  std::vector<user_defined::pair> res;
  int horizontal_distance = p1.first - p2.first;
  int vertical_distance = p1.second - p2.second;

  // in one distance
  user_defined::pair next_location({
      p1.first + horizontal_distance,
      p1.second + vertical_distance,
  });
  while (in_bounds(next_location)) {
    res.emplace_back(next_location);
    next_location = user_defined::pair({
        next_location.first + horizontal_distance,
        next_location.second + vertical_distance,
    });
  }

  // in another distance
  next_location = user_defined::pair(
      {p2.first - horizontal_distance, p2.second - vertical_distance});

  while (in_bounds(next_location)) {
    res.emplace_back(next_location);
    next_location = user_defined::pair({
        next_location.first - horizontal_distance,
        next_location.second - vertical_distance,
    });
  }

  return res;
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
      vector<char> row;
      for (char &c : line) {
        row.emplace_back(c);
      }
      matrix.emplace_back(row);
    }

    // get all antennas
    unordered_map<char, vector<user_defined::pair>> antennas;
    for (size_t i = 0; i < matrix.size(); i++) {
      for (size_t j = 0; j < matrix[0].size(); j++) {
        if (matrix[i][j] != '.') {
          antennas[matrix[i][j]].emplace_back(user_defined::pair(i, j));
        }
      }
    }

    // iterate through all antennas to get antinodes
    size_t size = matrix.size();
    auto hash = [&size](const user_defined::pair &p) {
      return p.first * size + p.second;
    };
    unordered_set<user_defined::pair, decltype(hash)> antinodes(8, hash);
    for (auto &group : antennas) {
      vector<user_defined::pair> group_antennas = group.second;
      for (size_t i = 0; i < group_antennas.size() - 1; i++) {
        for (size_t j = i + 1; j < group_antennas.size(); j++) {
          vector<user_defined::pair> possible_locations =
              get_possible_locations(group_antennas[i], group_antennas[j]);
          for (auto &location : possible_locations) {
            debug << "location: " << location << endl;
            antinodes.insert(location);
          }
        }
      }
      // antennas are also antinodes, add them in
      for (const auto& antenna : group_antennas) {
        antinodes.insert(antenna);
      }
    }

    ans = antinodes.size();
  }

  cout << fixed << ans << endl;
  return 0;
}
