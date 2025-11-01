#include "user_defined.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_safe_report(const vector<int> &sequence) {
  if (sequence.size() < 2) {
    return false;
  }
  // reverse it to see if it helps
  bool increasing = sequence[1] > sequence[0];
  for (size_t i = 1; i < sequence.size() - 1; i++) {
    bool polarity = sequence[i] < sequence[i + 1];
    if (polarity != increasing) {
      return false;
    }
    int difference = std::abs(sequence[i] - sequence[i + 1]);
    if (difference < 1 || difference > 3) {
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
    // parse into two lists
    while (getline(test_case, line)) {
      vector<int> sequence = user_defined::split_int(line, " ");
      if (is_safe_report(sequence)) {
        ans += 1;
      }
    }
    cout << fixed << ans << endl;
  }
  return 0;
}
