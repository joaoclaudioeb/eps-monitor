/**
 * @file uart_module.h
 *
 * @brief This file contains the header declaring the class for the UART module.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * Universal Asynchronous Receiver/Transmitter (UART) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef UART_MODULE_H_
#define UART_MODULE_H_

#include <string>

/**
 * Forward declaration of the friend-type class
 */
class VigilantCompanion;

/**
 * Some macros for configuring the UART module
 */
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1

/**
 * @class UARTModule
 *
 * @brief A class representing the UART module.
 *
 * @details Provides functionalities for UART communication.
 */
class UARTModule {
private:
    static int sErrorStatus;

public:
    UARTModule();
    ~UARTModule();

    /**
     * @brief Declares the class VigilantCompanion as a friend.
     *
     * @details This establishes VigilantCompanion as a friend, granting access
     * to private and protected members.
     */
    friend class VigilantCompanion;
    /**
     * @brief Sends a package over UART.
     *
     * @param[in] message is the message to be sent.
     */
    void sendPackage(string message);
    /**
     * @brief Receives a package over UART.
     *
     * @return The received package as a string.
     */
    string receivePackage();
};

#endif /* UART_MODULE_H_ */
