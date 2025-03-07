#ifndef ARRLIST_H
#define ARRLIST_H

#include <iostream>
#include <stdexcept>
const int MAX_SIZE = 100;
using namespace std;

// LISTA - Array
template <typename T>
class ArrList {
private:
    T array[MAX_SIZE];
    int size;

public:
    ArrList() : size(0) {}
    ~ArrList() {
        while (!listavuota())
            canclista(0);
    }

    int getSize() const {
        return size;
    }

    bool listavuota() const {
        return size == 0;
    }

    T leggilista(int posizione) const {
        if (posizione < 0 || posizione >= size) {
            throw out_of_range("Posizione non valida");
        }
        return array[posizione];
    }

    void scrivilista(T elemento, int posizione) {
        if (posizione < 0 || posizione >= size) {
            throw out_of_range("Posizione non valida");
        }
        array[posizione] = elemento;
    }

    T primolista() const {
        return array[0];
    }

    bool finelista(int posizione) const {
        return posizione == size;
    }

    int succlista(int posizione) const {
        if (posizione < 0 || posizione >= size) {
            throw out_of_range("Posizione non valida");
        }
        return posizione + 1;
    }

    int predlista(int posizione) const {
        if (posizione <= 0 || posizione > size) {
            throw out_of_range("Posizione non valida");
        }
        return posizione - 1;
    }

    void inslista(T elemento, int posizione) {
        if (posizione < 0 || posizione > size || size >= MAX_SIZE) {
            throw out_of_range("Posizione non valida");
        }
        for (int i = size; i > posizione; --i) {
            array[i] = array[i - 1];
        }
        array[posizione] = elemento;
        ++size;
    }

    void canclista(int posizione) {
        if (posizione < 0 || posizione >= size) {
            throw out_of_range("Posizione non valida");
        }
        for (int i = posizione; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
    }

    void stampaLista() const {
        for (int i = 0; i < size; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

#endif
