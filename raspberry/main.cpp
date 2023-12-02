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

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/timer.h"

using namespace std;

#include "rasp_pi_pico.cpp"

RaspberryPiPico rasp;

int main() {
    stdio_init_all();
    sleep_ms(2000);
    /**
     * Will be here forever
     */
    rasp.run();
    /**
     * Should never reach it
     */
    return 0;
}
