#ifndef PTRLIST_H
#define PTRLIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PTRList {
private:
    struct Nodo {
        T data;
        Nodo* next;
        Nodo(T value, Nodo* n = nullptr) : data(value), next(n) {}
    };

    Nodo* head;

    bool itHasNext (Nodo* posizione) {return posizione->next;};

public:
    PTRList() : head(nullptr) {}
    ~PTRList() {
        while (!listavuota())
            canclista(primolista());
    }

    bool listavuota() const {
        return head == nullptr;
    }

    Nodo* buildNode(T value) {return new Nodo(value, nullptr);};
    void setNext (Nodo* from, Nodo* to) {(from && to) ? from->next = to : throw invalid_argument("setH: Nodo non valido");};
    void setHead (Nodo* newHead) {newHead ? head = newHead : throw invalid_argument("setH: Nodo non valido");};

    T leggilista(Nodo* posizione) const {
        if (!posizione) {
            throw out_of_range("leggi: Posizione non valida");
        }
        return posizione->data;
    }

    void scrivilista(T elemento, Nodo* posizione) {
        if (!posizione) {
            throw out_of_range("scrivi: Posizione non valida");
        }
        posizione->data = elemento;
    }

    Nodo* primolista() const {
        return head;
    }

    bool finelista(Nodo* posizione) const {
        return posizione->next == nullptr;
    }

    Nodo* succlista(Nodo* posizione) const {
        if (!posizione) {
            throw out_of_range("succ: Posizione non valida");
        }
        return posizione->next;
    }

    Nodo* predlista(Nodo* posizione) const {
        if (posizione == head || !head) {
            return nullptr;
            // throw out_of_range("Posizione non valida");
        }
        Nodo* temp = head;
        while (temp->next != posizione) {
            temp = temp->next;
        }
        return temp;
    }

    void inslista(T elemento, Nodo* posizione) {
        if (posizione == nullptr) { // Inserimento in testa
            head = new Nodo(elemento, head);
        } else { // Inserimento dopo posizione
            /* Nodo* tmp = posizione->next;
            Nodo* nuovo = new Nodo(elemento, posizione->next);
            nuovo->next = tmp;
            */
            if (itHasNext(posizione)) {
                Nodo* tmp = posizione->next;
                Nodo* newNode = new Nodo(elemento, nullptr);
                posizione->next = newNode;
                newNode->next = tmp;
            }
            else
                posizione->next = new Nodo (elemento, nullptr);
        }
    }

    void canclista(Nodo* posizione) {
        if (posizione == head) { // Cancella in testa
            Nodo* temp = head;
            head = head->next;
            delete temp;
        } else { // Cancella dopo un nodo
            Nodo* prev = predlista(posizione);
            prev->next = posizione->next;
            delete posizione;
        }
    }

    void stampaLista() const {
        Nodo* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
#endif
