#include "ud_matrix.h"
#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
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

/**
modification: everything is twice as wide
easy modification: put different symbols in the matrix.
 */

pr find_starting_position(matrix<char> &m) {
  for (int i = 0; i < m.size(); i++) {
    for (int j = 0; j < m[0].size(); j++) {
      if (m[i][j] == '@') {
        return pr({i, j});
      }
    }
  }
  return pr({0, 0});
}

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
    matrix<char> m;

    while (getline(test_case, line) && !line.empty()) {

      vector<char> row;
      for (char &c : line) {
        switch (c) {
        case '#': {
          row.emplace_back('#');
          row.emplace_back('#');
          break;
        }
        case 'O': {
          row.emplace_back('[');
          row.emplace_back(']');
          break;
        }
        case '.': {
          row.emplace_back('.');
          row.emplace_back('.');
          break;
        }
        default: {
          row.emplace_back('@');
          row.emplace_back('.');
        }
        }
      }
      m.emplace_back(row);
    }
    unordered_map<char, pr> directions({{'>', pr({0, 1})},
                                        {'^', pr({-1, 0})},
                                        {'v', pr({1, 0})},
                                        {'<', pr({0, -1})}});
    unordered_map<char, pr> box_side({{']', pr({0, -1})}, {'[', pr({0, 1})}});
    pr start = find_starting_position(m);
    while (getline(test_case, line)) {

      for (char move : line) {
        pr &direction = directions[move];
        if (move == '>' || move == '<') {
          pr current = start;
          current += direction;
          while (m[current] != '.' && m[current] != '#') {
            current += direction;
          }

          // get a stopping point, shift everything if I can
          if (m[current] == '.') {
            pr prev = current - direction;
            while (current != start) {
              m[current] = m[prev];
              current = prev;
              prev = prev - direction;
            }
            m[start] = '.';

            // once everything is shifted, change 'start'
            start += direction;
          }
          // different vertically
        } else {
          pr current = start + direction;
          vector<pr> queue({current});
          unordered_set<pr, pair_hash> encountered(8, pair_hash(m.size()));
          bool can_shift = true;
          while (!queue.empty()) {
            auto pos = queue.front();
            if (m[pos] == '.') {
              encountered.insert(pos);
            } else if (m[pos] == '#') {
              can_shift = false;
              break;
            } else {
              pr side = pos + box_side[m[pos]];
              if (encountered.count(pos) == 0) {
                encountered.insert(pos);
                pr next = pos + direction;
                queue.emplace_back(side);
                queue.emplace_back(next);
              }
            }
            queue.erase(queue.begin());
          }

          if (can_shift) {
            // by then, everything is in encountered? assumption is that
            // everything in encountered is either a box or empty space. if
            // empty space, move it forward.

            std::function<bool(int, int)> comparator;
            if (move == '^') {
              comparator = std::greater<int>();
            } else {
              comparator = std::less<int>();
            }
            map<int, unordered_set<int>, std::function<bool(int, int)>>
                orderings(comparator);
            for (auto &point : encountered) {
              if (m[point] != '.') {
                orderings[point.first].insert(point.second);
              }
            }
            for (auto &[x, y_set] : orderings) {
              // do something here
              for (auto &y : y_set) {
                pr new_p = pr({x, y}) + direction;
                m[new_p] = m[x][y];
                m[x][y] = '.';
              }
            }
            // set start
            pr new_start = start + direction;
            m[new_start] = m[start];
            m[start] = '.';
            start = new_start;
          }
        }
      }
    }

    // once everything is calculated, iterate through the matrix and compute GPS
    for (int i = 0; i < m.size(); i++) {
      for (int j = 0; j < m[0].size(); j++) {
        if (m[i][j] == '[') {
          ans += 100 * i + j;
        }
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
