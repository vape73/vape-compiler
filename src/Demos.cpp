#include "Demos.h"
#include "HashTable.h"

void Demos::heap()
{
    auto heap = new Heap(1024);

    // Демо-режим
    auto ptr1 = heap->allocate(100);
    auto ptr2 = heap->allocate(200);
    auto ptr3 = heap->allocate(300);
    auto ptr4 = heap->allocate(400);
    auto ptr5 = heap->allocate(500);

    heap->logUsage();

    heap->free(*ptr2);
    heap->free(*ptr4);
    heap->free(*ptr3);

    heap->logUsage();

    auto ptr6 = heap->allocate(1024);
    auto ptr7 = heap->allocate(150);
    auto ptr8 = heap->allocate(150);
    auto ptr9 = heap->allocate(150); // Попытка выделить больше памяти, чем доступно
    auto ptr10 = heap->allocate(100);

    heap->logUsage();

    delete heap;
}

void Demos::dynamic_structures() {}

void Demos::hash_table()
{
    auto heap = new Heap(1024);

    auto raw_hash_table = heap->allocate(sizeof(HashTable<int>));
    auto hash_table = reinterpret_cast<HashTable<int> **>(raw_hash_table);

    (*hash_table)->init(heap);

    (*hash_table)->log();

    (*hash_table)->set("one", 1);
    (*hash_table)->set("eno", 5);
    (*hash_table)->set("two", 2);

    (*hash_table)->log();

    std::cout << "TRY TO GET \"one\":\n" << (*hash_table)->get("one") << std::endl << std::endl;
    std::cout << "TRY TO GET \"eno\":\n" << (*hash_table)->get("eno") << std::endl << std::endl;
    std::cout << "TRY TO GET \"two\":\n" << (*hash_table)->get("two") << std::endl << std::endl;

    (*hash_table)->remove("two");

    (*hash_table)->log();
    
    std::cout << "TRY TO GET REMOVED \"two\":\n" << (*hash_table)->get("two") << std::endl << std::endl;

    heap->free(*raw_hash_table);

    delete heap;
}