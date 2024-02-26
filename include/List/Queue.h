#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"
#include <deque>

class Queue : public List
{
    std::deque<void *> elements;

public:
    Queue(Heap &heap, size_t elementSize);

    void add(const void *element) override;

    void remove() override;

    void log() const override;
};

#endif // QUEUE_H