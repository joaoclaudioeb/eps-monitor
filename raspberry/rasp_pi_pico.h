/**
 * @file raspberry_pi_pico.h
 *
 * @brief This file contains the header declaring the class for the Raspberry Pi Pico system.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * operation of the Raspberry-based monitoring system.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef RASPBERRY_PI_PICO_H
#define RASPBERRY_PI_PICO_H

#include "adc_module.cpp"
#include "gpio_module.cpp"
#include "vigilant_companion.cpp"
#include "node.cpp"
#include "queue.cpp"
#include "clock_calendar.cpp"
#include "uart_module.cpp"

/**
 * A macro to Raspberry Pi Pico's ID.
 */
#define ID_RASP "69" 

/**
 * Enum for defining different states for the Raspberry Pi Pico system.
 */
enum State {
    SETUP_AND_TESTING_STATE, 
    READ_5V0_BUS_STATE, 
    READ_3V3_BUS_STATE, 
    END_STATE 
};

/**
 * @class RaspberryPiPico
 *
 * @brief A class representing the Raspberry Pi Pico system.
 *
 * @details Manages the functionalities and components of the Raspberry Pi Pico system,
 * including ADC, GPIO, UART, testing, logging, timestamp, and system states.
 */
class RaspberryPiPico {
private:
    State currentState; // Current state of the Raspberry Pi Pico system
    SystemData log; // System log data 
    
    ADCModule* adc; // Pointer to ADC module
    GPIOModule gpio; // GPIO module 
    UARTModule uart; // UART module 
    VigilantCompanion test; // Vigilant Companion module 
    Queue logQueue; // Queue for logging data
    ClockCalendar time; // Clock and calendar module 

public:
    RaspberryPiPico(); 
    ~RaspberryPiPico(); 

    /**
     * @brief Sends the system log.
     *
     * @details It starts the communication with the PC and sends all the last 10 stored information
     */
    void sendLog();

    /**
     * @brief Creates a log entry.
     *
     * @param[in] log is the log data to be created.
     */
    void createLog(SystemData log);

    /**
     * @brief Initializes the Raspberry Pi Pico system.
     *
     * @details It uses the VigilantCompanion object to configure the modules, as well as tes
     * each of them
     */
    void initialize(); 

    /**
     * @brief Runs the Raspberry Pi Pico system.
     *
     * @details It runs the system's state-machine
     */
    void run(); 
};

#endif /* RASPBERRY_PI_PICO_H */

