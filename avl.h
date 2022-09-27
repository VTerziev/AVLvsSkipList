#include <iostream>
using std::cout;
using std::max;

struct AVLTree {
    AVLTree() {
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
    struct Node {
        Node *l, *r;
        int height;
        int value;
        int count;

        Node (int value) {
            this->value = value;
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

    Node* root;

    Node* findNode(Node *root, int value) {
        if (root == nullptr) { return nullptr; }
        if (root->value<value) {
            return findNode(root->r, value);
        } else if ( root->value == value) {
            return root;
        } else {
            return findNode(root->l, value);
        }
    }

    Node *rotateLeft(Node *root) {
        if (root->r == nullptr) {
            throw std::runtime_error("That should not happen");
            return root;
        }
        Node *rightChild = root->r;
        root->r = root->r->l;
        rightChild->l = root;
        
        root->calculateHeight();
        rightChild->calculateHeight();

        return rightChild;
    }

    Node *rotateRight(Node *root) {
        if (root->l == nullptr) {
            throw std::runtime_error("That should not happen");
            return root;
        }
        Node *leftChild = root->l;
        root->l = root->l->r;
        leftChild->r = root;

        root->calculateHeight();
        leftChild->calculateHeight();

        return leftChild;
    }

    Node* rebalanceNode(Node *root) {
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

    Node* addNode(Node *root, int value) {
        if (root == nullptr) { return new Node(value); }

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

    Node* goOnlyRight(Node *root) {
        if (root->r == nullptr) { return root; }
        return goOnlyRight(root->r);
    }

    void printTree(Node *root) {
        if (root == nullptr) { return; }
        cout << "(";
        printTree(root->l);
        cout << " " << root->value << "," << root->height << "," << root->count << " ";
        printTree(root->r);
        cout << ")";
    }

    Node* removeValue(Node *root, int value, int count) {
        if (root == nullptr) { return root; }
        
        if (root->value==value) {
            root->count -= count;
            if (root->count>0) { return root; }

            if (root->l == nullptr && root->r == nullptr) {
                delete root;
                return nullptr;
            }

            if (root->l == nullptr) {
                Node *ret = root->r;
                delete root;
                return ret;
            }

            if (root->r == nullptr) {
                Node *ret = root->l;
                delete root;
                return ret;
            }

            Node* rightmost = goOnlyRight(root->l);
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

    void internalDestructor(Node* crr) {
        if (crr->l != nullptr) {
            internalDestructor(crr->l);
        }
        if (crr->r != nullptr) {
            internalDestructor(crr->r);
        }
        delete crr;
    }
};
