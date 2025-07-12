#ifndef MEOMRY_ALLOCATOR_GUARD
#define MEOMRY_ALLOCATOR_GUARD

#include <iostream>
using std::max;

template <typename T>
struct MemoryAllocator
{
    long long allocatedBytes = 0;
    long long maxAllocatedBytes = 0;
    int typeSize = sizeof(T);

    T *allocate()
    {
        T *ret = new T();
        allocatedBytes += typeSize;
        maxAllocatedBytes = max(maxAllocatedBytes, allocatedBytes);
        return ret;
    }

    void release(T *t)
    {
        allocatedBytes -= typeSize;
        maxAllocatedBytes = max(maxAllocatedBytes, allocatedBytes);
        delete t;
    }
};
#endif
