#ifndef DICTSORTEDVEC_H
#define DICTSORTEDVEC_H
#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class Sorted_Vector_Dictionary {
private:
    struct Pair { // Pair structure to hold key-value pairs
        string key;
        T value;
    };
    Pair data[MAX_SIZE]; // Array to store the pairs
    int size; // Current size of the dictionary

public:
    Sorted_Vector_Dictionary() : size(0) {} // Constructor

    // Check if the dictionary is empty
    bool isEmpty() {
        return size == 0;
    }

    // Insert a new key-value pair into the dictionary
    void insert(string key, T value) {
        int i = size - 1;
        while (i >= 0 && data[i].key > key) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = {key, value};
        size++;
    }

    // Check if a key exists in the dictionary
    bool belongs(string key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) return true;
        }
        return false;
    }

    // Delete a key-value pair from the dictionary
    void deleteKey(string key) {
        int i;
        for (i = 0; i < size; i++) {
            if (data[i].key == key) break;
        }
        if (i == size) return;
        while (i < size - 1) {
            data[i] = data[i + 1];
            i++;
        }
        size--;
    }

    // Retrieve the value associated with a key
    T retrieve(string key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) return data[i].value;
        }
        throw runtime_error("Key not found");
    }
};

#endif
