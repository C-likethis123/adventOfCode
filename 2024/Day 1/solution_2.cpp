#include <algorithm>
#include <bitset>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void split(string s, std::vector<int> &v, string delimiter) {
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
}

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");

  if (test_case.is_open()) {
    // parse into two lists
    vector<int> sequence;
    unordered_map<int, int> frequency_map;
    while (getline(test_case, line)) {
      // TODO: figure out a more elegantway to do this
      vector<int> split_int;
      split(line, split_int, " ");
      sequence.emplace_back(split_int[0]);
      frequency_map[split_int[1]] += 1;
    }


    // get distance
    for (int num : sequence) {
      ans += num * frequency_map[num];
    }
    cout << fixed << ans << endl;
  }
  return 0;
}
