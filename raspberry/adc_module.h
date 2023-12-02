/**
 * @file adc_module.h
 *
 * @brief This file contains the header declaring abstract and derived classes 
 * for the ADC module.
 *
 * @details Contains declarations of classes and functionalities related to the 
 * Analog-to-Digital Converter (ADC) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef ADC_MODULE_H_
#define ADC_MODULE_H_

#include "gpio_module.h"

/**
 * Some macros for the ADC configuration
 */
#define ADC_PIN 28
#define ADC_INPUT 2

/**
 * Forward declaration of the friend-type class
 */
class VigilantCompanion;

/**
 * @class ADCModule
 *
 * @brief An abstract base class that defines the interface for derived classes.
 *
 * @details This class serves as an interface for different sensors, shuch as
 * INA199CxDCKR and LMV321RIYLT. It declares methods that must be implemented by
 * derived sensor classes.
 */
class ADCModule {
protected:
    int rawValue;
    static int sErrorStatus; // Static variable to be shared among instances
public:
    /**
     * @brief Declares the class VigilantCompanion as a friend.
     *
     * @details This establishes VigilantCompanion as a friend, granting access
     * to private and protected members.
     */
    friend class VigilantCompanion;
    
    /**
     * @brief Pure virtual function to read sensor values.
     *
     * @details This function must be implemented by derived classes
     * to read the sensor's raw value and further convert to Volts or Amps.
     */         
    virtual void readSensor() = 0;
    /**
     * @brief Pure virtual function to evaluate sensor values.
     *
     * @param[in] bus is the bus for which to evaluate the sensor value.
     * @return The status/error code.
     *
     * @details This function must be implemented by derived classes
     * to evaluate the measurements in a givend bus.
     */         
    virtual int evaluateValue(BusType bus) = 0;
};

/**
 * @class VoltageSensor
 *
 * @brief A class derived from ADCModule to represent a voltage sensor (LMV321RIYLT).
 *
 * @details This class implements the VoltageSensor, inheriting from ADCModule.
 * It provides specific implementations for reading and evaluating voltage sensor measurements.
 */
class VoltageSensor : public ADCModule {
private:
    float voltageValue;
public:
    VoltageSensor();
    ~VoltageSensor();
    void readSensor();
    int evaluateValue(BusType bus);
};

/**
 * @class CurrentSensor
 *
 * @brief A class derived from ADCModule to represent a current sensor (INA199CxDCKR).
 *
 * @details This class implements the CurrentSensor, inheriting from ADCModule.
 * It provides specific implementations for reading and evaluating current sensor measurements.
 */
class CurrentSensor : public ADCModule {
private:
    float currentValue;
public:
    CurrentSensor();
    ~CurrentSensor();
    void readSensor();
    int evaluateValue(BusType bus);
};

#endif /* ADC_MODULE_H_ */
