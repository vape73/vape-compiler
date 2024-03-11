#include "HashTable.h"

int main()
{
    auto heap = new Heap(1024);

    void **raw_hash_table = heap->allocate(sizeof(HashTable<int>));
    auto hash_table = reinterpret_cast<HashTable<int> **>(raw_hash_table);

    (*hash_table)->init(heap);

    (*hash_table)->set("one", 1);
    (*hash_table)->set("two", 2);

    std::cout << (*hash_table)->get("one") << std::endl;
    std::cout << (*hash_table)->get("two") << std::endl;
    (*hash_table)->remove("two");
    std::cout << (*hash_table)->get("two") << std::endl;

    heap->free(raw_hash_table);

    delete heap;

    return 0;
}