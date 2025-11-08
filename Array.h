#ifndef LAB2_ARRAY_H
#define LAB2_ARRAY_H

#include <iostream>

class Array {
private:
    int* arr;
    int size;

public:
    Array();
    Array(int inputSize);
    Array(const Array& value);
    ~Array();

    Array& operator=(Array& right);
    int getSize();
    int& operator[](int index);
    int* getArr();
    void resize(int newSize);
};

#endif // LAB2_ARRAY_H
