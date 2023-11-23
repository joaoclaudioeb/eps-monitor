#ifndef NODE_H
#define NODE_H

#include <cstring> // Adicionando o header para usar std::string

class Node {
private:
    std::string data; // Modificando para std::string
    Node* next;

public:
    Node(const std::string& data, Node* nxt);
    std::string getData() const; // Alterando o tipo de retorno para std::string
    Node* getNext() const;
    void setData(const std::string& data); // Alterando o parâmetro para std::string
    void setNext(Node* nxt);
};

#endif


