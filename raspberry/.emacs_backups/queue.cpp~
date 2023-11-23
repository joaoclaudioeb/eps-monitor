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
    head = nullptr; // Officially empty
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
        return SystemData(); // Returning an empty SystemData when the queue is empty
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

