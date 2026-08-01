#include "container.h"
#include <unordered_set>

struct HashSet : Container {

  std::unordered_set<int> inner;

  inline bool contains(int x) { return inner.count(x) > 0; }
  inline void insert(int x) { inner.insert(x); };
  inline void remove(int x) { inner.erase(x); }
};