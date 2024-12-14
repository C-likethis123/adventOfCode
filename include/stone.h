#ifndef STONE_H
#define STONE_H
#include <vector>
class Stone {
public:
  Stone(long x);
  static std::vector<long> transform(long s);
  long x;
};
#endif // STONE_H