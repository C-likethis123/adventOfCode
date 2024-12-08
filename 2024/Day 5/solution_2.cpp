#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
how to change them to the correct order?
- the moment i see an out of order pair, there is one or more item that it could
possibly be out of order with.
- I can iterate to find the earliest item, then put it in front of that -
reordering it would take O(n). If I reorder everything, it will be O(n^2).
- maybe I can put things in an std::list (implemented as a doubly linked-list).
if it's in order, I append it to the back. if it's out of order, I iterate to
the front, then put it there. constructing this new list will take O(n)
- but searching for the correct index may still take O(n)....

So:
- search for correct index takes O(n)
- updating std::list takes O(1)
- complexity for rebalancing: O(n)
- so creating a correct list will still take O(n^2)

TODO: look at solutions once I have a naive one.

1. accounts for more than one out of order item
2. middle item is computed correctly
3. a problem could be the out of order list but idk what's wrong....


part 1: get mid if the list is sorted
other ppl's answers:
1. it sorts every list, then deduct it by part 1's answers
*/

std::vector<int> split(string s, string delimiter) {
  size_t pos = 0;
  std::string token;
  std::vector<int> v;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(stoi(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(stoi(s));
  return v;
}

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");
  if (test_case.is_open()) {
    // get section ordering rules
    unordered_map<int, unordered_set<int>> orderings;
    while (getline(test_case, line) && !line.empty()) {
      vector<int> ordering = split(line, "|");
      orderings[ordering[1]].insert(ordering[0]);
    }

    while (getline(test_case, line)) {
      vector<int> numbers = split(line, ",");
      unordered_set<int> forbidden;
      bool is_safe = true;
      std::list<int> in_order_list;
      for (size_t i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        if (forbidden.count(num)) {
          is_safe = false;
          break;
        }
        // using .merge method does not work because it will splice
        // orderings[num]
        auto &set_to_merge = orderings[num];
        for (auto &item : set_to_merge) {
          forbidden.insert(item);
        }
      }

      if (!is_safe) {
        // sort it to get the ordered list - sorting works but my custom bubble sort doesn't. weird
        std::sort(numbers.begin(), numbers.end(), [&orderings](const int& v1, const int v2) {
          return (orderings[v2]).count(v1) > 0;
        });
        ans += numbers[numbers.size() / 2];
      }
    }
  }

  cout << fixed << ans << endl;
  return 0;
}
