#ifndef UD_MATRIX_H
#define UD_MATRIX_H
#include "user_defined.h"
#include <experimental/iterator>
#include <initializer_list>
#include <iterator>
#include <vector>
namespace user_defined {

using pr = pair<int>;
template <typename K> class matrix : public std::vector<std::vector<K>> {
public:
  matrix() : std::vector<std::vector<K>>() {} // initialises an empty matrix
  matrix(std::initializer_list<std::initializer_list<K>> il)
      : std::vector<std::vector<K>>() {
    this->reserve(il.size());
    for (const auto &row : il) {
      this->emplace_back(row);
    }
  } // build with initialiser list

  friend std::ostream &operator<<(std::ostream &stream,
                                  const matrix<K> &matrix) {
    stream << "matrix[" << std::endl;
    for (const auto &row : matrix) {
      stream << "[";
      std::copy(std::begin(row), std::end(row),
                std::experimental::make_ostream_joiner(stream, ", "));
      stream << "]," << std::endl;
    }
    stream << "]" << std::endl;
    return stream;
  }
  K &operator[](const pr &pr) { return (*this)[pr.first][pr.second]; }

  // Overload operator[] for accessing with an integer index (for rows)
  std::vector<K> &operator[](size_t index) {
    return std::vector<std::vector<K>>::operator[](index);
  }

  const std::vector<K> &operator[](size_t index) const {
    return std::vector<std::vector<K>>::operator[](index);
  }

  inline bool in_bounds(const pr &p) const {
    return p.first >= 0 && p.first < (*this).size() && p.second >= 0 &&
           p.second < (*this)[0].size();
  }

  pr find_position(const K &item) const {
    int row_size = this->size();
    int col_size = (*this)[0].size();
    for (int i = 0; i < row_size; i++) {
      for (int j = 0; j < col_size; j++) {
        if ((*this)[i][j] == item) {
          return pr({i, j});
        }
      }
    }
    return pr({-1, -1});
  }
};

} // namespace user_defined

#endif // UD_MATRIX_H
