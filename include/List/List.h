#ifndef LIST_H
#define LIST_H

#include "Heap/Heap.h"

class List
{
protected:
    Heap &heap;
    size_t elementSize;

public:
    List(Heap &heap, size_t elementSize) : heap(heap), elementSize(elementSize) {}

    virtual void add(const void *element) = 0;
    virtual void remove() = 0;
    virtual void log() const = 0;
    virtual ~List() = default;
};

#endif // LIST_H
