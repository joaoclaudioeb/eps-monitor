/**
 * @file logger.h
 *
 * @brief Header file defining the class for the GPIO module.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * General Purpose Input/Output (GPIO) module.
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
 * @brief
 *
 * @details
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
     * @brief 
     *
     * @param[in] 
     *
     * @details 
     */          
    int serialPortConfig(const char* tty_channel, const char* log_file_name);
    /**
     * @brief 
     *
     * @param[in] 
     *
     * @details 
     */          
    void serialPortRead();
    /**
     * @brief 
     *
     * @param[in] 
     *
     * @details 
     */          
    void updateLogFile(int* count);
};

#endif /* LOGGER_H_ */
