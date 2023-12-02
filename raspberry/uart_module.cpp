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

void UARTModule::sendPackage(const char* message) {
    uart_puts(UART_ID, message);
}

string UARTModule::receivePackage() {
    string message;

    while (1){
        char c = uart_getc(UART_ID);
        if (c == '\n') {
            break;
        }
        message += c;
    }

    return message;
}
