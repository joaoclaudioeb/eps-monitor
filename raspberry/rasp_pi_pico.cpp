/**
 * @file rasp_pi_pico.cpp
 *
 * @brief This file contains the source code defining the class for the Raspberry Pi Pico system.
 *
 * @details It implements functionalities related to the Raspberry Pi Pico system operation.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#include "rasp_pi_pico.h"

RaspberryPiPico::RaspberryPiPico(){}
RaspberryPiPico::~RaspberryPiPico(){}


void RaspberryPiPico::initialize(){
    int auxErr = 0;
    int err = 1;
    
    /**
     * Starts the tests regarding the GPIO modules
     */
    createLog({+time, "Verificando integridade do módulo de GPIO.", ID_RASP});
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyGPIOModule(gpio)){
            createLog({+time, "....Módulo de GPIO está funcionando corretamente.", ID_RASP});
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de GPIO não está funcionando corretamente, saindo...", ID_RASP});
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de GPIO não está funcionando corretamente, tentando novamente.", ID_RASP});
    }
    
    /**
     * Starts the tests regarding the voltage sensor
     */
    adc = new VoltageSensor();
    createLog({+time, "Verificando integridade do módulo de ADC para a leitura de tensão.", ID_RASP});
    err = 1;
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyADCModule(adc)){
            createLog({+time, "....Módulo de ADC está funcionando corretamente.", ID_RASP});
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, saindo...", ID_RASP});
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, tentando novamente.", ID_RASP});
    }
    delete adc;

    /**
     * Starts the tests regarding the current sensor
     */
    adc = new CurrentSensor();
    createLog({+time, "Verificando integridade do módulo de ADC para a leitura de corrente.", ID_RASP});
    err = 1;
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyADCModule(adc)){
            createLog({+time, "....Módulo de ADC está funcionando corretamente.", ID_RASP});
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, saindo...", ID_RASP});
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, tentando novamente.", ID_RASP});
    }
    delete adc;

    /**
     * Starts the tests regarding the UART module
     */
    createLog({+time, "Verificando integridade do módulo de UART.", ID_RASP});
    err = 1;
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyUARTModule(uart)){
            createLog({+time, "....Módulo de UART está funcionando corretamente.", ID_RASP});
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de UART não está funcionando corretamente, saindo...", ID_RASP});
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de UART não está funcionando corretamente, tentando novamente.", ID_RASP});
    }
    
    /**
     * It defines if the initialization ended without errors
     */
    if(auxErr != 0){
        createLog({+time, "Ocorreram erros no programa, saindo.", ID_RASP});
        currentState = END_STATE;
    }
    else{
        createLog({+time, "Todos os módulos estão operacionais.", ID_RASP});
        currentState = READ_5V0_BUS_STATE;
    }
    sendLog();
}

void RaspberryPiPico::createLog(SystemData log){
    time.advance();
    logQueue.insertLog(log);
}

void RaspberryPiPico::sendLog(){
    while (!logQueue.isEmpty()) {
        SystemData log = logQueue.readFirstLog();
        string message = "ID" + log.ID + ":" + log.date + ": " + log.message + "\r\n";
        uart.sendPackage(message);
        logQueue.removeFirstLog();
    }
}

/**
 * With this method the system's state-machine is, in fact, run.
 * 
 * @TODO This method could have been implemented differently, in a leaner way.
 * This would be for future updates.
 */
void RaspberryPiPico::run(){
    int auxExit = 0;
    
    currentState = SETUP_AND_TESTING_STATE;
    
    while(1){
        switch(currentState){
        case SETUP_AND_TESTING_STATE:
            /**
              * This is the state in which the system is initialized and each module
              * is tested.
              */
            initialize();
            break;
        case READ_5V0_BUS_STATE:
            /**
              * This is the state in which the 5V0 bus is monitored and evaluated. 
              */
            adc = new VoltageSensor();            

            createLog({+time, "Inicializando leituras no barramento de 5V.", ID_RASP});
            gpio.chooseBus(BUS_5V0);
            createLog({+time, "Habilitando a carga do barramento PAYLOAD.", ID_RASP});
            gpio.driveLoad(PAYLOAD);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando a carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(PAYLOAD);
                if(adc->evaluateValue(PAYLOAD)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_5V0);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", ID_RASP});
                sendLog();
            }

            createLog({+time, "Habilitando a carga do barramento RADIO_MAIN.", ID_RASP});
            gpio.driveLoad(RADIO_MAIN);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(RADIO_MAIN);
                if(adc->evaluateValue(RADIO_MAIN)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_5V0);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", ID_RASP});
                sendLog();
            }
                 
            createLog({+time, "Habilitando a carga do barramento RADIO_BEACON.", ID_RASP});
            gpio.driveLoad(RADIO_BEACON);
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(RADIO_BEACON);
                if(adc->evaluateValue(RADIO_BEACON)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_5V0);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e trocando de barramento.", ID_RASP});
                sendLog();
            }           

            delete adc;
            currentState = READ_3V3_BUS_STATE;

            break;
        case READ_3V3_BUS_STATE:
            /**
              * This is the state in which the 3V3 bus is monitored and evaluated. 
              */
            adc = new VoltageSensor();            
            createLog({+time, "Inicializando leituras no barramento de 3V3.", ID_RASP});
            gpio.chooseBus(BUS_3V3);
            createLog({+time, "Habilitando a carga do barramento ANT_DEP.", ID_RASP});
            gpio.driveLoad(ANT_DEP);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando a carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(ANT_DEP);
                if(adc->evaluateValue(ANT_DEP)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_3V3);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", ID_RASP});
                sendLog();
            }

            createLog({+time, "Habilitando a carga do barramento BEACON.", ID_RASP});
            gpio.driveLoad(BEACON);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(BEACON);
                if(adc->evaluateValue(BEACON)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_3V3);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", ID_RASP});
                sendLog();
            }

            createLog({+time, "Habilitando a carga do barramento OBDH.", ID_RASP});
            gpio.driveLoad(OBDH);

            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new CurrentSensor();
                }
                                    
                gpio.chooseBus(OBDH);
                if(adc->evaluateValue(OBDH)){
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", ID_RASP});
                    gpio.driveLoad(NONE);
                    currentState = END_STATE;
                    auxExit = 1;
                }
                else{
                    delete adc;
                    adc = new VoltageSensor();
                    gpio.chooseBus(BUS_3V3);
                }
            }
            if(auxExit != 0){
                sendLog();
                break;
            }
            else{
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e trocando de barramento.", ID_RASP});
                sendLog();
            }
            
            delete adc;
            currentState = READ_5V0_BUS_STATE;
                      
            break;
        case END_STATE:
            /**
              * This is the state where the system stop its operation, if something wrong is detected.
              *
              * @TODO It's not the most interesting way to act on a mistake. Perhaps it would be interesting
              * to have a routine to see if it's possible to correct the problem or something similar
              */
            createLog({+time, "Fim do programa por problemas nos barramentos..", ID_RASP});
            sendLog();
            while(1);
            break;
        default:
            break;
        }
        gpio.heartBeat();
        sleep_ms(1000);
    }
}
