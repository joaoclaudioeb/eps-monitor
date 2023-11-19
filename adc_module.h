/**
 * @file adc_module.h
 *
 * @brief This is the header file for the abstract and derived classes for the ADC module.
 *
 * \author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * \version 0.0.0
 *
 * \date 12/11/2023
 */

#ifndef ADC_MODULE_H_
#define ADC_MODULE_H_

#include "gpio_module.h"

class VigilantCompanion;

#define ADC_PIN 28
#define ADC_INPUT 2

class ADCModule {
protected:
    int rawValue;
    static int sErrorStatus; 
public:
    /**
     * \brief .
     *
     * \param[in] .
     *
     * \return .
     */
    friend class VigilantCompanion;
    /**
     * \brief .
     *
     * \param[in] .
     *
     * \return .
     */         
    virtual void readSensor() = 0;
    /**
     * \brief .
     *
     * \param[in] .
     *
     * \return .
     */         
    virtual int evaluateValue(BusType bus) = 0;
};

class VoltageSensor : public ADCModule {
private:
    float voltageValue;
public:
    VoltageSensor();
    ~VoltageSensor();
    void readSensor();
    int evaluateValue(BusType bus);
};

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