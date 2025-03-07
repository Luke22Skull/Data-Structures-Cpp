#ifndef DICTHASHTABLE_H
#define DICTHASHTABLE_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Funzioni di hashing per chiavi stringa
unsigned int hashFunctionString(const string& key, int size) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = (hash * 31) + c;
    }
    return hash % size;
}

// Funzione di hashing per chiavi intere (basata sulla moltiplicazione)
unsigned int hashingInt1(int key, int size) {
    const double A = 0.6180339887; // Costante della sezione aurea
    return int(size * (key * A - int(key * A))) % size;
}

// Funzione di hashing per chiavi intere (XOR con shift)
unsigned int hashingInt2(int key, int size) {
    key ^= (key << 13);
    key ^= (key >> 17);
    key ^= (key << 5);
    return key % size;
}

template <class T>
class Dizionario {
private:
    struct DictNode {
        string key;
        T value;
        DictNode* next; // Tiene traccia della lista di bucket

        DictNode(string k, T v) : key(k), value(v), next(nullptr) {}
    };

    DictNode** table; // Array di puntatori a liste concatenate
    int size;        // Numero di bucket

    unsigned int getHash(const string& key) const {
        return hashFunctionString(key, size);
    }

    unsigned int getHash(int key, int hashType = 1) const {
        if (hashType == 1)
            return hashingInt1(key, size);
        else
            return hashingInt2(key, size);
    }

public:
    Dizionario(int size = 10) : size(size) {
        table = new DictNode*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~Dizionario() {
        for (int i = 0; i < size; ++i) {
            DictNode* temp = table[i];
            while (temp != nullptr) {
                DictNode* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    bool isEmpty() {
        for (int i = 0; i < size; ++i)
            if (!table[i]) return true;
        return false;
    }

    // Inserimento con chiave stringa
    void inserisci(const pair<string, T>& element) {
        int index = getHash(element.first);
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == element.first) {
                temp->value = element.second;
                return;
            }
            temp = temp->next;
        }

        DictNode* newNode = new DictNode(element.first, element.second);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Inserimento con chiave intera
    void inserisci(const pair <int, T>& element, int hashType = 1) {
        int index = getHash(element.first, hashType);
        string keyStr = to_string(element.first); // Converti la chiave in stringa
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == keyStr) {
                temp->value = element.second;
                return;
            }
            temp = temp->next;
        }

        DictNode* newNode = new DictNode(keyStr, element.second);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Funzioni appartiene
    bool appartiene(const string& key) const {
        int index = getHash(key);
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool appartiene(const int key) const {
        int index = getHash(key);
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == to_string(key)) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Funzioni cancella
    void cancella(const string& key) {
        int index = getHash(key);
        DictNode* temp = table[index];
        DictNode* prev = nullptr;

        while (temp != nullptr) {   // while di scorrimento nel bucket
            if (temp->key == key) {
                if (prev == nullptr) {
                    table[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void cancella(const int key) {
        int index = getHash(key);
        DictNode* temp = table[index];
        DictNode* prev = nullptr;

        while (temp != nullptr) {   // while di scorrimento nel bucket
            if (temp->key == to_string(key)) {
                if (prev == nullptr) {
                    table[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    // Funzioni recupera
    T recupera(const string& key) const {
        int index = getHash(key);
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        throw runtime_error("Chiave non trovata");
    }

    T recupera(const int key) const {
        int index = getHash(key);
        DictNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == to_string(key)) {
                return temp->value;
            }
            temp = temp->next;
        }
        throw runtime_error("Chiave non trovata");
    }

    void printDict() const {
        for (int i = 0; i < size; ++i) {
            if (table[i] != nullptr) {
                cout << "Bucket " << i << ":\n";
                DictNode* temp = table[i];
                while (temp != nullptr) {
                    cout << "  Key: " << temp->key << " - Value: " << temp->value << endl;
                    temp = temp->next;
                }
            }
        }
    }
};

#endif
