#ifndef UD_PAIR_H
#define UD_PAIR_H
#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
namespace user_defined {

// Custom hash functor
template <typename T> class pair : public std::pair<T, T> {
public:
  // default constructor so I can use it in an unordered_map
  pair() : std::pair<T, T>(T{}, T{}) {}
  pair(T a, T b) : std::pair<T, T>(a, b) {}

  friend std::ostream &operator<<(std::ostream &stream, const pair<T> &pair) {
    return stream << pair.first << "," << pair.second;
  }
  friend pair<T> operator+(const pair<T> &lhs, const pair<T> &pair1) noexcept {
    return pair<T>({lhs.first + pair1.first, lhs.second + pair1.second});
  }

  friend pair<T> &operator+=(pair<T> &lhs, const pair<T> added_pair) noexcept {
    lhs.first += added_pair.first;
    lhs.second += added_pair.second;
    return lhs;
  }

  friend pair<T> operator-(const pair<T> &lhs, const pair<T> &pair1) noexcept {
    return pair<T>({lhs.first - pair1.first, lhs.second - pair1.second});
  }

  friend pair<T> &operator-=(pair<T> &lhs,
                             const pair<T> subtracted_pair) noexcept {
    lhs.first -= subtracted_pair.first;
    lhs.second -= subtracted_pair.second;
    return lhs;
  }

  friend constexpr bool operator==(const pair<T> &lhs, const pair<T> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

  friend constexpr bool operator!=(const pair<T> &lhs, const pair<T> &rhs) {
    return !(lhs == rhs);
  }
};

std::vector<std::string> split(std::string_view s,
                               const std::string_view &delimiter) noexcept {
  std::vector<std::string> v;
  size_t start = 0;
  while (true) {
    size_t end = s.find(delimiter, start);
    std::string_view token = s.substr(start, end);
    if (!token.empty()) {
      v.emplace_back(token);
    }
    if (end == std::string_view::npos) {
      break;
    }
    start = end + delimiter.length();
  }
  return v;
};

template <typename T>
std::vector<T> split_int(std::string_view s,
                         const std::string_view &delimiter) noexcept {
  std::vector<T> v;
  size_t start = 0;
  while (true) {
    size_t end = s.find(delimiter, start);
    std::string_view token = s.substr(start, end);
    if (!token.empty()) {
      T value;
      auto [ptr, ec] =
          std::from_chars(token.data(), token.data() + token.size(), value);
      if (ec == std::errc()) {
        v.push_back(value);
      }
    }
    if (end == std::string_view::npos) {
      break;
    }
    start = end + delimiter.length();
  }
  return v;
};
} // namespace user_defined

namespace std {
template <typename T> struct hash<user_defined::pair<T>> {
  size_t operator()(const user_defined::pair<T> &p) const noexcept {
    size_t h1 = hash<T>{}(p.first);
    size_t h2 = hash<T>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};
} // namespace std

#endif // UD_PAIR_H
