#include "List.h"

struct List::Node {
    Array value;
    Node* next;
    Node(Array& v) : value(v), next(nullptr) {}
};

List::List() : head(nullptr), tail(nullptr), count(0) {}

List::~List() {
    clear();
}

void List::pushBack(Array& arr) {
    Node* node = new Node(arr);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    ++count;
}

void List::popBack() {
    if (!head) return;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        count = 0;
        return;
    }
    Node* curr = head;
    while (curr->next != tail)
        curr = curr->next;
    delete tail;
    tail = curr;
    tail->next = nullptr;
    --count;
}

Array& List::peek() {
    return tail->value;
}

Array& List::get(int index) {
    Node* curr = head;
    for (int i = 0; i < index; ++i)
        curr = curr->next;
    return curr->value;
}

int List::size() {
    return count;
}

bool List::empty() {
    return count == 0;
}

void List::clear() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
    count = 0;
}
