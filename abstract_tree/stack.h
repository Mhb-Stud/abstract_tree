#ifndef STACK_H
#define STACK_H
#include "double_linked_list.h"

template<typename Type>
class Stack {
private:

    DoubleLinkedList<Type> storage;

public:

    Stack() {
    }
    void push(Type const& val) {
        storage.pushFront(val);

    }
    void pop() {
        storage.popFront();

    }
    Type top() {
        return storage.front();

    }
    bool isEmpty() {
        return storage.empty();

    }
    int size() {
        return storage.size();

    }

};



#endif

