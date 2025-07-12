#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "skip_list.h"
#include "avl.h"
#include "scenario.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int main()
{
    MemoryAllocator<AvlNode> *avlNodesMemoryAllocator = new MemoryAllocator<AvlNode>();
    AVLTree *avl = new AVLTree(avlNodesMemoryAllocator);
    avl->insert(5);
    avl->insert(4);
    avl->insert(3);
    avl->insert(1);
    cout << 6 << ": " << avl->contains(6) << "\n";
    cout << 1 << ": " << avl->contains(1) << "\n";
    cout << 2 << ": " << avl->contains(2) << "\n";
    cout << 3 << ": " << avl->contains(3) << "\n";
    cout << "Allocated: " << avlNodesMemoryAllocator->allocatedBytes << "\n";
    delete avl;
    cout << "Allocated after delete: " << avlNodesMemoryAllocator->allocatedBytes << "\n\n";

    SlNodeFactory *slNodeFactory = new SlNodeFactory();
    SkipList *sl = new SkipList(slNodeFactory);
    sl->insert(5);
    sl->insert(4);
    sl->insert(3);
    sl->insert(1);
    cout << 6 << ": " << sl->contains(6) << "\n";
    cout << 1 << ": " << sl->contains(1) << "\n";
    cout << 2 << ": " << sl->contains(2) << "\n";
    cout << 3 << ": " << sl->contains(3) << "\n";

    cout << "Allocated: " << slNodeFactory->allocatedBytes << "\n";
    delete sl;
    cout << "Allocated: " << slNodeFactory->allocatedBytes << "\n\n";

    return 0;
}
