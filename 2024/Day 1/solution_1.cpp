#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <scn/scan.h>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

int main() {
  long ans = 0;
  string line;
  ifstream test_case("input.txt");
  // ofstream debug("output.txt");

  if (test_case) {
    // parse into two lists
    array<vector<int>, 2> sequences;
    sequences[0].reserve(1000);
    sequences[1].reserve(1000);
    constexpr string_view fmt = "{} {}";
    while (getline(test_case, line)) {
      if (auto result = scn::scan<int, int>(std::string_view(line), fmt)) {
        auto [a, b] = result->values();
        sequences[0].push_back(a);
        sequences[1].push_back(b);
      }
    }

    // sort lists
    for (auto &seq : sequences) {
      std::sort(seq.begin(), seq.end());
    }

    // get distance
    long ans = std::transform_reduce(
        sequences[0].begin(), sequences[0].end(), sequences[1].begin(), 0L,
        std::plus<>{}, [](int x, int y) { return std::abs(x - y); });
    cout << fixed << ans << endl;
  }
  return 0;
}
