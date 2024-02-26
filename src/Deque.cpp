#include "List/Deque.h"
#include <iostream>

Deque::Deque(Heap &heap, size_t elementSize) : List(heap, elementSize) {}

void Deque::addFront(const void *element)
{
    void *block = heap.allocate(elementSize);
    memcpy(block, element, elementSize);
    elements.push_front(block);
}

void Deque::addBack(const void *element)
{
    void *block = heap.allocate(elementSize);
    memcpy(block, element, elementSize);
    elements.push_back(block);
}

void Deque::removeFront()
{
    if (!elements.empty())
    {
        void *element = elements.front();
        elements.pop_front();
        heap.free(element);
    }
}

void Deque::removeBack()
{
    if (!elements.empty())
    {
        void *element = elements.back();
        elements.pop_back();
        heap.free(element);
    }
}

void Deque::add(const void *element)
{
    throw "not implemented method";
};

void Deque::remove()
{
    throw "not implemented method";
};

void Deque::log() const
{
    std::cout << "Deque contains " << elements.size() << " elements." << std::endl;
}
