#include <iostream>
namespace user_defined {

struct pair : std::pair<int, int> {
  pair(int a, int b) : std::pair<int, int>(a, b) {}
};
std::ostream &operator<<(std::ostream &stream, pair &pair) {
  stream << pair.first << "," << pair.second;
  return stream;
}
} // namespace user_defined
