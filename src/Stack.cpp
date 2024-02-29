#include "List/Stack.h"

Stack::Stack(Heap &heap, size_t elementSize) : List(heap, elementSize) {}

void Stack::add(const void *element)
{
    void *block = heap.allocate(elementSize);
    memcpy(block, element, elementSize);
    elements.push_back(block);
}

void Stack::remove()
{
    if (!elements.empty())
    {
        void *element = elements.back();
        elements.pop_back();
        heap.free(element);
    }
}

void Stack::log() const
{
    std::cout << "Stack contains " << elements.size() << " elements." << std::endl;
}
