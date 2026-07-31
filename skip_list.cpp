#include "allocator.cpp"
#include "container.h"
#include <cstdlib>
#include <iostream>

using std::cout;

struct SlNode {
  int value;
  int count;
  SlNode **next;
  int level;

  SlNode *getNextOnLevel(int level) {
    if (this->level > level) {
      return next[level];
    }
    return nullptr;
  }

  SlNode(int value, int level) {
    this->count = 1;
    this->value = value;
    this->next = Allocator::allocateArr<SlNode>(level);
    std::fill(next, next + level, nullptr);
    this->level = level;
  }

  ~SlNode() { Allocator::releaseArr(next, level); }
};

struct SkipList : Container {

  SkipList() {
    this->initial = Allocator::allocate<SlNode>(MIN_VALUE, MAX_LEVEL);
    this->path = Allocator::allocateArr<SlNode>(MAX_LEVEL);
  }

  bool contains(int x) { return internalContains(x); }

  void insert(int x) { internalInsert(x); }

  void remove(int x) { internalRemove(x); }

  void print() { printList(); }

  ~SkipList() {
    for (SlNode *crr = initial; crr != nullptr;) {
      SlNode *next = crr->next[0];
      Allocator::release(crr);
      crr = next;
    }
    Allocator::releaseArr(path, MAX_LEVEL);
  }

private:
  int MAX_LEVEL = 1;
  int MIN_VALUE = -1 << 30;

  SlNode *initial;
  SlNode **path;

  SlNode *constructNewInitial(int newMaxLevel) {
    SlNode *newInitial = Allocator::allocate<SlNode>(MIN_VALUE, newMaxLevel);
    for (int i = 0; i < MAX_LEVEL; i++) {
      newInitial->next[i] = initial->next[i];
    }
    return newInitial;
  }

  SlNode **constructNewPath(int newMaxLevel, SlNode *newInitial) {
    SlNode **newPath = Allocator::allocateArr<SlNode>(newMaxLevel);
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
    SlNode *newInitial = constructNewInitial(newMaxLevel);
    SlNode **newPath = constructNewPath(newMaxLevel, newInitial);

    Allocator::release(initial);
    Allocator::releaseArr(path, MAX_LEVEL);

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
    SlNode *current = initial;
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
    SlNode *current = path[0];

    current = current->getNextOnLevel(0);
    if (current != nullptr && current->value == value) {
      current->count++;
    } else {
      int newLevel = getRandomLevel();
      if (newLevel > MAX_LEVEL) {
        increaseMaxLevel(newLevel);
      }
      SlNode *newNode = Allocator::allocate<SlNode>(value, newLevel);
      for (int level = 0; level < newLevel; level++) {
        newNode->next[level] = path[level]->next[level];
        path[level]->next[level] = newNode;
      }
    }
  }

  void internalRemove(int value) {
    findPath(value);
    SlNode *current = path[0];
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
    SlNode *current = path[0];
    current = current->getNextOnLevel(0);
    return current != nullptr && current->value == value;
  }

  void printList() {
    for (SlNode *crr = initial; crr != nullptr; crr = crr->next[0]) {
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
