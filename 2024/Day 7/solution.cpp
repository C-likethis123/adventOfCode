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

vector<vector<char>> generate_outcomes(size_t n) {
  if (n == 0) {
    return vector<vector<char>>({{}});
  }
  vector<vector<char>> previous_outcome = generate_outcomes(n - 1);
  vector<vector<char>> current_outcome;
  vector<char> additions({'*', '+'});
  for (const char &addition : additions) {
    for (auto &outcome : previous_outcome) {
      vector<char> new_outcome({addition});
      for (const auto item : outcome) {
        new_outcome.emplace_back(item);
      }
      current_outcome.emplace_back(new_outcome);
    }
  }
  return current_outcome;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "supply filename";
    return -1;
  }
  long ans = 0;
  string line;
  ifstream test_case(argv[1]);
  std::regex re("(\\d+)");
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      // parsing logic has no issues
      std::sregex_iterator it(line.begin(), line.end(), re);
      std::sregex_iterator end;
      long first = stol((*it)[1]);
      vector<long> numbers;
      while (++it != end) {
        numbers.emplace_back(stol((*it)[1]));
      }

      vector<vector<char>> outcomes = generate_outcomes(numbers.size() - 1);
      for (auto &outcome : outcomes) {
        long sum = numbers[0];
        for (size_t i = 0; i < outcome.size(); i++) {
          if (outcome[i] == '*') {
            sum *= numbers[i + 1];
          } else {
            sum += numbers[i + 1];
          }
        }
        if (sum == first) {
          ans += first;
          break;
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
