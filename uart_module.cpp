/**
 * @file uart_module.cpp
 *
 * @brief This is the implementation file for class for the UART module.
 *
 * \author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * \version 0.0.0
 *
 * \date 12/11/2023
 */

#include "uart_module.h"

UARTModule::UARTModule() {}

UARTModule::~UARTModule() {}

void UARTModule::sendPackage(string message) {
    uart_puts(UART_ID, message.c_str());
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
