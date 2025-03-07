#ifndef GRAPHEXTMTX_H
#define GRAPHEXTMTX_H 

#include <iostream>
#include <stdexcept>
#include "PTRQueue.h"
#include "PTRStack.h"

template <class T>
class GrafoMatAdiacenzaEstesa {
private:
    static const int MAX_NODI = 100;
    int matrice[MAX_NODI][MAX_NODI];
    T valori[MAX_NODI];
    int numNodi;

    int trovaIndiceNodo(T valore) const {
        for (int i = 0; i < numNodi; ++i) {
            if (valori[i] == valore)
                return i;
        }
        return -1;
    }

public:
    GrafoMatAdiacenzaEstesa() : numNodi(0) {
        for (int i = 0; i < MAX_NODI; ++i) {
            for (int j = 0; j < MAX_NODI; ++j) {
                matrice[i][j] = 0;
            }
            valori[i] = -1;
        }
    }

    bool vuoto() const {
        return numNodi == 0;
    }

    void insnodo(T valore) {
        if (numNodi >= MAX_NODI)
            throw std::overflow_error("Numero massimo di nodi raggiunto");
        valori[numNodi] = valore;
        ++numNodi;
    }

    void insarco(int u, int v, int peso = 1) {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("Nodo non valido");
        if (peso <= 0)
            throw std::invalid_argument("Il peso deve essere positivo");
        matrice[u][v] = peso;
    }

    void cancnodo(T valore) {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        for (int i = 0; i < numNodi; ++i) {
            matrice[i][nodo] = 0;
            matrice[nodo][i] = 0;
        }
        valori[nodo] = -1;
    }

    void cancarco(int u, int v) {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("Nodo non valido");
        matrice[u][v] = 0;
    }

    void adiacenti(T valore) const {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        for (int i = 0; i < numNodi; ++i) {
            if (matrice[nodo][i] > 0)
                std::cout << valori[i] << " ";
        }
        std::cout << std::endl;
    }

    bool esistenodo(T valore) const {
        return trovaIndiceNodo(valore) != -1;
    }

    bool esistearco(int u, int v) const {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("Nodo non valido");
        return matrice[u][v] > 0;
    }

    int legginodo(T valore) const {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        return nodo;
    }

    int leggipeso(int u, int v) const {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("Nodo non valido");
        return matrice[u][v];
    }

    void stampamatrice() const {
        std::cout << "Matrice di Adiacenza Estesa:\n";
        for (int i = 0; i < numNodi; ++i) {
            for (int j = 0; j < numNodi; ++j) {
                std::cout << matrice[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs(T valoreIniziale, T valoreDaCercare) {
        int nodoIniziale = trovaIndiceNodo(valoreIniziale);
        if (nodoIniziale == -1)
            throw std::invalid_argument("Nodo iniziale non trovato");

        bool visitato[MAX_NODI] = {false};
        PTR_Queue<int> coda;

        coda.pushTail(nodoIniziale);
        visitato[nodoIniziale] = true;

        while (!coda.isEmptyCoda()) {
            int nodoCorrente = coda.readHead();
            coda.deleteHead();

            if (valori[nodoCorrente] == valoreDaCercare) {
                std::cout << "Nodo trovato con valore: " << valoreDaCercare << std::endl;
                return;
            }

            for (int i = 0; i < numNodi; ++i) {
                if (matrice[nodoCorrente][i] > 0 && !visitato[i]) {
                    coda.pushTail(i);
                    visitato[i] = true;
                }
            }
        }

        std::cout << "Nodo con valore " << valoreDaCercare << " non trovato." << std::endl;
    }

    void dfs(T valoreIniziale, T valoreDaCercare) {
        int nodoIniziale = trovaIndiceNodo(valoreIniziale);
        if (nodoIniziale == -1)
            throw std::invalid_argument("Nodo iniziale non trovato");

        bool visitato[MAX_NODI] = {false};
        PTR_Stack<int> pila;

        pila.pushStack(nodoIniziale);

        while (!pila.isEmptyStack()) {
            int nodoCorrente = pila.readStack();
            pila.popStack();

            if (!visitato[nodoCorrente]) {
                visitato[nodoCorrente] = true;

                if (valori[nodoCorrente] == valoreDaCercare) {
                    std::cout << "Nodo trovato con valore: " << valoreDaCercare << std::endl;
                    return;
                }

                for (int i = 0; i < numNodi; ++i) {
                    if (matrice[nodoCorrente][i] > 0 && !visitato[i]) {
                        pila.pushStack(i);
                    }
                }
            }
        }

        std::cout << "Nodo con valore " << valoreDaCercare << " non trovato." << std::endl;
    }
};

#endif
