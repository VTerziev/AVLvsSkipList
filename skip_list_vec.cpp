#include "allocator.cpp"
#include "container.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;

struct SlNodeVec {
  int value;
  int count;
  std::vector<SlNodeVec *> next;
  int level;

  SlNodeVec *getNextOnLevel(int level) {
    if (this->level > level) {
      return next[level];
    }
    return nullptr;
  }

  SlNodeVec(int value, int level) {
    this->count = 1;
    this->value = value;
    this->next = std::vector<SlNodeVec *>(level);
    this->level = level;
  }
};

struct SkipListVec : Container {

  SkipListVec() {
    this->initial = Allocator::allocate<SlNodeVec>(MIN_VALUE, MAX_LEVEL);
    this->path = std::vector<SlNodeVec *>(MAX_LEVEL);
  }

  bool contains(int x) { return internalContains(x); }

  void insert(int x) { internalInsert(x); }

  void remove(int x) { internalRemove(x); }

  void print() { printList(); }

  ~SkipListVec() {
    for (SlNodeVec *crr = initial; crr != nullptr;) {
      SlNodeVec *next = crr->next[0];
      Allocator::release(crr);
      crr = next;
    }
  }

private:
  int MAX_LEVEL = 1;
  int MIN_VALUE = -(1 << 30);

  SlNodeVec *initial;
  std::vector<SlNodeVec *> path;

  SlNodeVec *constructNewInitial(int newMaxLevel) {
    SlNodeVec *newInitial =
        Allocator::allocate<SlNodeVec>(MIN_VALUE, newMaxLevel);
    for (int i = 0; i < MAX_LEVEL; i++) {
      newInitial->next[i] = initial->next[i];
    }
    return newInitial;
  }

  std::vector<SlNodeVec *> constructNewPath(int newMaxLevel,
                                            SlNodeVec *newInitial) {
    std::vector<SlNodeVec *> newPath = std::vector<SlNodeVec *>(newMaxLevel);
    for (int i = 0; i < MAX_LEVEL; i++) {
      if (path[i] == initial) {
        newPath[i] = newInitial;
      } else {
        newPath[i] = path[i];
      }
    }
    for (int i = MAX_LEVEL; i < newMaxLevel; i++) {
      newPath[i] = newInitial;
    }
    return newPath;
  }

  void increaseMaxLevel(int newMaxLevel) {
    SlNodeVec *newInitial = constructNewInitial(newMaxLevel);
    std::vector<SlNodeVec *> newPath =
        constructNewPath(newMaxLevel, newInitial);

    Allocator::release(initial);

    initial = newInitial;
    path = newPath;
    MAX_LEVEL = newMaxLevel;
  }

  int getRandomLevel() {
    int ret = 1;
    for (; (rand()) & 1; ret++) {
    }
    return ret;
  }

  void findPath(int value) {
    SlNodeVec *current = initial;
    for (int level = MAX_LEVEL - 1; level >= 0; level--) {
      while (current->getNextOnLevel(level) != nullptr &&
             current->getNextOnLevel(level)->value < value) {
        current = current->getNextOnLevel(level);
      }
      path[level] = current;
    }
  }

  void internalInsert(int value) {
    findPath(value);
    SlNodeVec *current = path[0];

    current = current->getNextOnLevel(0);
    if (current != nullptr && current->value == value) {
      current->count++;
    } else {
      int newLevel = getRandomLevel();
      if (newLevel > MAX_LEVEL) {
        increaseMaxLevel(newLevel);
      }
      SlNodeVec *newNode = Allocator::allocate<SlNodeVec>(value, newLevel);
      for (int level = 0; level < newLevel; level++) {
        newNode->next[level] = path[level]->next[level];
        path[level]->next[level] = newNode;
      }
    }
  }

  void internalRemove(int value) {
    findPath(value);
    SlNodeVec *current = path[0];
    current = current->getNextOnLevel(0);

    if (current != nullptr && current->value == value) {
      current->count--;
      if (current->count == 0) {
        for (int level = 0; level < current->level; level++) {
          path[level]->next[level] = current->getNextOnLevel(level);
        }
        Allocator::release(current);
      }
    }
  }

  bool internalContains(int value) {
    findPath(value);
    SlNodeVec *current = path[0];
    current = current->getNextOnLevel(0);
    return current != nullptr && current->value == value;
  }

  void printList() {
    for (SlNodeVec *crr = initial; crr != nullptr; crr = crr->next[0]) {
      cout << crr->value << " : ";
      for (int lvl = 0; lvl < MAX_LEVEL; lvl++) {
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
