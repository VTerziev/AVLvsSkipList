#include <iostream>
#include "memory_allocator.h"
using std::cout;
using std::max;

struct AvlNode {
    AvlNode *l, *r;
    int height;
    int value;
    int count;

    AvlNode (int value) {
        this->value = value;
        this->l = nullptr;
        this->r = nullptr;
        this->height = 1;
        this->count = 1;
    }

    AvlNode () {
        this->value = -1;
        this->l = nullptr;
        this->r = nullptr;
        this->height = 1;
        this->count = 1;
    }

    int getLeftHeight() {
        if (this->l == nullptr) { return 0; }
        return this->l->height;
    }
    int getRightHeight() {
        if (this->r == nullptr) { return 0; }
        return this->r->height;
    }

    void calculateHeight() {
        this->height = 1+max(getLeftHeight(), getRightHeight());
    }
};

struct AVLTree {
    MemoryAllocator<AvlNode>* memAllocator;

    AVLTree(MemoryAllocator<AvlNode>* memAllocator) {
        this->memAllocator = memAllocator;
        this->root = nullptr;
    }
    bool contains(int x) {
        return findNode(root, x) != nullptr;
    }

    void insert(int x) {
        root = addNode(root, x);
    }

    void remove(int x) {
        root = removeValue(root, x, 1);
    }

    void print() {
        printTree(root);
    }

    ~AVLTree() {
        if (root!=nullptr) {
            internalDestructor(root);
        }
    }

private:
    AvlNode* root;

    AvlNode* findNode(AvlNode *root, int value) {
        if (root == nullptr) { return nullptr; }
        if (root->value<value) {
            return findNode(root->r, value);
        } else if ( root->value == value) {
            return root;
        } else {
            return findNode(root->l, value);
        }
    }

    AvlNode *rotateLeft(AvlNode *root) {
        if (root->r == nullptr) {
            throw std::runtime_error("That should not happen");
            return root;
        }
        AvlNode *rightChild = root->r;
        root->r = root->r->l;
        rightChild->l = root;

        root->calculateHeight();
        rightChild->calculateHeight();

        return rightChild;
    }

    AvlNode *rotateRight(AvlNode *root) {
        if (root->l == nullptr) {
            throw std::runtime_error("That should not happen");
            return root;
        }
        AvlNode *leftChild = root->l;
        root->l = root->l->r;
        leftChild->r = root;

        root->calculateHeight();
        leftChild->calculateHeight();

        return leftChild;
    }

    AvlNode* rebalanceNode(AvlNode *root) {
        if (root == nullptr) { return root; }

        int leftHeight = root->getLeftHeight();
        int rightHeight = root->getRightHeight();

        if (leftHeight>rightHeight+1) {
            if (root->l->getLeftHeight() >= root->l->getRightHeight()) {
                root = rotateRight(root);
            } else {
                root->l = rotateLeft(root->l);
                root = rotateRight(root);
            }
        } else if (leftHeight+1<rightHeight){
            if (root->r->getRightHeight() >= root->r->getLeftHeight()) {
                root = rotateLeft(root);
            } else {
                root->r = rotateRight(root->r);
                root = rotateLeft(root);
            }
        }
        return root;
    }

    AvlNode* addNode(AvlNode *root, int value) {
        if (root == nullptr) {
            // TODO: how to remove code duplication with non-default constructor?
            AvlNode* crr = this->memAllocator->allocate();
            crr->value = value;
            return crr;
//            return new AvlNode(value);
        }

        if (root->value < value) {
            root->r = addNode(root->r, value);
        } else if (root->value == value) {
            root->count ++;
        } else {
            root->l = addNode(root->l, value);
        }
        root->calculateHeight();
        return rebalanceNode(root);
    }

    AvlNode* goOnlyRight(AvlNode *root) {
        if (root->r == nullptr) { return root; }
        return goOnlyRight(root->r);
    }

    void printTree(AvlNode *root) {
        if (root == nullptr) { return; }
        cout << "(";
        printTree(root->l);
        cout << " " << root->value << "," << root->height << "," << root->count << " ";
        printTree(root->r);
        cout << ")";
    }

    AvlNode* removeValue(AvlNode *root, int value, int count) {
        if (root == nullptr) { return root; }

        if (root->value==value) {
            root->count -= count;
            if (root->count>0) { return root; }

            if (root->l == nullptr && root->r == nullptr) {
                this->memAllocator->release(root);
//                delete root;
                return nullptr;
            }

            if (root->l == nullptr) {
                AvlNode *ret = root->r;
                this->memAllocator->release(root);
//                delete root;
                return ret;
            }

            if (root->r == nullptr) {
                AvlNode *ret = root->l;
                this->memAllocator->release(root);
//                delete root;
                return ret;
            }

            AvlNode* rightmost = goOnlyRight(root->l);
            root->value = rightmost->value;
            root->count = rightmost->count;
            root->l = removeValue(root->l, root->value, root->count);

        } else if (root->value < value) {
            root->r = removeValue(root->r, value, count);
        } else {
            root->l = removeValue(root->l, value, count);
        }
        root->calculateHeight();
        return rebalanceNode(root);
    }

    void internalDestructor(AvlNode* crr) {
        if (crr->l != nullptr) {
            internalDestructor(crr->l);
        }
        if (crr->r != nullptr) {
            internalDestructor(crr->r);
        }
        this->memAllocator->release(crr);
//      delete crr;
    }
};
