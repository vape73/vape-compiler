#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "Heap/Heap.h"

int main()
{
    Heap heap(2048); // Инициализируем кучу размером 2048 байт

    // Демо-режим
    auto ptr1 = heap.allocate(100);
    auto ptr2 = heap.allocate(200);
    auto ptr3 = heap.allocate(300);
    auto ptr4 = heap.allocate(400);
    auto ptr5 = heap.allocate(500);

    heap.logUsage();

    heap.free(*ptr2);
    heap.free(*ptr4);
    heap.free(*ptr3);

    heap.logUsage();

    auto ptr6 = heap.allocate(1024);
    auto ptr7 = heap.allocate(150);
    auto ptr8 = heap.allocate(150);
    auto ptr9 = heap.allocate(150);// Попытка выделить больше памяти, чем доступно
    auto ptr10 = heap.allocate(100);

    heap.logUsage();

    return 0;
}
