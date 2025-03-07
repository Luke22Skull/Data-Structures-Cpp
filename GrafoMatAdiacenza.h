#ifndef GRAFOMATADIACENZA_H
#define GRAFOMATADIACENZA_H

#include <iostream>
#include <stdexcept>
#include "PTRStack.h"
#include "PTRQueue.h"

template <class T>
class GrafoMatAdiacenza {
private:
    static const int MAX_NODI = 100;
    bool matrice[MAX_NODI][MAX_NODI];
    T valori[MAX_NODI];
    int numNodi;

    int trovaNodo(const T& valore) const {
        for (int i = 0; i < numNodi; ++i) {
            if (valori[i] == valore)
                return i;
        }
        return -1;
    }

public:
    GrafoMatAdiacenza() : numNodi(0) {
        for (int i = 0; i < MAX_NODI; ++i) {
            for (int j = 0; j < MAX_NODI; ++j) {
                matrice[i][j] = false;
            }
            valori[i] = T(); // Inizializza con il valore di default del tipo T
        }
    }

    bool vuoto() const {
        return numNodi == 0;
    }

    void insnodo(const T& valore) {
        if (numNodi >= MAX_NODI)
            throw std::overflow_error("Numero massimo di nodi raggiunto");
        valori[numNodi] = valore;
        ++numNodi;
    }

    void insarco(int u, int v) {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("insArco: Nodo non valido");
        matrice[u][v] = true;
    }

    void cancnodo(const T& valore) {
        int nodo = trovaNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        for (int i = 0; i < numNodi; ++i) {
            matrice[i][nodo] = false;
            matrice[nodo][i] = false;
        }
        valori[nodo] = T(); // Reimposta il valore di default del tipo T
        numNodi--;
    }

    void cancarco(int u, int v) {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("cancArco: Nodo non valido");
        matrice[u][v] = false;
    }

    void adiacenti(const T& valore) const {
        int nodo = trovaNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        for (int i = 0; i < numNodi; ++i) {
            if (matrice[nodo][i])
                std::cout << valori[i] << " ";
        }
        std::cout << std::endl;
    }

    bool esistenodo(const T& valore) const {
        return trovaNodo(valore) != -1;
    }

    bool esistearco(int u, int v) const {
        if (u >= numNodi || v >= numNodi)
            throw std::out_of_range("esistearco: Nodo non valido");
        return matrice[u][v];
    }

    int legginodo(const T& valore) const {
        int nodo = trovaNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        return nodo;
    }

    void stampamatrice() const {
        std::cout << "Matrice di Adiacenza:\n";
        for (int i = 0; i < numNodi; ++i) {
            for (int j = 0; j < numNodi; ++j) {
                std::cout << matrice[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs(const T& valoreIniziale, const T& valoreDaCercare) {
        int nodoIniziale = trovaNodo(valoreIniziale);
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
                if (matrice[nodoCorrente][i] && !visitato[i]) {
                    coda.pushTail(i);
                    visitato[i] = true;
                }
            }
        }

        std::cout << "Nodo con valore " << valoreDaCercare << " non trovato." << std::endl;
    }

    void dfs(const T& valoreIniziale, const T& valoreDaCercare) {
        int nodoIniziale = trovaNodo(valoreIniziale);
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
                    if (matrice[nodoCorrente][i] && !visitato[i]) {
                        pila.pushStack(i);
                    }
                }
            }
        }

        std::cout << "Nodo con valore " << valoreDaCercare << " non trovato." << std::endl;
    }
};

#endif
