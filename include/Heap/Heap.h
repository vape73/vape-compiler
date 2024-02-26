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
  void *allocate(size_t size);
  void free(void *ptr);
  void logUsage() const;
  ~Heap();

private:
  void *heapStart;
  size_t heapSize;
  std::vector<Block> blocks;
};

#endif // HEAP_H
