#include "ud_matrix.h"
#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <deque>
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

template <typename T> using matrix = user_defined::matrix<T>;

/**
Code: '029A'. For every letter:
When there is an input: start from the robot on the keypad. User needs to find
the shortest distance.
- "compute the shortest distance needed", come up with some paths.

Use this path and feed this to the same function.
- For every input, compute the shortest distance needed to travel...

From the end, extract numeric code.

Assumptions: greedy. Just pick the shortest path from one to another. As long as
the robot takes the shortest path, the other robots will also generate the
shortest path.
 */

const std::unordered_map<pr, char>
    directions({{{0, 1}, '>'}, {{0, -1}, '<'}, {{1, 0}, '^'}, {{-1, 0}, 'v'}});

// TODO: figure out why I can't use "const" for matrices here
matrix<char> numerical_keypad(
    {{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'X', '0', 'A'}});

matrix<char> directional_keypad({{'X', '^', 'A'}, {'<', 'v', '>'}});

std::unordered_map<char, std::unordered_map<char, vector<std::string>>>
    shortest_paths_in_keypad_cache;

vector<std::string> shortest_paths_in_keypad(const char start_position,
                                             const char end_position,
                                             matrix<char> &keypad) {
  std::vector<std::string> res;
  if (start_position == end_position) {
    return res;
  }
  std::string result_hash = {start_position, end_position};

  if (shortest_paths_in_keypad_cache.count(start_position) > 0 &&
      shortest_paths_in_keypad_cache[start_position].count(end_position) > 0) {
    return shortest_paths_in_keypad_cache[start_position][end_position];
  }
  pr initial_position = keypad.find_position(start_position);
  std::queue<std::pair<pr, std::string>> q;
  std::unordered_map<pr, long> dist;
  q.emplace(initial_position, "");
  dist[initial_position] = 0;

  long shortest_distance = -1;
  while (!q.empty()) {
    auto [current, path] = q.front();
    q.pop();
    char current_char = keypad[current];
    long current_dist = dist[current];
    if (current_char == 'X') {
      continue;
    }
    if (shortest_distance != -1 && current_dist > shortest_distance) {
      break;
    }
    if (current_char == end_position) {
      shortest_distance = current_dist;
      res.push_back(path);
      continue;
    }

    for (const auto &[d, direction_key] : directions) {
      pr next = {current.first + d.first, current.second + d.second};
      if (!keypad.in_bounds(next))
        continue;
      char next_char = keypad[next];
      if (next_char == 'X')
        continue;

      if (!dist.count(next) || dist[next] == current_dist + 1) {
        dist[next] = current_dist + 1;
        q.push({next, path + direction_key});
      }
    }
  }
  shortest_paths_in_keypad_cache[start_position][end_position] = res;
  return res;
}

void generate_shortest_paths_in_keypads() {
  vector<char> all_codes(
      {'0', 'A', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
  // then find the path from the first letter to the next.
  for (char start : all_codes) {
    for (char end : all_codes) {
      shortest_paths_in_keypad(start, end, numerical_keypad);
    }
  }

  vector<char> all_directions({'A', '<', '>', '^', 'v'});
  for (char start : all_directions) {
    for (char end : all_directions) {
      shortest_paths_in_keypad(start, end, directional_keypad);
    }
  }
}

string interlace(const std::string &a) {
  string res;
  for (char c : a) {
    res.append(1, c);
    res.append(1, 'A');
  }
  return res;
}

long long cost(const string &seq, int depth) {
  if (depth == 0)
    return seq.length();
  // Select which keypad applies at this depth
  matrix<char> &keypad = (depth == 1) ? numerical_keypad : directional_keypad;
  string sequence;
  for (size_t i = 0; i < seq.size() - 1; i++) {
    auto paths = shortest_paths_in_keypad(seq[i], seq[i + 1], keypad);
    long long min_cost = LLONG_MAX;
    string min_seq;
    for (const auto &path : paths) {
      string interlaced = interlace(path);
      // next layer uses *directional keypad* no matter what current keypad is
      long long c = cost(interlaced, depth - 1);
      if (c < min_cost) {
        min_cost = c;
        min_seq = std::move(interlaced);
      }
    }

    // Append only the minimal-cost path
    sequence += min_seq;
  }

  return sequence.empty() ? seq.length() : cost(sequence, depth - 1);
}

int main(int argc, const char *argv[]) {
  long ans = 0;
  string code;
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  generate_shortest_paths_in_keypads();
  if (test_case.is_open()) {
    getline(test_case, code);

    ans = cost(code, 5);
    cout << fixed << ans << endl;
  }

  return 0;
}
