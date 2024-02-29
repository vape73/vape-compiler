#include "structures.h"

Node **Stack::allocate_node()
{
    if (auto ptr = heap->allocate(sizeof(Node)))
    {
        return reinterpret_cast<Node **>(ptr);
    }

    return nullptr;
}

Node **Stack::new_stack(int data)
{
    if (auto head = allocate_node())
    {

        (*head)->data = data;
        (*head)->next = nullptr;

        return head;
    }

    return nullptr;
}

Node **Stack::push(Node **head, int data)
{
    log(head);
    if (auto new_node = allocate_node())
    {
        (*new_node)->data = data;
        (*new_node)->next = head;

        log(new_node);
        return new_node;
    }
    return nullptr;
}

Node **Stack::pop(Node **head)
{
    log(head);
    auto new_head = (*head)->next;
    heap->free(*head);
    
    log(new_head);
    return new_head;
}

void Stack::log(Node **head)
{
    if (head == nullptr || *head == nullptr)
    {
        std::cout << "empty stack!\n";
    }
    auto q = head;

    std::cout << "STACK: ";

    while (q)
    {
        std::cout << (*q)->data << " ";
        q = (*q)->next;
    }
    std::cout << std::endl;
}