#ifndef ARRLIST_H
#define ARRLIST_H

#include <iostream>
#include <stdexcept>
const int MAX_SIZE = 100;
using namespace std;

// LIST - Array
template <typename T>
class ArrList {
private:
    T array[MAX_SIZE];
    int size;

public:
    ArrList() : size(0) {}
    ~ArrList() {
        while (!isEmptyList())
            deleteList(0);
    }

    int getSize() const {
        return size;
    }

    bool isEmptyList() const {
        return size == 0;
    }

    T readValueAtIndex(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        return array[index];
    }

    void writeValue(T value, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        array[index] = value;
    }

    T firstInList() const {
        return array[0];
    }

    bool endList(int index) const {
        return index == size;
    }

    T nextValue(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        return array[index + 1];
    }

    T previousValue(int index) const {
        if (index <= 0 || index > size) {
            throw out_of_range("Index error");
        }
        return array[index - 1];
    }

    void insertValue(T value, int index) {
        if (index < 0 || index > size || size >= MAX_SIZE) {
            throw out_of_range("Index error");
        }
        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
    }

    void deleteList(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    void printList() const {
        for (int i = 0; i < size; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

#endif
