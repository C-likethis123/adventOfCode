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

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  const std::regex gates("(.+): (\\d)");
  const std::regex connections("(.+) (AND|XOR|OR) (.+) -> (.+)");
  std::smatch match;
  std::vector<std::vector<string>> connections_list;
  const std::unordered_map<std::string, std::function<int(int, int)>> operators{
      {"AND", [](int x1, int x2) { return x1 & x2; }},
      {"OR", [](int x1, int x2) { return x1 | x2; }},
      {"XOR", [](int x1, int x2) { return x1 ^ x2; }},
  };
  if (test_case.is_open()) {
    unordered_map<string, int> gate_mappings;
    while (getline(test_case, line) && !line.empty()) {
      if (std::regex_search(line, match, gates)) {
        gate_mappings[match[1]] = stoi(match[2]);
      }
    }

    while (getline(test_case, line)) {
      if (std::regex_search(line, match, connections)) {
        connections_list.push_back({match[1], match[2], match[3], match[4]});
      }
    }
    // only compute items where both inputs are present
    while (!connections_list.empty()) {
      for (int i = 0; i < connections_list.size(); ++i) {
        const auto &connection = connections_list[i];
        if (gate_mappings.count(connection[0]) &&
            gate_mappings.count(connection[2])) {
          gate_mappings[connection[3]] = (operators.at(connection[1]))(
              gate_mappings[connection[0]], gate_mappings[connection[2]]);
          connections_list.erase(connections_list.begin() + i);
          break;
        }
      }
    }

    // combine the bits together, sort, and produce the binary
    std::vector<string> list_start_z;
    for (const auto &x : gate_mappings) {
      if (x.first.rfind("z") == 0) {
        list_start_z.push_back(x.first);
      }
    }
    sort(list_start_z.begin(), list_start_z.end(), [](string &s1, string &s2) {
      return stoi(s1.substr(1)) > stoi(s2.substr(1));
    });

    for (const string &s : list_start_z) {
      ans = ans << 1;
      ans |= gate_mappings[s];
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
