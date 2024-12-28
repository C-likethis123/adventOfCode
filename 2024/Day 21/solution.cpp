#include "user_defined.h"
#include "ud_matrix.h"
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
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T>
using matrix = user_defined::matrix<T>;

/**

- try finding the shortest sequence for one robot
  observation: if those two points make up a "rectangle", traverse through the rectangle, it will always be the shortest. so i don't need the actual sequence.

- need to store the state of all the robots.
- then increment.

How many robots needed:
- numerical keypad
- directional keyboard
- directional keyboard
- i control the last directional keypad

all robots initially aim at the keypad's A key.

in order to press 0 first:
1) <A
2)
3)
4)
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
  }

  cout << fixed << ans << endl;
  return 0;
}

