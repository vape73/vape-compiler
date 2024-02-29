#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "structures.h"

int main()
{
    auto heap = new Heap(1024);
    auto stack = new Stack(heap);
    auto queue = new Queue(heap);
    auto deque = new Deque(heap);

//    auto stack_head = stack->new_stack(1);
//    stack_head = stack->push(stack_head, 2);
//    stack_head = stack->push(stack_head, 3);
//
//    auto queue_head = queue->new_queue(1);
//    queue_head = queue->push(queue_head, 2);
//    queue_head = queue->push(queue_head, 3);
//
//    stack_head = stack->pop(stack_head);

    auto deque_head = deque->new_deque(1);
    deque_head = deque->push_front(deque_head, 2);
    // deque_head = deque->push_back(deque_head, 3);


}
