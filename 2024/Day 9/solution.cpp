#include "user_defined.h"
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
even number index: files space
odd number index: free size

Eg: 12345 -

022111222
        xe
After adjusting, it will look like:
022111222......

brute force:
- represent it as a vector<char>, and pad empty spaces.
- two pointers: start from right most item, move file blocks to the left most
free space. continue until done.
- at the end, compute a checksum.
- adjustment stops when the two indices meet

better: work with a more compact representation.


TIL:
- find can be used to return an iterator. subtract it by begin() to get the
iterator.

*/
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
    vector<int> file_blocks;
    size_t file_id = 0;
    for (size_t i = 0; i < line.size(); i++) {
      int num = line[i] - '0';
      if (i % 2 == 0) {
        for (size_t j = 0; j < num; j++) {
          file_blocks.emplace_back(file_id);
        }
        file_id++;
      } else {
        for (size_t j = 0; j < num; j++) {
          file_blocks.emplace_back(-1);
        }
      }
    }
    for (int i : file_blocks) {
      debug << i << ",";
    }

    auto first_index = std::find(file_blocks.begin(), file_blocks.end(), -1) -
                       file_blocks.begin();
    auto second_index = file_blocks.size() - 1;
    while (second_index > first_index) {
      if (file_blocks[second_index] == -1) {
        second_index--;
      } else if (file_blocks[first_index] == -1) {
        file_blocks[first_index] = file_blocks[second_index];
        first_index++;
        second_index--;
      } else {
        first_index++;
      }
    }
    for (size_t i = 0; i < second_index; i++) {
      debug << file_blocks[i] << ",";
    }
    for (size_t i = 0; i < second_index + 1; i++) {
      if (file_blocks[i] != -1) {
        ans += i * file_blocks[i];
        debug << fixed << ans << endl;
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
