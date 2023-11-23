/**
 * @file gpio_module.cpp
 *
 * @brief This file contains the source code defining the class for the GPIO module.
 *
 * @details It implements functionalities related to the General Purpose Input/Output (GPIO) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "gpio_module.h"

int GPIOModule::sErrorStatus = 0;

GPIOModule::GPIOModule() {}

GPIOModule::~GPIOModule() {}

void GPIOModule::chooseBus(BusType bus) {
    switch(bus){
    case BUS_5V0:
        gpio_put_masked(BUS_SEL_MASK, BUS_5V0);
        break;    
    case BUS_3V3:
        gpio_put_masked(BUS_SEL_MASK, BUS_3V3);
        break;
    case ANT_DEP:
        gpio_put_masked(BUS_SEL_MASK, ANT_DEP);
        break;
    case BEACON:
        gpio_put_masked(BUS_SEL_MASK, BEACON);
        break;
    case OBDH:
        gpio_put_masked(BUS_SEL_MASK, OBDH);
        break;
    case PAYLOAD:
        gpio_put_masked(BUS_SEL_MASK, PAYLOAD);
        break;
    case RADIO_MAIN:
        gpio_put_masked(BUS_SEL_MASK, RADIO_MAIN);
        break;
    case RADIO_BEACON:
        gpio_put_masked(BUS_SEL_MASK, RADIO_BEACON);
        break;
    default:
        break;
    }
}

void GPIOModule::driveLoad(BusType bus) {
    switch(bus){
    case NONE:
        gpio_put_masked(LOAD_SEL_MASK, DISABLE_LOAD);
        break;
    case ANT_DEP:
        gpio_put_masked(LOAD_SEL_MASK, FIRST_LOAD);
        break;
    case BEACON:
        gpio_put_masked(LOAD_SEL_MASK, SECOND_LOAD);
        break;
    case OBDH:
        gpio_put_masked(LOAD_SEL_MASK, THIRD_LOAD);
        break;
    case PAYLOAD:
        gpio_put_masked(LOAD_SEL_MASK, FIRST_LOAD);
        break;
    case RADIO_MAIN:
        gpio_put_masked(LOAD_SEL_MASK, SECOND_LOAD);
        break;
    case RADIO_BEACON:
        gpio_put_masked(LOAD_SEL_MASK, THIRD_LOAD);
        break;
    default:
        gpio_put_masked(LOAD_SEL_MASK, DISABLE_LOAD);
        break;
    }
}

void GPIOModule::heartBeat(){
    gpio_put(PICO_DEFAULT_LED_PIN, !gpio_get(PICO_DEFAULT_LED_PIN));
} 
