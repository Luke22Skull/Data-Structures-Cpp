#ifndef DICTSORTEDVEC_H
#define DICTSORTEDVEC_H

#include <iostream>
#include <stdexcept>

using namespace std;
const int MAX_SIZE = 100;

template <typename T>
class Sorted_Vector_Dictionary {
private:
    struct Pair {
        string key;
        T value;
    };
    Pair data[MAX_SIZE];
    int size;

public:
    Sorted_Vector_Dictionary() : size(0) {}

    bool isEmpty() {
        return size == 0;
    }

    void inserisci(string key, T value) {
        int i = size - 1;
        while (i >= 0 && data[i].key > key) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = {key, value};
        size++;
    }

    bool appartiene(string key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) return true;
        }
        return false;
    }

    void cancella(string key) {
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

    T recupera(string key) {
        for (int i = 0; i < size; i++) {
            if (data[i].key == key) return data[i].value;
        }
        throw runtime_error("Chiave non trovata");
    }
};

#endif
