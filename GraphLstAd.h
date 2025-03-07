#ifndef GRAPHLSTAD_H
#define GRAPHLSTAD_H

#include <iostream>
#include <stdexcept>

template <class T>
class GrafoListaAdiacenza {
private:
    static const int MAX_NODI = 100;
    struct Nodo {
        T valore;
        Nodo* prossimo;
        Nodo(T val) : valore(val), prossimo(nullptr) {}
    };
    
    Nodo* adiacenze[MAX_NODI]; // Array di puntatori a liste di adiacenza
    T valori[MAX_NODI]; // Valori dei nodi
    int numNodi;

    int trovaIndiceNodo(T valore) const {
        for (int i = 0; i < numNodi; ++i) {
            if (valori[i] == valore)
                return i;
        }
        return -1;
    }

public:
    GrafoListaAdiacenza() : numNodi(0) {
        for (int i = 0; i < MAX_NODI; ++i) {
            adiacenze[i] = nullptr;
        }
    }

    bool vuoto() const {
        return numNodi == 0;
    }

    void insnodo(T valore) {
        if (numNodi >= MAX_NODI)
            throw std::overflow_error("Numero massimo di nodi raggiunto");
        valori[numNodi++] = valore;
    }

    void insarco(T val1, T val2) {
        int u = trovaIndiceNodo(val1);
        int v = trovaIndiceNodo(val2);
        if (u == -1 || v == -1)
            throw std::out_of_range("Nodo non valido");
        Nodo* nuovo = new Nodo(val2);
        nuovo->prossimo = adiacenze[u];
        adiacenze[u] = nuovo;
    }

    void cancnodo(T valore) {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        while (adiacenze[nodo] != nullptr) {
            Nodo* temp = adiacenze[nodo];
            adiacenze[nodo] = adiacenze[nodo]->prossimo;
            delete temp;
        }
        valori[nodo] = T{};
    }

    void cancarco(T val1, T val2) {
        int u = trovaIndiceNodo(val1);
        // int v = trovaIndiceNodo(val2);
        if (u == -1)
            throw std::out_of_range("Nodo non valido");
        Nodo* temp = adiacenze[u];
        Nodo* prev = nullptr;
        while (temp != nullptr && temp->valore != val2) {
            prev = temp;
            temp = temp->prossimo;
        }
        if (temp != nullptr) {
            if (prev != nullptr)
                prev->prossimo = temp->prossimo;
            else
                adiacenze[u] = temp->prossimo;
            delete temp;
        }
    }

    void adiacenti(T valore) const {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        Nodo* temp = adiacenze[nodo];
        while (temp != nullptr) {
            std::cout << temp->valore << " ";
            temp = temp->prossimo;
        }
        std::cout << std::endl;
    }

    bool esistenodo(T valore) const {
        return trovaIndiceNodo(valore) != -1;
    }

    bool esistearco(T val1, T val2) const {
        int u = trovaIndiceNodo(val1);
        if (u == -1)
            throw std::out_of_range("Nodo non valido");
        Nodo* temp = adiacenze[u];
        while (temp != nullptr) {
            if (temp->valore == val2)
                return true;
            temp = temp->prossimo;
        }
        return false;
    }

    void stampalista() const {
        for (int i = 0; i < numNodi; ++i) {
            if (valori[i] != T{}) {
                std::cout << "Nodo " << valori[i] << ": ";
                Nodo* temp = adiacenze[i];
                while (temp != nullptr) {
                    std::cout << temp->valore << " ";
                    temp = temp->prossimo;
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif

