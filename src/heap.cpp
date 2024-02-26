#include "Heap/Heap.h"

Heap::Heap(size_t size)
{
  heapStart = std::malloc(size); // Используем malloc для выделения памяти
  if (heapStart == nullptr)
  {
    std::cerr << "Failed to allocate heap." << std::endl;
    exit(1);
  }
  heapSize = size;
}

Heap::~Heap()
{
  std::free(heapStart); // Освобождаем всю выделенную память
}

void *Heap::allocate(size_t size)
{
  void *blockStart = heapStart;
  for (auto &block : blocks)
  {
    if (!block.used && block.size >= size)
    {
      block.used = true;
      return block.data; // Возвращаем указатель на данные
    }
    blockStart = static_cast<char *>(blockStart) + block.size;
  }

  size_t remainingHeap = static_cast<char *>(heapStart) + heapSize -
                         static_cast<char *>(blockStart);
  if (remainingHeap < size)
  {
    std::cerr << "Heap out of memory." << std::endl;
    return nullptr;
  }

  // Выделяем память для нового блока и сохраняем указатель на данные
  void *data = blockStart;
  blocks.push_back({data, size, true});
  return data;
}

void Heap::free(void *ptr)
{
  for (auto &block : blocks)
  {
    if (block.data == ptr && block.used)
    {
      block.used = false;
      return;
    }
  }
  std::cerr << "Attempt to free unallocated or already freed block."
            << std::endl;
}

void Heap::logUsage() const
{
  std::cout << "Heap Size: " << heapSize << " bytes" << std::endl;
  for (const auto &block : blocks)
  {
    std::cout << "Block at " << block.data << " - Size: " << block.size
              << " bytes - " << (block.used ? "Used" : "Free") << "\n";
  }
}
