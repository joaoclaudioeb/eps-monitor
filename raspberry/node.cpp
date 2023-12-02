/**
 * @file node.cpp
 *
 * @brief This file contains the source code defining the class for creating nodes.
 *
 * @details It provides the implementation of functionalities necessary for creating
 * nodes used within the queue data structure. These nodes encapsulate SystemData and
 * maintain connections to form the queue.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

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

