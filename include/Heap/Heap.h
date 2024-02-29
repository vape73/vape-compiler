#ifndef HEAP_H
#define HEAP_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Block.h"

class Heap
{
public:
    explicit Heap(size_t size);

    void **allocate(size_t size);

    template <typename T>
    T **allocate();

    void free(void *ptr);

    void logUsage() const;

    ~Heap();

private:
    void *heapStart;
    size_t heapSize;
    void *heapTop;
    std::vector<Block> blocks;

    size_t getUnmarkedSpace() const;

    std::vector<Block>::iterator findBlock(void *ptr);

    size_t get_free_space() const;

    std::vector<Block>::iterator findMinSuitableBlock(size_t size);

    void splitBlock(std::vector<Block>::iterator
                        blockIt,
                    size_t size);

    void mergeBlocks(std::vector<Block>::iterator blockIt);

    void compact();
};

#endif // HEAP_H
