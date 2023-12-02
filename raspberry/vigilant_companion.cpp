/**
 * @file vigilant_companion.cpp
 *
 * @brief This file contains the source code defining the class module's testing
 * and configuration.
 *
 * @details It implements functionalities related to the configuration and testing of the Raspberry
 * Pi Pico modules.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "vigilant_companion.h"

int VigilantCompanion::setupAndVerifyGPIOModule(GPIOModule& gpio){
    gpio_init_mask(GPIO_INIT_PINS);
    gpio_set_dir_masked(GPIO_CONFIG_MASK, GPIO_DIR_PINS);
    gpio_pull_down(ADC_PIN);

    for(int i = 0; i < 8; i++) {
        gpio.chooseBus((BusType)(i << 6));
        sleep_ms(1);
        if((int)((gpio_get_all() >> 6) & 0x0F) != i) {
            gpio.sErrorStatus++;
        }
        sleep_ms(300);
    }

    if(gpio.sErrorStatus != 0){
      gpio.sErrorStatus = 1;}
    else{
        gpio.sErrorStatus = 0;
    }
    return gpio.sErrorStatus; 
}

int VigilantCompanion::setupAndVerifyADCModule(ADCModule* adc) {
    float auxValue = 0;
    
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_INPUT);

    adc->readSensor();
    
    auxValue = ((adc->rawValue - BUS_1V65) / BUS_1V65) * 100.0;

    if((auxValue * ((auxValue > 0) - (auxValue < 0))) > 5 ){
        adc->sErrorStatus = 1;
    }
    else{
        adc->sErrorStatus = 0;
    }

    return adc->sErrorStatus;
}

int VigilantCompanion::setupAndVerifyUARTModule(UARTModule& uart) {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart.sendPackage("echo \r\n");
    
    if(uart.receivePackage()=="echo"){
        uart.sErrorStatus = 1;
    }
    else{
        uart.sErrorStatus = 0;
    }

    return uart.sErrorStatus;
}
