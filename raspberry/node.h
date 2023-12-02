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
     * @brief Drives a load associated with a specific bus.
     *
     * @param[in] bus is the load to be connected to the EPS.
     *
     * @details It is used to activate a specific GPIO (17, 18 or 20, for now)
     * to connect a load to the EPS. Some type of MOSFET-based drive should be used
     * to activate these loads.
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

