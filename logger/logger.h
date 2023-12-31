/**
 * @file logger.h
 *
 * @brief This file contains the header declaring the class for message reception and storage.
 *
 * @details Contains declarations of the class and functionalities related to the reception of
 * logs generated by the Raspberry Pi Pico, as well as the storage of these logs.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>

#include "node.cpp"
#include "queue.cpp"

using namespace std;

/**
 * @class Logger
 *
 * @brief Handles logging operations for serial port data.
 *
 * @details Manages logging of data received from a serial port, buffering it
 * and updating a log file accordingly.
 */
class Logger {
private:
    Queue logQueue;
    int tty, log, len, index = 0;
    char buffer[2048], newChar;
    struct termios options;
public:
    Logger();        
    ~Logger();
  
    /**
     * @brief Configures the serial port for logging.
     *
     * @param[in] tty_channel is the serial port channel.
     * @param[in] log_file_name is the name of the log file.
     * @return The status of the serial port configuration.
     *
     * @details Configures the serial port based on provided parameters.
     */          
    int serialPortConfig(const char* tty_channel, const char* log_file_name);
    /**
     * @brief Reads data from the serial port.
     *
     * @details Reads incoming data from the serial port and buffers it.
     */            
    void serialPortRead();
    /**
     * @brief Updates the log file with buffered data.
     *
     * @param[in,out] count is the count of logged entries.
     *
     * @details Writes buffered log data to the log file.
     */           
    void updateLogFile(int* count);
};

#endif /* LOGGER_H_ */
