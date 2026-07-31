#include "avl.h"
#include "container.h"
#include "scenario.cpp"
#include "skip_list.cpp"
#include "skip_list_vec.cpp"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::string;

void exec(Container *c) {
  c->insert(5);
  c->insert(4);
  c->insert(3);
  c->insert(1);
  cout << 6 << ": " << c->contains(6) << "\n";
  cout << 1 << ": " << c->contains(1) << "\n";
  cout << 2 << ": " << c->contains(2) << "\n";
  cout << 3 << ": " << c->contains(3) << "\n";

  cout << "Allocated: " << Allocator::allocatedBytes << "\n";
}

int main() {

  AVLTree *avl = Allocator::allocate<AVLTree>();
  exec(avl);
  Allocator::release(avl);
  cout << "Allocated after delete: " << Allocator::allocatedBytes << "\n\n";

  Allocator::reset();

  SkipList *sl = Allocator::allocate<SkipList>();
  exec(sl);
  Allocator::release(sl);
  cout << "Allocated after delete: " << Allocator::allocatedBytes << "\n\n";

  SkipListVec *slv = Allocator::allocate<SkipListVec>();
  exec(slv);
  Allocator::release(slv);
  cout << "Allocated after delete: " << Allocator::allocatedBytes << "\n\n";

  return 0;
}
