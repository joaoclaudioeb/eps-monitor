/**
 * @file queue.cpp
 *
 * @brief This file contains the source code defining the class for the queue.
 *
 * @details It implements functionalities related to the queue creation.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "queue.h"
#include <iostream>

Queue::Queue() : head(nullptr) {}

Queue::~Queue() {
    Node* cursor = head;
    while (head) {
        cursor = cursor->getNext();
        delete head;
        head = cursor;
    }
    head = nullptr; 
}

void Queue::insertLog(const string& data) { 
    Node* p = head;
    Node* q = head;

    if (head == nullptr)
        head = new Node(data, head); 
    else {
        while (q != nullptr) {
            p = q;
            q = p->getNext();
        }
        p->setNext(new Node(data, nullptr)); 
    }
}

string Queue::readFirstLog() { 
    if (head != nullptr)
        return head->getData();
    else
        return string(); 
}

void Queue::removeFirstLog() {
    if (head != nullptr) {
        Node* oldHead = head;
        head = head->getNext();
        delete oldHead;
    }
}

void Queue::listAllLogs() {
    Node* aux = head;
    cout << "Leitura: ";
    while (aux != nullptr) {
        cout << aux->getData() << "\n"; 
        aux = aux->getNext();
    }
}

bool Queue::isEmpty() const {
    return (head == nullptr);
}

