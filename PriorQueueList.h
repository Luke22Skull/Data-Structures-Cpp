#ifndef PRIORQUEUELIST_H
#define PRIORQUEUELIST_H
#include <iostream>
#include "PTRList.h"
using namespace std;

template <typename T>
class PriorQueueList {
private:
    PTRList<T> list;
public:
    PriorQueueList() {} // createPriorQueue
    ~PriorQueueList() {
        while (!list.isEmptyList()) {
            deleteMin();
        }
    }

    void insert(T element) { // insert
        if (list.isEmptyList()) {
            list.insertList(element, list.firstList());
            return;
        } else {
            auto* position = list.firstList();
            if (element <= list.readList(list.firstList())) {
                auto* newHead = list.buildNode(element);
                list.setNext(newHead, list.firstList());
                list.setHead(newHead);
                return;
            } else {
                while (!list.endList(position) && element >= list.readList(list.nextList(position))) {
                    position = position->next;
                    cout << "pos: " << position->data << endl;
                }
                list.insertList(element, position);
            }
        }
    }

    T min() const { // min
        if (list.isEmptyList()) throw logic_error("Queue is empty");
        return list.readList(list.firstList());
    }

    void deleteMin() { // deleteMin
        if (list.isEmptyList()) throw logic_error("Queue is empty");
        list.deleteList(list.firstList());
    }

    void printList() const { // Debug: print the list
        list.printList();
    }
};

#endif
