/**
 * @file node.h
 *
 * @brief This file contains the header declaring the class for creating nodes.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * creation of nodes.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef NODE_H
#define NODE_H

#include "systemdata.h"

/**
 * @class Node
 *
 * @brief A class for the nodes.
 *
 * @details This class is used to control the node's creation, also to access the node's information.
 */
class Node {
private:
    SystemData data;
    Node* next;

public:
    Node(const SystemData& systemData, Node* nxt);

    /**
     * @brief Gets the data stored in the node.
     *
     * @return The system data stored.
     */
    SystemData getData() const;
    /**
     * @brief Gets the pointer to the next node.
     *
     * @return A pointer to the next node.
     */
    Node* getNext() const;
    /**
     * @brief Sets the system data for the node.
     *
     * @param[in] data is the structured data to be set in the node.
     */ 
    void setData(const SystemData& systemData);
    /**
     * @brief Sets the pointer to the next node.
     *
     * @param[in] nxt is a pointer to the next node.
     */
    void setNext(Node* nxt);
};

#endif /* NODE_H_ */

