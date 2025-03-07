#ifndef GRAPHMTXINCIDENCE_H
#define GRAPHMTXINCIDENCE_H

#include <iostream>
#include <stdexcept>

template <class T>
class GrafoMatIncidenza {
private:
    static const int MAX_NODI = 100;
    static const int MAX_ARCHI = 200;
    int matrice[MAX_NODI][MAX_ARCHI]; // Matrice di incidenza
    T valori[MAX_NODI]; // Valori dei nodi
    int numNodi;
    int numArchi;

    int trovaIndiceNodo(T valore) const {
        for (int i = 0; i < numNodi; ++i) {
            if (valori[i] == valore)
                return i;
        }
        return -1;
    }

public:
    GrafoMatIncidenza() : numNodi(0), numArchi(0) {
        for (int i = 0; i < MAX_NODI; ++i) {
            valori[i] = -1;
            for (int j = 0; j < MAX_ARCHI; ++j) {
                matrice[i][j] = 0;
            }
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
        if (u == -1 || v == -1 || numArchi >= MAX_ARCHI)
            throw std::out_of_range("Nodo o arco non valido");
        matrice[u][numArchi] = 1;
        matrice[v][numArchi] = -1;
        numArchi++;
    }

    void cancnodo(T valore) {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        valori[nodo] = -1;
        for (int j = 0; j < numArchi; ++j) {
            matrice[nodo][j] = 0;
        }
    }

    void cancarco(int indiceArco) {
        if (indiceArco >= numArchi)
            throw std::out_of_range("Arco non valido");
        for (int i = 0; i < numNodi; ++i) {
            matrice[i][indiceArco] = 0;
        }
    }

    void adiacenti(T valore) const {
        int nodo = trovaIndiceNodo(valore);
        if (nodo == -1)
            throw std::invalid_argument("Nodo non trovato");
        for (int j = 0; j < numArchi; ++j) {
            if (matrice[nodo][j] != 0) {
                for (int i = 0; i < numNodi; ++i) {
                    if (matrice[i][j] != 0 && i != nodo)
                        std::cout << valori[i] << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    bool esistenodo(T valore) const {
        return trovaIndiceNodo(valore) != -1;
    }

    bool esistearco(T val1, T val2) const {
        int u = trovaIndiceNodo(val1);
        int v = trovaIndiceNodo(val2);
        if (u == -1 || v == -1)
            throw std::out_of_range("Nodo non valido");
        for (int j = 0; j < numArchi; ++j) {
            if (matrice[u][j] == 1 && matrice[v][j] == -1)
                return true;
        }
        return false;
    }

    void stampamatrice() const {
        std::cout << "Matrice di Incidenza:\n";
        for (int i = 0; i < numNodi; ++i) {
            for (int j = 0; j < numArchi; ++j) {
                std::cout << matrice[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif

