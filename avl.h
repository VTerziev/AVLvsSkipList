#ifndef AVL_GUARD
#define AVL_GUARD

#include "memory_allocator.cpp"

struct AvlNode
{
public:
    AvlNode(int value);
    AvlNode();

private:
    AvlNode *l, *r;
    int height;
    int value;
    int count;
    int getLeftHeight();
    int getRightHeight();
    void calculateHeight();

    friend class AVLTree;
};

struct AVLTree
{
    AVLTree(MemoryAllocator<AvlNode> *memAllocator);
    bool contains(int x);
    void insert(int x);
    void remove(int x);
    void print();
    ~AVLTree();

private:
    MemoryAllocator<AvlNode> *memAllocator;
    AvlNode *root;

    AvlNode *removeValue(AvlNode *root, int value, int count);
    void internalDestructor(AvlNode *crr);
    AvlNode *goOnlyRight(AvlNode *root);
    void printTree(AvlNode *root);
    AvlNode *addNode(AvlNode *root, int value);
    AvlNode *rebalanceNode(AvlNode *root);
    AvlNode *findNode(AvlNode *root, int value);
    AvlNode *rotateLeft(AvlNode *root);
    AvlNode *rotateRight(AvlNode *root);
};

#endif