#include <iostream>
#include <string>
#include <vector>
namespace user_defined {

template <typename T> class pair : public std::pair<T, T> {
public:
  pair(T a, T b) : std::pair<T, T>(a, b){};

  friend std::ostream &operator<<(std::ostream &stream, const pair<T> &pair) {
    stream << pair.first << "," << pair.second;
    return stream;
  }
  friend pair<T> operator+(const pair<T> &lhs, const pair<T> &pair1) {
    return pair<T>({lhs.first + pair1.first, lhs.second + pair1.second});
  }
};

std::vector<std::string> split(std::string s, std::string delimiter);
std::vector<int> split_int(std::string s, std::string delimiter);
} // namespace user_defined
