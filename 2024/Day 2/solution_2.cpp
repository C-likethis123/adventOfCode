#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> split(string s, string delimiter) {
  vector<int> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(std::stoi(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(std::stoi(s));
  return v;
}
/*
brute force: for every level, compute if removing the report would make it safe.
- would be O(2n)
*/

int compare(int x, int y) {
  if (x == y) {
    return 0;
  }
  if (x < y) {
    return -1;
  }
  return 1;
}

bool is_safe(vector<int> &sequence) {
  for (size_t i = 0; i < sequence.size() - 1; i++) {
    int current_polarity = compare(sequence[i], sequence[i + 1]);
    if (i > 0) {
      int previous_polarity = compare(sequence[i - 1], sequence[i]);
      if (current_polarity != previous_polarity) {
        return false;
      }
    }
    int abs_difference = std::abs(sequence[i] - sequence[i + 1]);
    if (abs_difference == 0 || abs_difference > 3) {
      return false;
    }
  }
  return true;
}

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");

  if (test_case.is_open()) {
    while (getline(test_case, line)) {
      // TODO: figure out a more elegant way to do this
      vector<int> sequence = split(line, " ");
      bool is_safe_report = is_safe(sequence);

      // found a number that makes it unsafe
      if (!is_safe_report) {
        // try skipping all numbers
        for (size_t skip = 0; skip < sequence.size(); skip++) {
          vector<int> temp;
          for (size_t i = 0; i < sequence.size(); i++) {
            if (i != skip) {
              temp.emplace_back(sequence[i]);
            }
          }
          if (is_safe(temp)) {
            is_safe_report = true;
            break;
          }
        }
      }

      ans += is_safe_report;
    }
    cout << fixed << ans << endl;
  }
  return 0;
}
