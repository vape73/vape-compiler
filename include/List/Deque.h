#ifndef DEQUE_H
#define DEQUE_H

#include "List.h"
#include <deque>

class Deque : public List
{
    std::deque<void *> elements;

public:
    Deque(Heap &heap, size_t elementSize);

    void addFront(const void *element);

    void addBack(const void *element);

    void removeFront();

    void removeBack();

    void add(const void *element) override;

    void remove() override;

    void log() const override;
};

#endif // DEQUE_H