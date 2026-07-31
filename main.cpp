#include "avl.h"
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

int main() {
  AVLTree *avl = Allocator::allocate<AVLTree>();
  avl->insert(5);
  avl->insert(4);
  avl->insert(3);
  avl->insert(1);
  cout << 6 << ": " << avl->contains(6) << "\n";
  cout << 1 << ": " << avl->contains(1) << "\n";
  cout << 2 << ": " << avl->contains(2) << "\n";
  cout << 3 << ": " << avl->contains(3) << "\n";
  cout << "Allocated: " << Allocator::allocatedBytes << "\n";
  Allocator::release(avl);
  cout << "Allocated after delete: " << Allocator::allocatedBytes << "\n\n";

  Allocator::reset();

  SkipList *sl = Allocator::allocate<SkipList>();
  sl->insert(5);
  sl->insert(4);
  sl->insert(3);
  sl->insert(1);
  cout << 6 << ": " << sl->contains(6) << "\n";
  cout << 1 << ": " << sl->contains(1) << "\n";
  cout << 2 << ": " << sl->contains(2) << "\n";
  cout << 3 << ": " << sl->contains(3) << "\n";

  cout << "Allocated: " << Allocator::allocatedBytes << "\n";
  Allocator::release(sl);
  cout << "Allocated: " << Allocator::allocatedBytes << "\n\n";

  SkipListVec *slv = Allocator::allocate<SkipListVec>();
  slv->insert(5);
  slv->insert(4);
  slv->insert(3);
  slv->insert(1);
  cout << 6 << ": " << slv->contains(6) << "\n";
  cout << 1 << ": " << slv->contains(1) << "\n";
  cout << 2 << ": " << slv->contains(2) << "\n";
  cout << 3 << ": " << slv->contains(3) << "\n";

  cout << "Allocated: " << Allocator::allocatedBytes << "\n";
  Allocator::release(slv);
  cout << "Allocated: " << Allocator::allocatedBytes << "\n\n";

  return 0;
}
