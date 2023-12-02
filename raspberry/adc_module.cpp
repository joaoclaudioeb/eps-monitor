/**
 * @file adc_module.cpp
 *
 * @brief This file contains the source code defining abstract and derived classes 
 * for the ADC module.
 *
 * @details It implements functionalities related to the ADC (Analog-to-Digital Converter) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "adc_module.h"

int ADCModule::sErrorStatus = 0;

VoltageSensor::VoltageSensor() {}

VoltageSensor::~VoltageSensor() {}

/**
 * This method conducts raw measurements and handles conversions 
 * specific to the LMV321RIYLT. 
 * 
 * @TODO Currently, it performs a voltage divider conversion 
 * for testing purposes only. Actual conversion logic is pending.
 */
void VoltageSensor::readSensor() {
    rawValue = adc_read();
    voltageValue = (rawValue / 4095.0) * 3.3;
}

/**
 * This method assesses the current measurements against expected values.
 * 
 * @TODO Currently, it compares the measurements obtained from a voltage divider 
 * for testing purposes. The implementation for actual comparison logic is pending.
 */
int VoltageSensor::evaluateValue(BusType bus){
    int err = 0;
    float auxValue = 0;
    
    readSensor();
    
    switch(bus){
    case BUS_5V0:
        auxValue = ((voltageValue - 1.65) / 1.65) * 100.0;
        break;
    case BUS_3V3:
        auxValue = ((voltageValue - 1.65) / 1.65) * 100.0;
        break;
    default:
        break;
    }
    
    if((auxValue * ((auxValue > 0) - (auxValue < 0))) > 5 ){
        err = 1;
    }
    else{
        err = 0;
    }
    
    return err;
}

CurrentSensor::CurrentSensor() {}

CurrentSensor::~CurrentSensor() {}

/**
 * This method conducts raw measurements and handles conversions 
 * specific to the INA199CxDCKR. 
 * 
 * @TODO Currently, it performs a voltage divider conversion 
 * for testing purposes only. Actual conversion logic is pending.
 */
void CurrentSensor::readSensor() {
    rawValue = adc_read();
    currentValue = (rawValue / 4095.0) * 3.3; 
}

/**
 * This method assesses the current measurements against expected values.
 * 
 * @TODO Currently, it compares the measurements obtained from a voltage divider 
 * for testing purposes. The implementation for actual comparison logic is pending.
 */
int CurrentSensor::evaluateValue(BusType bus){
    int err = 0;
    float auxValue = 0;
    
    readSensor();
    
    switch(bus){
    case ANT_DEP:
        auxValue = ((currentValue - 1.65) / 1.65) * 100.0;
        break;
    case BEACON:
        auxValue = ((currentValue - 1.65) / 1.65) * 100.0;
        break;
    case OBDH:
        auxValue = ((currentValue - 2.65) / 1.65) * 100.0;
        break;
    case PAYLOAD:
        auxValue = ((currentValue - 1.65) / 1.65) * 100.0;
        break;
    case RADIO_MAIN:
        auxValue = ((currentValue - 1.65) / 1.65) * 100.0;
        break;
    case RADIO_BEACON:
        auxValue = ((currentValue - 1.65) / 1.65) * 100.0;
        break;
    default:
        break;
    }

    if((auxValue * ((auxValue > 0) - (auxValue < 0))) > 5 ){
        err = 1;
    }
    else{
        err = 0;
    }
    
    return err;
}
