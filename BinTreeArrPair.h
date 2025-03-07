#ifndef BINTREEARRPAIR_H
#define BINTREEARRPAIR_H

#include <iostream>
#include <stdexcept>
#include "ArrList.h"
using namespace std;

class ArrBinTree {
private:
    ArrList<std::pair<int, bool>> nodi;

public:
    ArrBinTree() {}

    bool isEmptyTree() const {
        return nodi.listavuota();
    }

    bool isEmptyDx(int posizione) const {
        int dx = 2 * posizione + 2;
        return dx >= nodi.getSize() || !nodi.leggilista(dx).second;
    }

    bool isEmptySx(int posizione) const {
        int sx = 2 * posizione + 1;
        return sx >= nodi.getSize() || !nodi.leggilista(sx).second;
    }

    bool isEmptyNode(int posizione) const {
        return isEmptyDx(posizione) && isEmptySx(posizione);
    }

    void setNodeData(int posizione, int valore) {
        if (posizione < 0 || posizione >= nodi.getSize()) {
            throw std::out_of_range("Posizione non valida");
        }
        nodi.scrivilista({valore, true}, posizione);
    }

    int getRoot() const {
        if (isEmptyTree()) throw std::runtime_error("Albero vuoto");
        return nodi.leggilista(0).first;
    }

    void insertFather(int valore) {
        nodi.inslista({valore, true}, 0);
    }

    void insertChildDx(int posizione, int valore) {
        int dx = 2 * posizione + 2;
        if (dx >= MAX_SIZE) throw std::out_of_range("Fuori dai limiti");
        nodi.inslista({valore, true}, dx);
    }

    void insertChildSx(int posizione, int valore) {
        int sx = 2 * posizione + 1;
        if (sx >= MAX_SIZE) throw std::out_of_range("Fuori dai limiti");
        nodi.inslista({valore, true}, sx);
    }

    void uniteTrees(ArrBinTree& T1, ArrBinTree& T2) {
        nodi.inslista({0, true}, 0);
        insertChildSx(0, T1.getRoot());
        insertChildDx(0, T2.getRoot());
    }

    void deleteSubBinTree(int posizione) {
        if (posizione < 0 || posizione >= nodi.getSize()) return;
        nodi.scrivilista({nodi.leggilista(posizione).first, false}, posizione);
        deleteSubBinTree(2 * posizione + 1);
        deleteSubBinTree(2 * posizione + 2);
    }

    void printTree() const {
        if (isEmptyTree()) {
            std::cout << "L'albero è vuoto." << std::endl;
            return;
        }

        cout << endl;
        int livello = 0;
        int elementiLivello = 1;
        int i = 0;
        while (i < nodi.getSize()) {
            // Stampa l'indentazione per il livello corrente
            int indentazione = (1 << (livello + 1)) - 1;
            for (int k = 0; k < indentazione; ++k) {
                std::cout << " ";
            }
            for (int j = 0; j < elementiLivello && i < nodi.getSize(); ++j, ++i) {
                auto nodo = nodi.leggilista(i);
                if (nodo.second) {
                    std::cout << nodo.first;
                } else {
                    std::cout << "X"; // Indica un nodo vuoto
                }
                // Stampa spazi tra i nodi dello stesso livello
                int spaziTraNodi = (1 << (livello + 2)) - 1;
                for (int k = 0; k < spaziTraNodi; ++k) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
            livello++;
            elementiLivello = 1 << livello; // 2^livello
        }
    }

    int getFather(int posizione) const {
        if (posizione < 0 || posizione >= nodi.getSize()) {
            throw std::out_of_range("Posizione non valida");
        }
        if (posizione == 0) {
            throw std::runtime_error("Il nodo radice non ha un padre");
        }
        int padrePos = (posizione - 1) / 2;
        if (!nodi.leggilista(padrePos).second) {
            throw std::runtime_error("Il nodo padre non esiste");
        }
        return nodi.leggilista(padrePos).first;
    }
};

#endif
