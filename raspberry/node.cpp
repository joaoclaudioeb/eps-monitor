#include "node.h"

Node::Node(const SystemData& systemData, Node* nxt) : data(systemData), next(nxt) {}

SystemData Node::getData() const {
    return data;
}

Node* Node::getNext() const {
    return next;
}

void Node::setData(const SystemData& systemData) {
    data = systemData;
}

void Node::setNext(Node* nxt) {
    next = nxt;
}

