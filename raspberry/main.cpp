/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
    
    rasp.run();
    return 0;
}
