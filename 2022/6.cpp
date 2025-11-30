#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

long get_characters_processed(std::string_view line, int window_size) {
  unordered_map<char, int> frequencies;
  for (size_t i = 0; i < window_size - 1; ++i) {
    frequencies[line[i]]++;
  }
  int characters_processed = window_size - 1;
  for (size_t i = window_size - 1; i < line.size(); ++i) {
    characters_processed += 1;
    frequencies[line[i]]++;
    if (frequencies.size() == window_size) {
      return characters_processed;
    }
    if (frequencies[line[i - window_size + 1]] == 1) {
      frequencies.erase(line[i - window_size + 1]);
    } else {
      frequencies[line[i - window_size + 1]]--;
    }
  }
  return 0;
}

int main() {
  ifstream test_case("input_6.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_6.txt" << endl;
    return 1;
  }

  string line;

  while (getline(test_case, line) && !line.empty()) {
    string_view sv(line);
    cout << "Part 1: " << get_characters_processed(sv, 4) << endl;
    cout << "Part 2: " << get_characters_processed(sv, 14) << endl;
  }

  return 0;
}
