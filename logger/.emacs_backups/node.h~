#ifndef NODE_H
#define NODE_H

#include "systemdata.h"

class Node {
private:
    SystemData data;
    Node* next;

public:
    Node(const SystemData& systemData, Node* nxt);
    SystemData getData() const;
    Node* getNext() const;
    void setData(const SystemData& systemData);
    void setNext(Node* nxt);
};

#endif

