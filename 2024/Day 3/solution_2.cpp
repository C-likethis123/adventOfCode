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
idea:
- within a do() xxxxx don't snippet, do the multiplications in the middle.
- if there's a do() do() don't(), the do() in the middle doesn't do anything to
change the state, so it can be safely ignored.

*/

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");
  std::regex reg_exp("mul\\((\\d+),(\\d+)\\)");
  std::array<std::regex, 2> instructions(
      {std::regex("do\\(\\)"), std::regex("don't\\(\\)")});
  bool curr_instruction = 1;
  const int DONT_INSTRUCTION = 1;
  std::string all_lines;
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      all_lines += line;
    }
    std::smatch multiplications;
    while (!all_lines.empty()) {
      // determine if it's a do or don't instruction
      std::regex_search(all_lines, multiplications,
                        instructions[curr_instruction]);
      bool res = std::regex_search(all_lines, multiplications,
                                   instructions[curr_instruction]);
      if (curr_instruction == DONT_INSTRUCTION && res) {
          line = multiplications.prefix();
          auto words_begin =
              std::sregex_iterator(line.begin(), line.end(), reg_exp);
          auto words_end = std::sregex_iterator();
          for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            ans += stoi(match[1]) * stoi(match[2]);
          }
        }
      all_lines = multiplications.suffix();
      curr_instruction = !curr_instruction;
    }

    cout << fixed << ans << endl;
  }
  return 0;
}
