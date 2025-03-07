#ifndef GRAPHPTR_H
#define GRAPHPTR_H

#include <iostream>
#include <stdexcept>

template <class T>
class GrafoPuntatori {
private:
    struct Nodo {
        T valore;
        Nodo* successivo;
        Nodo(T val) : valore(val), successivo(nullptr) {}
    };

    struct ListaAdiacenza {
        Nodo* testa;
        ListaAdiacenza() : testa(nullptr) {}
    };

    struct Vertice {
        T valore;
        ListaAdiacenza adiacenti;
        Vertice* prossimo;
        Vertice(T val) : valore(val), prossimo(nullptr) {}
    };

    Vertice* testa;

    Vertice* trovaVertice(T valore) const {
        Vertice* temp = testa;
        while (temp) {
            if (temp->valore == valore)
                return temp;
            temp = temp->prossimo;
        }
        return nullptr;
    }

public:
    GrafoPuntatori() : testa(nullptr) {}

    bool vuoto() const {
        return testa == nullptr;
    }

    void insnodo(T valore) {
        if (esistenodo(valore))
            throw std::invalid_argument("Nodo già esistente");
        Vertice* nuovo = new Vertice(valore);
        nuovo->prossimo = testa;
        testa = nuovo;
    }

    void insarco(T u, T v) {
        Vertice* verticeU = trovaVertice(u);
        Vertice* verticeV = trovaVertice(v);
        if (!verticeU || !verticeV)
            throw std::out_of_range("Nodo non valido");
        Nodo* nuovo = new Nodo(v);
        nuovo->successivo = verticeU->adiacenti.testa;
        verticeU->adiacenti.testa = nuovo;
    }

    void cancnodo(T valore) {
        Vertice** ptr = &testa;
        while (*ptr && (*ptr)->valore != valore) {
            ptr = &((*ptr)->prossimo);
        }
        if (*ptr) {
            Nodo* tempA = (*ptr)->adiacenti.testa;
            while (tempA) {
                Nodo* daEliminare = tempA;
                tempA = tempA->successivo;
                delete daEliminare;
            }
            Vertice* daEliminare = *ptr;
            *ptr = (*ptr)->prossimo;
            delete daEliminare;
        }
    }

    void cancarco(T u, T v) {
        Vertice* verticeU = trovaVertice(u);
        if (!verticeU)
            throw std::out_of_range("Nodo non valido");
        Nodo** ptr = &(verticeU->adiacenti.testa);
        while (*ptr && (*ptr)->valore != v) {
            ptr = &((*ptr)->successivo);
        }
        if (*ptr) {
            Nodo* daEliminare = *ptr;
            *ptr = (*ptr)->successivo;
            delete daEliminare;
        }
    }

    void adiacenti(T valore) const {
        Vertice* vertice = trovaVertice(valore);
        if (!vertice)
            throw std::invalid_argument("Nodo non trovato");
        Nodo* temp = vertice->adiacenti.testa;
        while (temp) {
            std::cout << temp->valore << " ";
            temp = temp->successivo;
        }
        std::cout << std::endl;
    }

    bool esistenodo(T valore) const {
        return trovaVertice(valore) != nullptr;
    }

    bool esistearco(T u, T v) const {
        Vertice* verticeU = trovaVertice(u);
        if (!verticeU)
            throw std::out_of_range("Nodo non valido");
        Nodo* temp = verticeU->adiacenti.testa;
        while (temp) {
            if (temp->valore == v)
                return true;
            temp = temp->successivo;
        }
        return false;
    }

    void stampagrafo() const {
        Vertice* temp = testa;
        while (temp) {
            std::cout << "Nodo " << temp->valore << ": ";
            Nodo* adj = temp->adiacenti.testa;
            while (adj) {
                std::cout << adj->valore << " ";
                adj = adj->successivo;
            }
            std::cout << std::endl;
            temp = temp->prossimo;
        }
    }
};

#endif
