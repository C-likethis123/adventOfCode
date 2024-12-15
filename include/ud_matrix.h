#ifndef UD_MATRIX_H
#define UD_MATRIX_H
#include "user_defined.h"
#include <vector>
namespace user_defined {

using pr = pair<int>;
template <typename K> class matrix : public std::vector<std::vector<K>> {
public:
  matrix() : std::vector<std::vector<K>>() {} // initialises an empty matrix

  friend std::ostream &operator<<(std::ostream &stream,
                                  const matrix<K> &matrix) {
    stream << "matrix[";
    for (const auto &row : matrix) {
      stream << "[";
      for (const auto &item : row) {
        stream << item << ", ";
      }
      stream << "]," << std::endl;
    }
    stream << "]" << std::endl;
    return stream;
  }
  const K &operator[](const pr &pr) const {
    return (*this)[pr.first][pr.second];
  }

  // Overload operator[] for accessing with an integer index (for rows)
  std::vector<K> &operator[](size_t index) {
    return std::vector<std::vector<K>>::operator[](index);
  }

  const std::vector<K> &operator[](size_t index) const {
    return std::vector<std::vector<K>>::operator[](index);
  }

  bool in_bounds(const pr &p) {
    return p.first >= 0 && p.first < (*this).size() && p.second >= 0 &&
           p.second < (*this)[0].size();
  }
};
} // namespace user_defined

#endif // UD_MATRIX_H
