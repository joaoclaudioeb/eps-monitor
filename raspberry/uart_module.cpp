/**
 * @file uart_module.cpp
 *
 * @brief This file contains the source code defining the class for the UART module.
 *
 * @details It implements functionalities related to the Universal Asynchronous Receiver/Transmitter
 * (UART) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "uart_module.h"

int UARTModule::sErrorStatus = 0;

UARTModule::UARTModule() {}

UARTModule::~UARTModule() {}

void UARTModule::sendPackage(string message) {
    uart_puts(UART_ID, message.c_str());
}

string UARTModule::receivePackage() {
    string message;
    bool received = false;
    
    while (!received) {
        if (uart_is_readable(UART_ID)) {
            uint8_t data = uart_getc(UART_ID);
            // Check for the exit condition (e.g., 'x')
            if (data == '\n') {
                received = true;
            }
            message += data;
        }

        // Add some delay to prevent busy waiting
        sleep_ms(100);
    }

    return message;
}
