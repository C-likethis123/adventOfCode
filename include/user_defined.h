#include <iostream>
#include <string>
#include <vector>
namespace user_defined {

template <typename T>
struct pair : std::pair<T, T> {
  pair(T a, T b) : std::pair<T, T>(a, b) {}
};
template<typename T>
std::ostream &operator<<(std::ostream &stream, const pair<T> &pair) {
  stream << pair.first << "," << pair.second;
  return stream;
}

std::vector<std::string> split(std::string s, std::string delimiter);
std::vector<int> split_int(std::string s, std::string delimiter);
} // namespace user_defined
