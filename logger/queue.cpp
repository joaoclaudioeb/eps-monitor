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

void Queue::insertLog(const std::string& data) { // Atualizando o parâmetro para std::string
    Node* p = head;
    Node* q = head;

    if (head == nullptr)
        head = new Node(data, head); // Alterando para inserir a string no novo nó
    else {
        while (q != nullptr) {
            p = q;
            q = p->getNext();
        }
        p->setNext(new Node(data, nullptr)); // Alterando para inserir a string no novo nó
    }
}

std::string Queue::readFirstLog() { // Alterando o tipo de retorno para std::string
    if (head != nullptr)
        return head->getData();
    else
        return std::string(); // Retornando uma string vazia quando a fila está vazia
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
    std::cout << "Leitura: ";
    while (aux != nullptr) {
        std::cout << aux->getData() << std::endl; // Alterando para imprimir a string diretamente
        aux = aux->getNext();
    }
}

bool Queue::isEmpty() const {
    return (head == nullptr);
}
