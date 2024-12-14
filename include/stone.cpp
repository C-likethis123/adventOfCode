#include "stone.h"
#include <iostream>
#include <string>

Stone::Stone(long x) : x(x){};
std::vector<long> Stone::transform(long s) {
  std::vector<long> res;
  if (s == 0) {
    res.emplace_back(1);
  } else if (std::to_string(s).size() % 2 == 0) {
    std::string str = std::to_string(s);
    size_t size = str.size();
    res.emplace_back(std::stol(str.substr(0, size / 2)));
    res.emplace_back(std::stol(str.substr(size / 2)));
  } else {
    res.emplace_back(s * 2024);
  }
  return res;
}
