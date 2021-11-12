/*****************************************
* Shahrood User ID:  -
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include <algorithm>
#include "exception.h"

template <typename Type>
class DoubleLinkedList {
public:
    class DoubleNode {
    public:
        DoubleNode(Type const& = Type(), DoubleNode* = nullptr, DoubleNode* = nullptr);

        Type value() const;
        DoubleNode* previous() const;
        DoubleNode* next() const;
        void setNext(DoubleNode* const&);
        void setPrevious(DoubleNode* const&);
    private:
        Type nodeValue;
        DoubleNode* previousNode;
        DoubleNode* nextNode;
    };

    DoubleLinkedList<Type>();
    DoubleLinkedList<Type>(DoubleLinkedList const&);
    ~DoubleLinkedList<Type>();

    DoubleNode* listHead;
    DoubleNode* listTail;
    // Accessors

    int size() const;
    bool empty() const;

    Type front() const;
    Type back() const;

    DoubleNode* begin() const;
    DoubleNode* end() const;

    DoubleNode* find(Type const&) const;
    int count(Type const&) const;

    // Mutators

    void swap(DoubleLinkedList&);
    Type getValueAt(int const&);

    void pushFront(Type const&);
    void pushBack(Type const&);

    void popFront();
    void popBack();

    int erase(Type const&);
    void setHead(DoubleNode* const&);
    void setTail(DoubleNode* const&);

private:
    int listSize;

    // List any additional private member functions you author here
    // Friends

};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
// initilizes linkedlist
DoubleLinkedList<Type>::DoubleLinkedList() :
    // Updated the initialization list here
    listHead(nullptr),
    listTail(nullptr),
    listSize(0)
{ }
template <typename Type>
// initilizes linkList using an existing linkedList expands the old linkedList
DoubleLinkedList<Type>::DoubleLinkedList(DoubleLinkedList const& list) :
    // Updated the initialization list here
    listHead(nullptr),
    listTail(nullptr),
    listSize(0)

{

    DoubleNode* temp = list.begin();
    while (temp != nullptr) {
        pushFront(temp->value());
        temp = temp->next();
    }
}

//by iterating the nodes dealocates node memories one by one
template <typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList() {
    if (listHead != nullptr) {
        DoubleNode* firstElement = listHead;
        DoubleNode* secondElement = firstElement->next();
        while (firstElement != nullptr) {
            delete firstElement;
            if (secondElement == nullptr) {
                delete secondElement;
                break;
            }
            firstElement = secondElement;
            secondElement = firstElement->next();
        }
    }

}

// returns the size of the list by iterating all the nodes
template <typename Type>
int DoubleLinkedList<Type>::size() const {
    DoubleNode* temp = listHead;
    int counter = 0;
    while (temp != nullptr) {
        temp = temp->next();
        counter++;
    }
    return counter;

}

// checks wheather the list is emty or not by checking the head pointer
template <typename Type>
bool DoubleLinkedList<Type>::empty() const {
    if (!listHead) return true;
    return false;
}

//returnes the value of the list's front node and throws underflow exption if the list is empty
template <typename Type>
Type DoubleLinkedList<Type>::front() const {
    // Enter your implementation here
    if (listHead != nullptr)return listHead->value();
    else throw Underflow();
    //exeption handeling
    return 0; // This returns the default value
}

//returnes the value of the list's last node and throws underflow exption if the list is empty
template <typename Type>
Type DoubleLinkedList<Type>::back() const {
    // Enter your implementation here
    if (listTail != nullptr)return listTail->value();
    else throw Underflow();
    //exeption handeling
    return 0; // This returns the default value
}

// just an accessor
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::begin() const {
    return listHead;
}

//just an accessor
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::end() const {
    return listTail;
}

// returnes the address of the found node value
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::find(Type const& value) const {
    // Enter your implementation here
    DoubleNode* temp = listHead;
    while (temp != nullptr) {
        if (temp->value() == value)return temp;
        temp = temp->next();
    }

    return nullptr;
}

// counts the number of identical elements
template <typename Type>
int DoubleLinkedList<Type>::count(Type const& value) const {
    DoubleNode* temp = listHead;
    int counter = 0;
    while (temp != nullptr) {
        if (temp->value() == value)counter++;
        temp = temp->next();
    }

    return counter;
}

// by giving the address of first and last node to head and tail it swaps the lists
template <typename Type>
void DoubleLinkedList<Type>::swap(DoubleLinkedList& list) {
    // Enter your implementation here
    DoubleNode* temph = list.listHead;
    DoubleNode* tempt = list.listTail;
    list.listHead = listHead;
    list.listTail = listTail;
    listTail = tempt;
    listHead = temph;
    int temp = list.listSize;
    list.listSize = listSize;
    listSize = temp;

}

template<typename Type>
Type DoubleLinkedList<Type>::getValueAt(int const& index)
{
    if (listHead != nullptr && index < size()) {
        DoubleNode* temp = listHead;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next();
        }
        return temp->value();
    
    }
    return Type();
}

//first checks wheather the list is empty or not then it adds a new element to the list
template <typename Type>
void DoubleLinkedList<Type>::pushFront(Type const& value) {
    // Enter your implementation here
    if (empty()) {
        listHead = new DoubleNode(value, nullptr, nullptr);
        listTail = listHead;
    }
    else {
        DoubleNode* temp = listHead;
        listHead = new DoubleNode(value, nullptr, listHead);
        temp->setPrevious(listHead);
    }

}

// same thing as above but this time it adds it to the back
template <typename Type>
void DoubleLinkedList<Type>::pushBack(Type const& value) {
    // Enter your implementation here
    if (empty()) {
        listTail = new DoubleNode(value, nullptr, nullptr);
        listHead = listTail;
    }
    else {
        DoubleNode* temp = listTail;
        listTail = new DoubleNode(value, temp, nullptr);
        temp->setNext(listTail);
    }
}

// removes the first element in the list throws exption if the list is empty
template <typename Type>
void DoubleLinkedList<Type>::popFront() {
    // Enter your implementation here
    if (listHead != nullptr) {
        if (listHead->next() != nullptr) {
            listHead->next()->setPrevious(nullptr);
            listHead = listHead->next();
        }
        else listHead = listTail = nullptr;
    }
    else throw Underflow();

}

// removes the last element in the list and throws exption if the list is empty
template <typename Type>
void DoubleLinkedList<Type>::popBack() {
    // Enter your implementation here

    if (listTail != nullptr) {
        if (listTail->previous() != nullptr) {
            listTail->previous()->setNext(nullptr);
            listTail = listTail->previous();
        }
        else listHead = listTail = nullptr;
    }
    else throw Underflow();
}

// erases a node by deleting its address from next and previous nodes
template <typename Type>
int DoubleLinkedList<Type>::erase(Type const& value) {
    // Enter your implementation here
    DoubleNode* temp = listHead;
    int counter = 0;
    while (temp != nullptr) {
        if (temp->value() == value) {
            if (temp != listHead && temp->next() != nullptr && size() != 1) {
                DoubleNode* firstAdress = temp->next();
                DoubleNode* SecondAdress = temp->previous();
                temp->previous()->setNext(firstAdress);
                temp->next()->setPrevious(SecondAdress);
            }
            else if (temp == listHead && size() != 1) {
                listHead = listHead->next();
                listHead->setPrevious(nullptr);
            }
            else if (temp->next() == nullptr && size() != 1) {
                listTail = temp->previous();
                temp->previous()->setNext(nullptr);
            }
            else if (size() == 1) {
                listHead = listTail = nullptr;
            }
            counter++;
        }
        temp = temp->next();
    }
    return counter;
}

// initializes the double node
template <typename Type>
DoubleLinkedList<Type>::DoubleNode::DoubleNode(
    Type const& nv,
    DoubleLinkedList::DoubleNode* pn,
    DoubleLinkedList::DoubleNode* nn) :
    // Updated the initialization list here
    nodeValue(nv), // This assigns 'nodeValue' the default value
    previousNode(pn),
    nextNode(nn)
{
    // Enter your implementation here

}

//returnes the node value this is never used because of the fields beeing public :)
template <typename Type>
Type DoubleLinkedList<Type>::DoubleNode::value() const {
    // Enter your implementation here
    return nodeValue;
    // This returns the default value
}

// same thing here :)
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::DoubleNode::previous() const {

    return previousNode;
}

//same :)
template <typename Type>
typename DoubleLinkedList<Type>::DoubleNode* DoubleLinkedList<Type>::DoubleNode::next() const {

    return nextNode;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////


template <typename Type>
void DoubleLinkedList<Type>::DoubleNode::setNext(DoubleNode* const& next) {

    nextNode = next;

};
template <typename Type>
void DoubleLinkedList<Type>::DoubleNode::setPrevious(DoubleNode* const& prev) {

    previousNode = prev;

};
template <typename Type>
void DoubleLinkedList<Type>::setHead(DoubleNode* const& Head) {
    listHead = Head;
}
template <typename Type>
void DoubleLinkedList<Type>::setTail(DoubleNode* const& Tail) {
    listTail = Tail;
}


#endif
