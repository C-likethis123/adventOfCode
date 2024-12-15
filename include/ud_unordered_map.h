#ifndef UD_UNORDERED_MAP_H
#define UD_UNORDERED_MAP_H
#include <unordered_map>
namespace user_defined {

template <typename K, typename H>
class unordered_map : public std::unordered_map<K, H> {
public:
  unordered_map(K k, H h) : std::unordered_map<K, H>(k, h) {}

  friend std::ostream &operator<<(std::ostream &stream,
                                  const unordered_map<K, H> &um) {
    stream << "map:{";
    for (const auto &[k, h] : um) {
      stream << "{" << k << ", " << h << "}" << std::endl;
    }
    stream << "}" << endl;
    return stream;
  }
};
} // namespace user_defined

#endif // UD_UNORDERED_MAP_H
