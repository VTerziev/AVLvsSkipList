#include <cstdlib>
#include <iostream>

using std::cout;

struct SkipList {

    SkipList() {
        this->initial = new Node(MIN_VALUE, MAX_LEVEL);
        this->path = new Node*[MAX_LEVEL];
    }

    bool contains(int x) {
        return internalContains(x);
    }

    void insert(int x) {
        internalInsert(x);
    }

    void remove(int x) {
        internalRemove(x);
    }
    
    void print() {
        printList();
    } 
    
    ~SkipList() { 
        for (Node* crr = initial; crr != nullptr ; ) {
            Node* next = crr->next[0];
            delete crr;
            crr = next;
        }
        delete[] path;
    }
private:
    int MAX_LEVEL = 1;
    int MIN_VALUE = -1<<30;

    struct Node {
        int value;
        int count;
        Node** next;
        int level;

        Node* getNextOnLevel(int level) {
            if (this->level>level) { return next[level]; }
            return nullptr;
        }

        Node(int value, int level) {
            this->count = 1;
            this->value = value;
            this->next = new Node*[level];
            std::fill(next, next + level, nullptr);
            this->level = level;
        }

        ~Node() {
            delete[] next;
        }
    };

    Node* initial;
    Node** path;

    Node* constructNewInitial(int newMaxLevel) {
        Node* newInitial = new Node(MIN_VALUE, newMaxLevel);
        for (int i = 0 ; i < MAX_LEVEL; i ++ ) {
            newInitial->next[i] = initial->next[i];
        }
        return newInitial;
    }

    Node** constructNewPath(int newMaxLevel, Node* newInitial) {
        Node** newPath = new Node*[newMaxLevel];
        for (int i = 0 ; i < MAX_LEVEL ; i ++ ) { 
            if (path[i] == initial) {
                newPath[i] = newInitial;
            } else {
                newPath[i] = path[i];
            }
        }
        for (int i = MAX_LEVEL ; i < newMaxLevel ; i ++ ) { 
            newPath[i] = newInitial;
        }
        return newPath;
    }

    void increaseMaxLevel(int newMaxLevel) {
        Node* newInitial = constructNewInitial(newMaxLevel);
        Node** newPath = constructNewPath(newMaxLevel, newInitial);

        delete initial;
        delete[] path;

        initial = newInitial;
        path = newPath;
        MAX_LEVEL = newMaxLevel;
    }

    int getRandomLevel() {
        int ret = 1;
        for ( ; (rand())&1 ; ret ++ ) {}
        return ret;
    }

    void findPath(int value) {
        Node* current = initial;
        for (int level = MAX_LEVEL-1 ; level >= 0 ; level -- ) {
            while (current->getNextOnLevel(level) != nullptr && current->getNextOnLevel(level)->value<value) {
                current = current->getNextOnLevel(level);
            }
            path[level] = current;
        }
    }

    void internalInsert(int value) {
        findPath(value);
        Node* current = path[0];

        current = current->getNextOnLevel(0);
        if (current != nullptr && current->value == value) {
            current->count ++;
        } else {
            int newLevel = getRandomLevel();
            if (newLevel > MAX_LEVEL) {
                increaseMaxLevel(newLevel);
            }
            Node* newNode = new Node(value, newLevel);
            for (int level = 0 ; level < newLevel ; level ++ ) {
                newNode->next[level] = path[level]->next[level];
                path[level]->next[level] = newNode;
            }
        }
    }

    void internalRemove(int value) {
        findPath(value);
        Node* current = path[0];
        current = current->getNextOnLevel(0);

        if (current != nullptr && current->value == value) {
            current->count --;
            if (current->count == 0) {
                for (int level = 0 ; level < current->level ; level ++ ) {
                    path[level]->next[level] = current->getNextOnLevel(level);
                }
                delete current;
            }
        }
    }

    bool internalContains(int value) {
        findPath(value);
        Node* current = path[0];
        current = current->getNextOnLevel(0);
        return current != nullptr && current->value == value;
    }

    void printList() {
        for (Node *crr = initial ; crr != nullptr ; crr = crr->next[0]) {
            cout << crr->value << " : ";
            for ( int lvl = 0 ; lvl < MAX_LEVEL ; lvl ++ ) {
                if (lvl < crr->level) {
                    cout << "[";
                    if (crr->next[lvl] != nullptr) {
                        cout << crr->next[lvl]->value;
                    } else {
                        cout << "null";
                    }
                    cout << "]";
                } else {
                    cout << " | ";
                }
            }
            cout << "\n";
        }
    }
};
