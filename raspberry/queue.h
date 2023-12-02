/**
 * @file queue.h
 *
 * @brief This file contains the header declaring the class for the queue.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * creation of queue.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

/**
 * @class Queue
 *
 * @brief A class representing a queue data structure.
 *
 * @details Manages a queue of logs represented by nodes, providing methods for insertion,
 * removal, reading, and listing logs.
 */
class Queue {
private:
    /**
     * Pointer to the first node in the queue.
     */
    Node* head; 
public:
    Queue();
    ~Queue(); 

    /**
     * @brief Inserts a log into the queue.
     *
     * @param[in] systemData is the data to be inserted as a log.
     */
    void insertLog(const SystemData& systemData);

    /**
     * @brief Reads the first log in the queue.
     *
     * @return The system data of the first log.
     */
    SystemData readFirstLog();

    /**
     * @brief Removes the first log from the queue.
     */
    void removeFirstLog();

    /**
     * @brief Lists all logs in the queue.
     */
    void listAllLogs();

    /**
     * @brief Checks if the queue is empty.
     *
     * @return The state of the queue (if it is empty or not).
     */
    bool isEmpty() const;
};

#endif /* QUEUE_H */


