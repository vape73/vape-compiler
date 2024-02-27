#include "Heap/Heap.h"

Heap::Heap(size_t size) {
    heapStart = malloc(size); // Используем malloc для выделения памяти
    heapTop = heapStart;
    if (heapStart == nullptr) {
        std::cerr << "Failed to allocate heap." << std::endl;
        exit(1);
    }
    heapSize = size;
    blocks.reserve(size);
}

Heap::~Heap() {
    std::free(heapStart); // Освобождаем всю выделенную память
}

void **Heap::allocate(size_t size) {
    // Проверяем, есть ли достаточно свободного места
    if (get_free_space() < size) {
        std::cerr << "Heap out of memory." << std::endl;
        return nullptr;
    }

    // Проверяем, есть ли подходящий блок для выделения памяти
    auto freeHole = findMinSuitableBlock(size);
    if (freeHole != blocks.end()) {
        splitBlock(freeHole, size);
        freeHole->used = true;
        return &(freeHole->data);
    }

    if (getUnmarkedSpace() < size) {
        std::cerr << "Heap out of memory." << std::endl;
        return nullptr;
    }

    // Выделяем память для нового блока и сохраняем указатель на данные

    void *data = heapTop;
    Block new_block = {data, size, true};
    blocks.push_back(new_block);
    heapTop = static_cast<void *>(static_cast<char *>(heapTop) + size);
    return &((blocks.end() - 1)->data);
}

void Heap::free(void *ptr) {
    auto block = findBlock(ptr);
    if (block == blocks.end()) {
        std::cerr << "Attempt to free unallocated or already freed block."
                  << std::endl;
        return;
    }

    block->used = false;
    mergeBlocks(block);
}

void Heap::logUsage() const {
    std::cout << "Heap Size: " << heapSize << " bytes" << std::endl;
    for (const auto &block: blocks) {
        std::cout << "Block at " << block.data << " - Size: " << block.size
                  << " bytes - " << (block.used ? "Used" : "Free") << "\n";
    }
}

size_t Heap::getUnmarkedSpace() {
    return static_cast<char *>(heapStart) + heapSize -
           static_cast<char *>(heapTop);
}

std::vector<Block>::iterator Heap::findBlock(void *ptr) {
    auto it = blocks.begin();
    for (; it != blocks.end(); ++it) {
        if (it->data == ptr && it->used)
            break;
    }
    return it;
}

// функция возвращающая свободное место исходя из неразмеченногоместа в
// конце кучи и неиспользованных блоков
size_t Heap::get_free_space() {
    size_t freeSpace = 0;
    for (const auto &block: blocks) {
        if (!block.used) {
            freeSpace += block.size;
        }
    }
    freeSpace += getUnmarkedSpace();
    return freeSpace;
}

std::vector<Block>::iterator Heap::findMinSuitableBlock(size_t size) {
    auto minBlockIt = blocks.end();
    size_t minSize = std::numeric_limits<size_t>::max();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->used && it->size >= size && it->size < minSize) {
            minSize = it->size;
            minBlockIt = it;
        }
    }

    return minBlockIt;
}

void Heap::splitBlock(std::vector<Block>::iterator blockIt, size_t size) {
    void *newBlockData = static_cast<char *>(blockIt->data) + size;
    size_t newSize = blockIt->size - size;

    // Создание нового свободного блока с оставшимся размером
    blocks.insert(blockIt + 1, {newBlockData, newSize, false});

    // Обновление размера существующего блока
    blockIt->size = size;
}

// Функция для объединения двух смежных свободных блоков вокруг указанного

void Heap::mergeBlocks(std::vector<Block>::iterator blockIt) {
    auto nextIt = blockIt + 1;
    if (nextIt != blocks.end() && !nextIt->used) {
        blockIt->size += nextIt->size;
        blocks.erase(nextIt);
    }

    if (blockIt != blocks.begin()) {

        auto prevIt = blockIt - 1;
        if (!prevIt->used) {
            blockIt->data = prevIt->data;
            blockIt->size += prevIt->size;
            blocks.erase(prevIt);
        }
    }
}