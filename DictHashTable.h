#ifndef DICTHASHTABLE_H
#define DICTHASHTABLE_H
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Hash functions for string keys
unsigned int hashFunctionString(const string& key, int size) {
    unsigned int hash = 0;
    for (char c : key) {
        hash = (hash * 31) + c;
    }
    return hash % size;
}

// Hash function for integer keys (multiplication-based)
unsigned int hashingInt1(int key, int size) {
    const double A = 0.6180339887; // Golden ratio constant
    return int(size * (key * A - int(key * A))) % size;
}

// Hash function for integer keys (XOR with shift)
unsigned int hashingInt2(int key, int size) {
    key ^= (key << 13);
    key ^= (key >> 17);
    key ^= (key << 5);
    return key % size;
}

template <class T>
class Dictionary {
private:
    struct DictNode { // Node structure for the dictionary
        string key;
        T value;
        DictNode* next; // Pointer to the next node in the bucket list
        DictNode(string k, T v) : key(k), value(v), next(nullptr) {}
    };
    DictNode** table; // Array of pointers to linked lists (buckets)
    int size; // Number of buckets

    // Get hash value for string keys
    unsigned int getHash(const string& key) const {
        return hashFunctionString(key, size);
    }

    // Get hash value for integer keys
    unsigned int getHash(int key, int hashType = 1) const {
        if (hashType == 1)
            return hashingInt1(key, size);
        else
            return hashingInt2(key, size);
    }

public:
    Dictionary(int size = 10) : size(size) {
        table = new DictNode*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~Dictionary() {
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

    // Check if the dictionary is empty
    bool isEmpty() {
        for (int i = 0; i < size; ++i)
            if (!table[i]) return true;
        return false;
    }

    // Insert element with string key
    void insert(const pair<string, T>& element) {
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

    // Insert element with integer key
    void insert(const pair<int, T>& element, int hashType = 1) {
        int index = getHash(element.first, hashType);
        string keyStr = to_string(element.first); // Convert integer key to string
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

    // Check if a string key exists
    bool belongs(const string& key) const {
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

    // Check if an integer key exists
    bool belongs(const int key) const {
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

    // Delete element with string key
    void deleteKey(const string& key) {
        int index = getHash(key);
        DictNode* temp = table[index];
        DictNode* prev = nullptr;
        while (temp != nullptr) { // Traverse the bucket list
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

    // Delete element with integer key
    void deleteKey(const int key) {
        int index = getHash(key);
        DictNode* temp = table[index];
        DictNode* prev = nullptr;
        while (temp != nullptr) { // Traverse the bucket list
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

    // Retrieve value with string key
    T retrieve(const string& key) const {
        int index = getHash(key);
        DictNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        throw runtime_error("Key not found");
    }

    // Retrieve value with integer key
    T retrieve(const int key) const {
        int index = getHash(key);
        DictNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == to_string(key)) {
                return temp->value;
            }
            temp = temp->next;
        }
        throw runtime_error("Key not found");
    }

    // Print the dictionary
    void printDict() const {
        for (int i = 0; i < size; ++i) {
            if (table[i] != nullptr) {
                cout << "Bucket " << i << ":\n";
                DictNode* temp = table[i];
                while (temp != nullptr) {
                    cout << " Key: " << temp->key << " - Value: " << temp->value << endl;
                    temp = temp->next;
                }
            }
        }
    }
};

#endif
