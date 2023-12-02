/**
 * @file vigilant_companion.h
 *
 * @brief This file contains the header declaring the class for the module's testing and configuration.
 *
 * @details Contains declarations of the class and functionalities related class for the module's
 * testing and configuration
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef VIGILANT_COMPANION_H_
#define VIGILANT_COMPANION_H_

#include "adc_module.h"
#include "gpio_module.h"
#include "uart_module.h"

/**
 * A macro for the 1V65 reference voltage
 */
#define BUS_1V65 2048

class GPIOModule; // Forward declaration of the GPIOModule class
class ADCModule; // Forward declaration of the ADCModule class
class UARTModule; //Forward declaration of the UARTModule class

/**
 * @class VigilantCompanion
 *
 * @brief A class responsible for verifying and setting up modules.
 *
 * @details Provides methods to set up and verify GPIO, UART, and ADC modules.
 */
class VigilantCompanion{
public:
    /**
     * @brief Sets up and verifies the GPIO module.
     *
     * @param[in] gpio is the reference to the GPIO module object.
     * @return An integer indicating the success status of the setup.
     */
    int setupAndVerifyGPIOModule(GPIOModule& gpio);
    /**
     * @brief Sets up and verifies the UART module.
     *
     * @param uart is the reference to the UART module object.
     * @return An integer indicating the success status of the setup.
     */
    int setupAndVerifyUARTModule(UARTModule& uart);
    /**
     * @brief Sets up and verifies the ADC module.
     *
     * @param adc is the pointer to the ADC module object.
     * @return An integer indicating the success status of the setup.
     */
    int setupAndVerifyADCModule(ADCModule* adc);
};

#endif /* VIGILANT_COMPANION_H_ */
