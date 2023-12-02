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
    /**
     * Now it is officially empty
     */
     head = nullptr; 
}

void Queue::insertLog(const SystemData& systemData) {
    Node* p = head;
    Node* q = head;

    if (head == nullptr)
        head = new Node(systemData, head);
    else {
        while (q != nullptr) {
            p = q;
            q = p->getNext();
        }
        p->setNext(new Node(systemData, nullptr));
    }
}

SystemData Queue::readFirstLog() {
    if (head != nullptr)
        return head->getData();
    else
        /**
         * Returning an empty SystemData when the queue is empty
         */
         return SystemData(); 
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
    while (aux != nullptr) {
        std::cout << "ID: " << aux->getData().ID << " Date: " << aux->getData().date
                  << " Message: " << aux->getData().message << std::endl;
        aux = aux->getNext();
    }
}

bool Queue::isEmpty() const {
    return (head == nullptr);
}

