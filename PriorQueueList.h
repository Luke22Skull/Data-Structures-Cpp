#ifndef PRIORQUEUELIST_H
#define PRIORQUEUELIST_H

#include <iostream>
#include "PTRList.h"

using namespace std;

template <typename T>
class PriorCodaLista {
private:
    PTRList<T> lista;

public:
    PriorCodaLista() {} // creaPriorCoda

    ~PriorCodaLista() {
        while (!lista.listavuota()) {
            deleteMin();
        }
    }

    void inserisci(T elemento) { // inserisci
        if (lista.listavuota()) {
            lista.inslista(elemento, lista.primolista());
            return;
        }
        else {
            auto* posizione = lista.primolista();
            if (elemento <= lista.leggilista(lista.primolista())) {
                auto* newHead = lista.buildNode(elemento);
                lista.setNext(newHead, lista.primolista());
                lista.setHead(newHead);
                return;
            }
            else {
                while (!lista.finelista(posizione) && elemento >= lista.leggilista(lista.succlista(posizione))) {
                    posizione = posizione->next; 
                    cout << "pos: " << posizione->data << endl;
                }
                lista.inslista(elemento, posizione);
            }
        }
    }

    T min() const { // min
        if (lista.listavuota()) throw logic_error("Coda vuota");
        return lista.leggilista(lista.primolista());
    }

    void deleteMin() { // deleteMin
        if (lista.listavuota()) throw logic_error("Coda vuota");
        lista.canclista(lista.primolista());
    }

    void stampaLista() const { // Debug: stampa la lista
        lista.stampaLista();
    }
};

#endif
