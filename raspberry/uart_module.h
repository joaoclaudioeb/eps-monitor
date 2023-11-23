/**
 * @file uart_module.h
 *
 * @brief This is the header file for the class for the UART module.
 *
 * \author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * \version 0.0.0
 *
 * \date 12/11/2023
 */

#ifndef UART_MODULE_H_
#define UART_MODULE_H_

#include <string>

class VigilantCompanion;

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

class UARTModule {
private:
    static int sErrorStatus;

public:
    UARTModule();
    ~UARTModule();

        /**
     * \brief .
     *
     * \param[in] .
     *
     * \return .
     */
    friend class VigilantCompanion;
    void sendPackage(const char* message);
    string receivePackage();
};

#endif /* UART_MODULE_H_ */
