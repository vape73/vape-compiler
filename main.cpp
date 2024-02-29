#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "List/Stack.h"
#include "List/Queue.h"
#include "List/Deque.h"

int main()
{
    Heap heap(1024); // Инициализация кучи с размером 1024 байта

    // Демонстрация работы со стеком
    Stack stack(heap, sizeof(int));
    int a = 1, b = 2, c = 3;
    stack.add(&a);
    stack.add(&b);
    stack.add(&c);
    stack.log();
    heap.logUsage();

    stack.remove(); // Удаление последнего элемента (c)
    stack.log();
    heap.logUsage();

    // Демонстрация работы с очередью
    Queue queue(heap, sizeof(int));
    queue.add(&a);
    queue.add(&b);
    queue.add(&c);
    queue.log();
    heap.logUsage();

    queue.remove(); // Удаление первого элемента (a)
    queue.log();
    heap.logUsage();

    heap.free(*ptr2);
    heap.free(*ptr4);
    heap.free(*ptr3);
    // Демонстрация работы с деком
    Deque deque(heap, sizeof(int));
    deque.addFront(&b); // Добавление в начало
    deque.addFront(&a); // Добавление в начало
    deque.addBack(&c);  // Добавление в конец
    deque.log();
    heap.logUsage();

    deque.removeFront(); // Удаление из начала (b)
    deque.log();
    heap.logUsage();

    auto ptr6 = heap.allocate(1024);
    auto ptr7 = heap.allocate(150);
    auto ptr8 = heap.allocate(150);
    auto ptr9 = heap.allocate(150);// Попытка выделить больше памяти, чем доступно
    auto ptr10 = heap.allocate(100);

    heap.logUsage();

    return 0;
}
