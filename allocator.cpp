#ifndef ALLOCATOR_GUARD
#define ALLOCATOR_GUARD

#include <algorithm>

struct Allocator {
  static inline long long allocatedBytes;
  static inline long long maxAllocatedBytes;

  template <typename T, typename... Args> static T *allocate(Args... args) {
    int typeSize = sizeof(T);
    allocatedBytes += typeSize;
    maxAllocatedBytes = std::max(maxAllocatedBytes, allocatedBytes);
    return new T(args...);
  }

  template <typename T> static T **allocateArr(int cnt) {
    int ptrTypeSize = sizeof(T *);
    allocatedBytes += ptrTypeSize * cnt;
    maxAllocatedBytes = std::max(maxAllocatedBytes, allocatedBytes);
    return new T *[cnt];
  }

  template <typename T> static void release(T *node) {
    int typeSize = sizeof(T);
    allocatedBytes -= typeSize;
    maxAllocatedBytes = std::max(maxAllocatedBytes, allocatedBytes);
    delete node;
  }

  template <typename T> static void releaseArr(T **arr, int cnt) {
    int ptrTypeSize = sizeof(T *);
    allocatedBytes -= ptrTypeSize * cnt;
    maxAllocatedBytes = std::max(maxAllocatedBytes, allocatedBytes);
    delete[] arr;
  }

  static void reset() {
    allocatedBytes = 0;
    maxAllocatedBytes = 0;
  }
};

// Allocator::allocatedBytes = 0;
// Allocator::maxAllocatedBytes = 0;

#endif