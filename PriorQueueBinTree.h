#ifndef PRIORQUEUEBINTREE_H
#define PRIORQUEUEBINTREE_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PriorCodaAlbero {
private:

    struct Nodo {
        T data;
        Nodo* left;
        Nodo* right;

        Nodo(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Nodo* root; // Radice del Min-Heap

    // Funzione ausiliaria per inserire un elemento rispettando la struttura del Min-Heap
    void inserisciHeap(Nodo*& nodo, T elemento) {
        if (!nodo) {
            nodo = new Nodo(elemento);
            return;
        }
        if (elemento < nodo->data) {
            swap(nodo->data, elemento); // swap scambia 2 elementi
        }
        if (!nodo->left) {
            inserisciHeap(nodo->left, elemento);
        } else if (!nodo->right) {
            inserisciHeap(nodo->right, elemento);
        } else {
            // Inserimento nel sottoalbero con meno nodi
            if (altezza(nodo->left) <= altezza(nodo->right)) {
                inserisciHeap(nodo->left, elemento);
            } else {
                inserisciHeap(nodo->right, elemento);
            }
        }
    }

    // Funzione ausiliaria per trovare l'elemento minimo
    T trovaMin(Nodo* nodo) const {
        if (!nodo) throw logic_error("Coda vuota");
        return nodo->data;
    }

    // Funzione ausiliaria per trovare il nodo padre
    Nodo* trovaPadre(Nodo* nodo, Nodo* target) const {
        if (!nodo || nodo == target) return nullptr;
        if (nodo->left == target || nodo->right == target) return nodo;
        Nodo* leftResult = trovaPadre(nodo->left, target);
        if (leftResult) return leftResult;
        return trovaPadre(nodo->right, target);
    }

    // Funzione ausiliaria per eliminare l'elemento minimo
    void deleteMinHeap(Nodo*& nodo) {
        if (!nodo) return;

        if (!nodo->left && !nodo->right) {
            // nodo = nullptr;
            Nodo** travelerPTR; 
            Nodo* padre = trovaPadre(root, nodo);
            travelerPTR = &padre;

            (*travelerPTR)->left = nullptr;
            (*travelerPTR)->right = nullptr;

            delete nodo;
            nodo = nullptr;
            return;
        }

        Nodo* minChild = nullptr;

        if (nodo->left && nodo->right) {
            minChild = (nodo->left->data < nodo->right->data) ? nodo->left : nodo->right;
        } else {
            minChild = nodo->left ? nodo->left : nodo->right;
        }

        swap(nodo->data, minChild->data);
        deleteMinHeap(minChild);
    }

    // Funzione per calcolare l'altezza di un nodo
    int altezza(Nodo* nodo) const {
        if (!nodo) return 0;
        return 1 + max(altezza(nodo->left), altezza(nodo->right));
    }

    // Funzione per stampare l'albero (per scopi di debug)
    void stampaAlbero(Nodo* nodo, int depth = 0) const {
        if (!nodo) return;
        if (nodo->right)
            stampaAlbero(nodo->right, depth + 1);
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << nodo->data << endl;
        if (nodo->left)
            stampaAlbero(nodo->left, depth + 1);
    }

    // Funzione per deallocare l'albero
    void deleteSubBinTree(Nodo* nodo) {
        if (!nodo) return;
        deleteSubBinTree(nodo->left);
        deleteSubBinTree(nodo->right);
        delete nodo;
    }

public:
    PriorCodaAlbero() : root(nullptr) {} // creaPriorCoda

    ~PriorCodaAlbero() {
        deleteSubBinTree(root);
    }

    void inserisci(T elemento) { // inserisci
        inserisciHeap(root, elemento);
    }

    T min() const { // min
        return trovaMin(root);
    }

    void deleteMin() { // deleteMin
        deleteMinHeap(root);
    }

    void stampa() const { // Stampa l'albero per scopi di debug
        stampaAlbero(root);
    }
};

#endif
