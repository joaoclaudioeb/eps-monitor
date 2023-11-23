#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

class Queue {
private:
    Node* head;

public:
    Queue();
    ~Queue();
    void insertLog(const std::string& data); // Atualizando o parâmetro para std::string
    std::string readFirstLog(); // Alterando o tipo de retorno para std::string
    void removeFirstLog();
    void listAllLogs();
    bool isEmpty() const;
};

#endif

