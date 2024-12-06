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

/*
idea: use regex :D
*/

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");
  std::regex reg_exp("mul\\((\\d+),(\\d+)\\)");
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      auto words_begin =
          std::sregex_iterator(line.begin(), line.end(), reg_exp);
      auto words_end = std::sregex_iterator();

      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        ans += stoi(match[1]) * stoi(match[2]);
      }
    }

    cout << fixed << ans << endl;
  }
  return 0;
}
