/**
 * @file main.cpp
 *
 * @brief This file contains the main(), to group the .h and .cpp files to run the
 * application.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include <thread>

#include "logger.cpp"
#include "menu.cpp"

Logger logger;
Menu menu;

int main() {
    /**
     * Configuring the serial port
     */
    logger.serialPortConfig("/dev/ttyUSB0", "serial_log.txt");

    /**
     * Creating the threads
     */
    std::thread uartThread(&Logger::serialPortRead, &logger);
    std::thread menuThread(&Menu::mainOptions, &menu);

    /**
     * Join the threads to the main thread
     */
    uartThread.join();
    menuThread.join();

    return 0;
}

