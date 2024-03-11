#ifndef HASHTABLE_H
#define HASHTABLE_H

#define FILL_FACTOR 75

#include <iostream>
#include "Heap/Heap.h"

template <typename T>
struct HashTableElement
{
    std::string key = "";
    T value;
};

template <typename T>
struct HashTable
{
    Heap *heap;
    HashTableElement<T> **elements;
    int capacity = 32;
    int count = 0;

    long hash(std::string key)
    {
        long sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i] * (i + 1);
        return sum;
    }

    void init(Heap *input_heap)
    {
        heap = input_heap;
        void **raw_elements = heap->allocate(sizeof(capacity * sizeof(HashTableElement<T>)));
        elements = reinterpret_cast<HashTableElement<T> **>(raw_elements);
    }

    void realloc()
    {
        if (count / capacity * 100 >= FILL_FACTOR)
        {
            void **new_elements = heap->allocate(sizeof(2 * capacity * sizeof(HashTableElement<T>)));
            memcpy(*new_elements, *elements, capacity * sizeof(HashTableElement<T>));
            heap->free(*elements);
            elements = reinterpret_cast<HashTableElement<T> **>(new_elements);
            ;
            capacity *= 2;
        }
    }

    void set(std::string key, T value)
    {
        realloc();
        long hashed_key = hash(key);
        if ((*elements)[hashed_key].key != "")
        {
            long temp = hashed_key + 1;
            while ((*elements)[temp].key != "")
                temp++;
            (*elements)[temp].key = key;
            (*elements)[temp].value = value;
        }
        else
        {
            (*elements)[hashed_key].key = key;
            (*elements)[hashed_key].value = value;
        };
        count++;
    }

    T get(std::string key)
    {
        long hashed_key = hash(key);
        if ((*elements)[hashed_key].key == key)
        {
            return (*elements)[hashed_key].value;
        }
        else
        {
            for (int i = hashed_key + 1; i < hashed_key + capacity; i++)
            {
                if (i == hashed_key)
                    break;
                if ((*elements)[i].key == key)
                    return (*elements)[i].value;
            }
            return NULL;
        }
    }
};

#endif // HASHTABLE_H