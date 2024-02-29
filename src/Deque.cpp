#include "structures.h"

DequeNode **Deque::allocate_node() {
  heap->logUsage();
  if (auto ptr = heap->allocate(sizeof(DequeNode))) {
    return reinterpret_cast<DequeNode **>(ptr);
  }

  return nullptr;
}

DequeNode **Deque::new_deque(int data) {
  if (auto head = allocate_node()) {

    (*head)->data = data;
    (*head)->next = nullptr;
    (*head)->prev = nullptr;
    return head;
  }

  return nullptr;
}

DequeNode **Deque::push_front(DequeNode **head, int data) {
  log(head);
  if (auto new_node = allocate_node()) {
    (*new_node)->data = data;

    if (head == nullptr || *head == nullptr) {
      (*new_node)->prev = new_node;
      (*new_node)->next = new_node;
      log(new_node);
      return new_node;
    }

    (*new_node)->next = head;
    (*new_node)->prev = (*head)->prev;
    (*(*head)->prev)->next = new_node;
    (*head)->prev = new_node;

    log(new_node);
    return new_node;
  }
}

DequeNode **Deque::push_back(DequeNode **head, int data) {
  log(head);
  if (auto new_node = allocate_node()) {
    (*new_node)->data = data;

    if (*head == nullptr) {
      (*new_node)->prev = new_node;
      (*new_node)->next = new_node;
      log(new_node);
      return new_node;
    }

    (*new_node)->next = head;
    (*new_node)->prev = (*head)->prev;
    (*(*head)->prev)->next = new_node;
    (*head)->prev = new_node;

    log(head);
    return head;
  }
}

DequeNode **Deque::pop_front(DequeNode **head) {
  log(head);
  if (*head == nullptr || (*head)->next == head) {
    log(nullptr);
    return nullptr;
  }

  auto new_head = (*head)->next;
  (*(*head)->prev)->next = (*head)->next;
  (*(*head)->next)->prev = (*head)->prev;
  heap->free(*head);

  log(new_head);
  return new_head;
}

DequeNode **Deque::pop_back(DequeNode **head) {
  log(head);
  if (*head == nullptr || (*head)->next == head) {
    log(nullptr);
    return nullptr;
  }

  (*head)->prev = (*(*head)->prev)->prev;
  (*(*head)->prev)->next = head;
  heap->free((*head)->prev);

  log(head);
  return head;
}

void Deque::log(DequeNode **head) {
  if (head == nullptr || *head == nullptr) {
    std::cout << "empty deque!\n";
  }
  auto q = head;

  std::cout << "DEQUE: ";
  while (q) {
    std::cout << (*q)->data << " ";
    q = (*q)->next;
  }
  std::cout << std::endl;
}
