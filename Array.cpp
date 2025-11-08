#include "Array.h"
Array::Array() : arr(nullptr), size(0) {}

Array::Array(int inputSize) {
    if (inputSize > 0) {
        arr = new int[inputSize];
        for (int i = 0; i < inputSize; ++i)
            arr[i] = 0;
        size = inputSize;
    }
}

Array::Array(const Array& value) : arr(nullptr), size(0) {
    if (value.size == 0) return;
    arr = new int[value.size];
    for (int i = 0; i < value.size; ++i)
        arr[i] = value.arr[i];
    size = value.size;
}


Array& Array::operator=(Array& right) {
    if (this == &right)
        return *this;
    Array tmp(right);
    int* a = arr;
    arr = tmp.arr;
    tmp.arr = a;
    int b = size;
    size = tmp.size;
    tmp.size = b;
    return *this;
}

Array::~Array() {
    delete[] arr;
    arr = nullptr;
    size = 0;
}

int Array::getSize() {
    return size;
}

int& Array::operator[](int index) {
    return arr[index];
}


int* Array::getArr() {
    return arr;
}

void Array::resize(int newSize) {
    if (newSize == size)
        return;

    int* temp = nullptr;
    if (newSize > 0) {
        temp = new int[newSize];
        for (int i = 0; i < newSize && i < size; i++)
            temp[i] = arr[i];
        for (int i = size; i < newSize; i++)
            temp[i] = 0;
    }

    delete[] arr;
    arr = temp;
    size = newSize;
}
