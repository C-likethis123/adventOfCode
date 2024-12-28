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

/**

look for sets of 3 computers where each computer is connected to the other 2
computers How many sets of interconnected computers start with a t?


brute force:
- start a store
- for every incoming set, store them in a mapping.
- if there is a set of 3 interconnected computers, store them and check if it
begins with t.
 */

using Interconnected = std::vector<string>;

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
    unordered_map<string, vector<string>> edges;
    auto hash = [](const Interconnected &i) {
      std::size_t seed = 0;
      std::hash<std::string> hasher;
      for (const auto &str : i) {
        seed ^= hasher(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    };
    unordered_set<Interconnected, decltype(hash)> encountered(8, hash);
    while (getline(test_case, line)) {
      vector<string> x = user_defined::split(line, "-");
      edges[x[0]].emplace_back(x[1]);
      edges[x[1]].emplace_back(x[0]);
    }

    for (const auto &[first, neighbors] : edges) {
      for (size_t i = 0; i < neighbors.size(); ++i) {
        const string &second = neighbors[i];
        for (size_t j = i + 1; j < neighbors.size(); ++j) {
          const string &third = neighbors[j];
          // Check if second and third are connected
          if (std::find(edges[second].begin(), edges[second].end(), third) !=
              edges[second].end()) {
            Interconnected triangle = {first, second, third};
            std::sort(triangle.begin(), triangle.end());
            if (encountered.count(triangle) == 0) {
              encountered.insert(triangle);
              ans += first[0] == 't' || second[0] == 't' || third[0] == 't';
            }
          }
        }
      }
    }
    cout << fixed << ans << endl;
    return 0;
  }
}