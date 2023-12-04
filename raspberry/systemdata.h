/**
 * @file systemdata.h
 *
 * @brief This file contains the structure of the system data.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include <string>

/**
 * @struct SystemData
 *
 * @brief Represents the system data information.
 *
 * @details Contains fields for date, message, and ID.
 */
struct SystemData {
    string date; // The event's date and time
    string message; // The message to stored in a log
    string ID; // ID of the dispositive
};

#endif /* SYSTEMDATA_H */


