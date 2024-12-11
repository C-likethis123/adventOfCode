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

vector<vector<char>> matrix;
vector<pair<int, int>> get_possible_locations(pair<int, int> &p1,
                                              pair<int, int> &p2) {
  int horizontal_distance = p1.first - p2.first;
  int vertical_distance = p1.second - p2.second;

  return std::vector({
      pair<int, int>(
          {p1.first + horizontal_distance, p1.second + vertical_distance}),
      pair<int, int>(
          {p2.first - horizontal_distance, p2.second - vertical_distance}),
  });
}

bool in_bounds(pair<int, int> &p1) {
  return p1.first >= 0 && p1.first < matrix.size() && p1.second >= 0 &&
         p1.second < matrix[0].size();
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
    unordered_map<char, vector<pair<int, int>>> antennas;
    for (size_t i = 0; i < matrix.size(); i++) {
      for (size_t j = 0; j < matrix[0].size(); j++) {
        if (matrix[i][j] != '.') {
          antennas[matrix[i][j]].emplace_back(std::pair<int, int>(i, j));
        }
      }
    }

    // iterate through all antennas to get antinodes
    size_t size = matrix.size();
    auto hash = [&size](const pair<int, int> &p) {
      return p.first * size + p.second;
    };
    unordered_set<pair<int, int>, decltype(hash)> antinodes(8, hash);
    for (auto &group : antennas) {
      vector<pair<int, int>> group_antennas = group.second;
      for (size_t i = 0; i < group_antennas.size() - 1; i++) {
        for (size_t j = i + 1; j < group_antennas.size(); j++) {
          vector<pair<int, int>> possible_locations =
              get_possible_locations(group_antennas[i], group_antennas[j]);
          debug << "antenna 1: " << group_antennas[i].first << ","
               << group_antennas[i].second << endl;
          debug << "antenna 2: " << group_antennas[j].first << ","
               << group_antennas[j].second << endl;
          for (auto &location : possible_locations) {
            if (in_bounds(location)) {
              debug << "location: " << location.first << "," << location.second
                   << endl;
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
