#ifndef STONE_H
#define STONE_H
#include <vector>
class Stone {
public:
  Stone(long x);
  static std::vector<Stone> transform(Stone &s);

private:
  long x;
};
#endif // STONE_H