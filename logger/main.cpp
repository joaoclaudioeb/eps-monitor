#include <thread>

#include "logger.cpp"
#include "menu.cpp"

Logger logger;
Menu menu;

int main() {
    
    logger.serialPortConfig("/dev/ttyUSB0", "serial_log.txt");
   
    std::thread uartThread(&Logger::serialPortRead, &logger);
    std::thread menuThread(&Menu::mainOptions, &menu);

    // Join the threads to the main thread
    uartThread.join();
    menuThread.join();

    return 0;
}

