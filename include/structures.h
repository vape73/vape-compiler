#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Heap/Heap.h"

struct Node
{
    Node **next;
    int data;
};

struct DequeNode : Node
{
    DequeNode **next;
    DequeNode **prev;
};

class DynamicStructure
{
protected:
    Heap *heap;

public:
    DynamicStructure(Heap *heap) : heap(heap) {}
};

class Stack : public DynamicStructure
{
private:
    Node **allocate_node();

public:
    Stack(Heap *heap) : DynamicStructure(heap) {}
    Node **new_stack(int data);
    Node **push(Node **head, int data);
    Node **pop(Node **head);
    void log(Node **head);
};

class Queue : public DynamicStructure
{
private:
    Node **allocate_node();

public:
    Queue(Heap *heap) : DynamicStructure(heap) {}
    Node **new_queue(int data);
    Node **push(Node **head, int data);
    Node **pop(Node **head);
    void log(Node **head);
};

class Deque : public DynamicStructure
{
private:
    DequeNode **allocate_node();

public:
    Deque(Heap *heap) : DynamicStructure(heap) {}
    DequeNode **new_deque(int data);
    DequeNode **push_front(DequeNode **head, int data);
    DequeNode **push_back(DequeNode **head, int data);
    DequeNode **pop_front(DequeNode **head);
    DequeNode **pop_back(DequeNode **head);
    void log(DequeNode **head);
};

#endif // STRUCTURES_H