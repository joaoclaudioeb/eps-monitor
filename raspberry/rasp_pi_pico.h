#ifndef RASPBERRY_PI_PICO_H
#define RASPBERRY_PI_PICO_H

#include "adc_module.cpp"
#include "gpio_module.cpp"
#include "vigilant_companion.cpp"
#include "node.cpp"
#include "queue.cpp"
#include "clock_calendar.cpp"
#include "uart_module.cpp"

#define ID_RASP "69"

enum State {
    SETUP_AND_TESTING_STATE,
    READ_5V0_BUS_STATE,
    READ_3V3_BUS_STATE,
    END_STATE
};

class RaspberryPiPico {
private:
    State currentState;
    SystemData log;
    
    ADCModule* adc;
    GPIOModule gpio;
    UARTModule uart;
    VigilantCompanion test;
    Queue logQueue;
    ClockCalendar time;

public:
    RaspberryPiPico();
    ~RaspberryPiPico();

    void sendLog();
    void createLog(SystemData log);
    void initialize(); // Configurações iniciais
    void run(); // Máquina de estados
};

#endif