#ifndef UD_PAIR_H
#define UD_PAIR_H
#include <iostream>
#include <string>
#include <vector>
namespace user_defined {

// Custom hash functor
template <typename T> class pair : public std::pair<T, T> {
public:
  // default constructor so I can use it in an unordered_map
  pair() : std::pair<T, T>(T{}, T{}) {}
  pair(T a, T b) : std::pair<T, T>(a, b) {}

  friend std::ostream &operator<<(std::ostream &stream, const pair<T> &pair) {
    stream << pair.first << "," << pair.second;
    return stream;
  }
  friend pair<T> operator+(const pair<T> &lhs, const pair<T> &pair1) {
    return pair<T>({lhs.first + pair1.first, lhs.second + pair1.second});
  }

  friend pair<T> operator+=(pair<T>& lhs, const pair<T> added_pair) {
    lhs.first += added_pair.first;
    lhs.second += added_pair.second;
    return lhs;
  }

  friend pair<T> operator-(const pair<T> &lhs, const pair<T> &pair1) {
    return pair<T>({lhs.first - pair1.first, lhs.second - pair1.second});
  }

  friend pair<T> operator-=(pair<T>& lhs, const pair<T> subtracted_pair) {
    lhs.first -= subtracted_pair.first;
    lhs.second -= subtracted_pair.second;
    return lhs;
  }

  friend constexpr bool operator==(const pair<T>& lhs, const pair<T>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

  friend constexpr bool operator!=(const pair<T>& lhs, const pair<T>& rhs) {
    return !(lhs == rhs);
  }
};

template <typename T> struct pair_hash {
  int matrix_size; // Stores the matrix size

  pair_hash(int size) : matrix_size(size) {}

  std::size_t operator()(const pair<T> &p) const {
    return p.first * matrix_size + p.second;
  }
};

std::vector<std::string> split(std::string s, std::string delimiter);
std::vector<int> split_int(std::string s, std::string delimiter);
} // namespace user_defined

#endif // UD_PAIR_H
