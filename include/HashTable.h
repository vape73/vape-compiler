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
    int capacity;
    int count;

    long hash(std::string key)
    {
        long sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i] * (i + 1);
        return sum % capacity;
    }

    void init(Heap *input_heap)
    {
        heap = input_heap;
        capacity = 32;
        count = 0;
        void **raw_elements = heap->allocate(sizeof(capacity * sizeof(HashTableElement<T>)));
        elements = reinterpret_cast<HashTableElement<T> **>(raw_elements);
    }

    void realloc()
    {
        int new_capacity = 2 * capacity;
        void **new_elements = heap->allocate(sizeof(new_capacity * sizeof(HashTableElement<T>)));
        HashTableElement<T> **new_elements_ptr = reinterpret_cast<HashTableElement<T> **>(new_elements);

        for (int i = 0; i < capacity; ++i)
        {
            if ((*elements)[i].key != "")
            {
                long hashed_key = hash((*elements)[i].key) % new_capacity;
                while ((*new_elements_ptr)[hashed_key].key != "")
                {
                    hashed_key = (hashed_key + 1) % new_capacity;
                }
                (*new_elements_ptr)[hashed_key] = (*elements)[i];
            }
        }

        heap->free(*elements);

        elements = new_elements_ptr;
        capacity = new_capacity;
    }

    void set(std::string key, T value)
    {
        if (count / capacity * 100 >= FILL_FACTOR)
        {
            realloc();
        }

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
            // std::cerr << "ERROR: key " << key << " not found\n";
            throw "Unexpected key";
        }

        return T();
    }

    void remove(std::string key)
    {
        long hashed_key = hash(key);
        if ((*elements)[hashed_key].key == key)
        {
            (*elements)[hashed_key].key = "";
            (*elements)[hashed_key].value = T();
            count--;
        }
        else
        {
            for (int i = hashed_key + 1; i < hashed_key + capacity; i++)
            {
                if ((*elements)[i].key == key)
                {
                    (*elements)[i].key = "";
                    (*elements)[i].value = T();
                    count--;
                    break;
                }
            }
        }
    }

    void clear()
    {
        for (int i = 0; i < capacity; i++)
        {
            (*elements)[i].key = "";
            (*elements)[i].value = T();
        }
        count = 0;
    }

    void log()
    {
        if (!count)
        {
            std::cout << "EMPTY HASH TABLE" << std::endl
                      << std::endl;
            return;
        }
        std::cout << "HASH TABLE HAS " << count << " ELEMENTS:" << std::endl;
        for (int i = 0; i < capacity; i++)
        {
            if ((*elements)[i].key != "")
            {
                std::cout << "KEY: " << (*elements)[i].key << ", VALUE: " << (*elements)[i].value << std::endl;
            }
        }
        std::cout << std::endl
                  << std::endl;
    }
};

#endif // HASHTABLE_H
