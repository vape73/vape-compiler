#include "structures.h"

Node **Queue::allocate_node()
{
    if (auto ptr = heap->allocate(sizeof(Node)))
    {
        return reinterpret_cast<Node **>(ptr);
    }

    return nullptr;
}

Node **Queue::new_queue(int data)
{
    if (auto head = allocate_node())
    {

        (*head)->data = data;
        (*head)->next = nullptr;

        return head;
    }

    return nullptr;
}

Node **Queue::push(Node **head, int data)
{
    log(head);
    if (auto new_node = allocate_node())
    {
        (*new_node)->data = data;
        (*new_node)->next = nullptr;

        if (*head == nullptr)
        {
            log(new_node);
            return new_node;
        }

        auto q = head;

        while ((*q)->next != nullptr)
        {
            q = (*q)->next;
        }

        (*q)->next = new_node;

        log(head);
        return head;
    }
    return nullptr;
}

Node **Queue::pop(Node **head)
{
    log(head);
    auto new_head = (*head)->next;
    heap->free(*head);

    log(new_head);
    return new_head;
}

void Queue::log(Node **head)
{
    if (head == nullptr || *head == nullptr)
    {
        std::cout << "empty queue!\n";
    }
    auto q = head;

    std::cout << "QUEUE: ";

    while (q)
    {
        std::cout << (*q)->data << " ";
        q = (*q)->next;
    }
    std::cout << std::endl;
}