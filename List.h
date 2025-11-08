#ifndef LAB2_LIST_H
#define LAB2_LIST_H

#include <iostream>
#include "Array.h"

class List {
private:
    struct Node;

    Node* head;
    Node* tail;
    int count;

public:
    List();
    ~List();

    void pushBack(Array& arr);
    void popBack();
    Array& peek();
    Array& get(int index);

    int size();
    bool empty();
    void clear();
};

#endif // LAB2_LIST_H
