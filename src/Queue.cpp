#include "List/Queue.h"

Queue::Queue(Heap &heap, size_t elementSize) : List(heap, elementSize) {}

void Queue::add(const void *element)
{
    void *block = heap.allocate(elementSize);
    memcpy(block, element, elementSize);
    elements.push_back(block);
}

void Queue::remove()
{
    if (!elements.empty())
    {
        void *element = elements.front();
        elements.pop_front();
        heap.free(element);
    }
}

void Queue::log() const
{
    std::cout << "Queue contains " << elements.size() << " elements." << std::endl;
}
