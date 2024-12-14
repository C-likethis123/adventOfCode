#include "stone.h"
#include <string>
#include <iostream>

Stone::Stone(long x) : x(x){};
std::vector<Stone> Stone::transform(Stone &s) {
  std::vector<Stone> res;
  if (s.x == 0) {
    res.emplace_back(1);
  } else if (std::to_string(s.x).size() % 2 == 0) {
    std::string str = std::to_string(s.x);
    size_t size = str.size();
    res.emplace_back(std::stol(str.substr(0, size / 2)));
    res.emplace_back(std::stol(str.substr(size / 2)));
  } else {
    res.emplace_back(s.x * 2024);
  }
  return res;
}
