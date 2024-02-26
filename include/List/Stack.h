#ifndef STACK_H
#define STACK_H

#include "List.h"
#include <vector>

class Stack : public List
{
    std::vector<void *> elements;

public:
    Stack(Heap &heap, size_t elementSize);

    void add(const void *element) override;

    void remove() override;

    void log() const override;
};

#endif // STACK_H