#include "node.h"

Node::Node(const std::string& data, Node* nxt) : data(data), next(nxt) {}

std::string Node::getData() const {
    return data;
}

Node* Node::getNext() const {
    return next;
}

void Node::setData(const std::string& data) {
    this->data = data;
}

void Node::setNext(Node* nxt) {
    next = nxt;
}

