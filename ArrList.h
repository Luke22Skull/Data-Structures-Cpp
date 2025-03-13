#ifndef ARRLIST_H
#define ARRLIST_H

#include <iostream>
#include <stdexcept>
const int MAX_SIZE = 100;   // Max List size
using namespace std;

// LIST - Array
template <typename T>
class ArrList {
private:
    T array[MAX_SIZE];  // Actual List
    int size;   // size of the array

public:
    // Constructor: initialize array with size = 0
    ArrList() : size(0) {}

    // Destructor
    ~ArrList() {
        while (!isEmptyList())
            deleteList(0);
    }

    // getter: gets the size of the array
    int getSize() const {
        return size;
    }

    // checks if the list is empty
    bool isEmptyList() const {
        return size == 0;
    }

    // reads the value at a given index
    T readValueAtIndex(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        return array[index];
    }

    // modifies the value at a given index with a new value
    void writeValue(T value, int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        array[index] = value;
    }

    // gets the first element in list
    T firstInList() const {
        return array[0];
    }

    // checks if the list is full
    bool endList(int index) const {
        return index == size;
    }
    
    // gets the next value in the array with a given index
    T nextValue(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        return array[index + 1];
    }

    // gets the previous value in the array with a given index
    T previousValue(int index) const {
        if (index <= 0 || index > size) {
            throw out_of_range("Index error");
        }
        return array[index - 1];
    }

    // shifts values and inserts a new value
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

    // deletes value at a given index, then shifts
    void deleteList(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index error");
        }
        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    // prints the list
    void printList() const {
        for (int i = 0; i < size; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

#endif
