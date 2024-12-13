#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdlib>
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
- start from the last file block:
  - iterate through list of free spaces based on the indices and attempt to find
a space that this file block could move to.
  - if I can move, the index of the file changes to the start of the file block,
and I compute the checksum.
  - after the movement, if there is remaining free space, update the block
index. If there is no free space, yeet it from the set/list?

  - if I cannot move the block, compute the checksum directly


points for optimisation:
- for now, I'll find free spaces via a brute force algo
- but an optimised algorithm will recognise that when I'm searching for a
suitable free space, I want to find the leftmost space where the file can fit
in.
- so the free spaces should be sorted, and a binary search algo can be used.

*/

long sum_of_pos(long start, int n) { return n * (2 * start + n - 1) / 2; }

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
    getline(test_case, line);
    vector<user_defined::pair<long>> file_blocks;
    vector<user_defined::pair<long>> free_spaces;
    int index = 0;
    for (size_t i = 0; i < line.size(); i++) {
      long size = line[i] - '0';
      if (i % 2 == 0) {
        file_blocks.emplace_back(user_defined::pair<long>({index, size}));
        index += size;
      } else {
        if (size > 0) {
          free_spaces.emplace_back(user_defined::pair<long>({index, size}));
          index += size;
        }
      }
    }

    for (long i = file_blocks.size() - 1; i > 0; i--) {
      auto &[pos, space] = file_blocks[i];
      long file_index = i;
      bool found_space = false;
      for (size_t j = 0; j < free_spaces.size(); j++) {
        auto &[space_index, space_space] = free_spaces[j];
        if (space_space >= space && space_index < pos) {
          long sum = sum_of_pos(space_index, space);
          ans += sum * file_index;
          // update the space
          free_spaces[j].first = space_index + space;
          free_spaces[j].second = space_space - space;
          found_space = true;
          break;
        }
      }
      if (!found_space) {
        long sum = sum_of_pos(pos, space);
        ans += sum * file_index;
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
