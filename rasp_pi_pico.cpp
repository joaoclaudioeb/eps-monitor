#include "rasp_pi_pico.h"

RaspberryPiPico::RaspberryPiPico(){}
RaspberryPiPico::~RaspberryPiPico(){}


void RaspberryPiPico::initialize(){
    int auxErr = 0;
    int err = 1;
    
    createLog({+time, "Verificando integridade do módulo de GPIO.", 69 });
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyGPIOModule(gpio)){
            createLog({+time, "....Módulo de GPIO está funcionando corretamente.", 69 });
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de GPIO não está funcionando corretamente, saindo...", 69 });
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de GPIO não está funcionando corretamente, tentando novamente.", 69 });
    }

    adc = new VoltageSensor();
    createLog({+time, "Verificando integridade do módulo de ADC para a leitura de tensão.", 69 });
    err = 1;
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyADCModule(adc)){
            createLog({+time, "....Módulo de ADC está funcionando corretamente.", 69 });
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, saindo...", 69 });
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, tentando novamente.", 69 });
    }
    delete adc;

    adc = new CurrentSensor();
    createLog({+time, "Verificando integridade do módulo de ADC para a leitura de corrente.", 69 });
    err = 1;
    for(int i = 0; (i < 3) && err; i++){
        if(!test.setupAndVerifyADCModule(adc)){
            createLog({+time, "....Módulo de ADC está funcionando corretamente.", 69 });
            err = 0;
        }
        else if(i == 2){
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, saindo...", 69 });
            auxErr += 1;
        }
        else
            createLog({+time, "....Módulo de ADC não está funcionando corretamente, tentando novamente.", 69 });
    }
    delete adc;

    if(auxErr != 0){
        createLog({+time, "Ocorreram erros no programa, saindo.", 69 });
        currentState = END_STATE;
    }
    else{
        createLog({+time, "Todos os módulos estão operacionais.", 69 });
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
        cout << "ID" << log.ID << ":" << log.date << ": " << log.message << endl;
        logQueue.removeFirstLog();
    }
}

void RaspberryPiPico::run(){
    int auxExit = 0;
    
    currentState = SETUP_AND_TESTING_STATE;
    
    while(1){
        switch(currentState){
        case SETUP_AND_TESTING_STATE:
            /**
              * Este é o estado onde a inicialzação dos módulos é feita, bem como alguns
              * testes são conduzidos, para ver a integridade deles.
              */
            initialize();
            break;
        case READ_5V0_BUS_STATE:
            /**
              * Este é o estado onde a inicialzação das leituras do barramento de 5V é feita.
              * 
              */
            adc = new VoltageSensor();            

            createLog({+time, "Inicializando leituras no barramento de 5V.", 69 });
            gpio.chooseBus(BUS_5V0);
            createLog({+time, "Habilitando a carga do barramento PAYLOAD.", 69 });
            gpio.driveLoad(PAYLOAD);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando a carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", 69 });
                sendLog();
            }

            


            createLog({+time, "Habilitando a carga do barramento RADIO_MAIN.", 69 });
            gpio.driveLoad(RADIO_MAIN);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", 69 });
                sendLog();
            }
            
            

            
            createLog({+time, "Habilitando a carga do barramento RADIO_BEACON.", 69 });
            gpio.driveLoad(RADIO_BEACON);
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_5V0)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e trocando de barramento.", 69 });
                sendLog();
            }           

            delete adc;
            currentState = READ_3V3_BUS_STATE;

            break;
        case READ_3V3_BUS_STATE:
            /**
              * Este é o estado onde a inicialzação das leituras do barramento de 3V3 é feita.
              * 
              */
            adc = new VoltageSensor();            
            createLog({+time, "Inicializando leituras no barramento de 3V3.", 69 });
            gpio.chooseBus(BUS_3V3);
            createLog({+time, "Habilitando a carga do barramento ANT_DEP.", 69 });
            gpio.driveLoad(ANT_DEP);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando a carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", 69 });
                sendLog();
            }




            createLog({+time, "Habilitando a carga do barramento BEACON.", 69 });
            gpio.driveLoad(BEACON);
            
            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e acionando a próxima.", 69 });
                sendLog();
            }




            createLog({+time, "Habilitando a carga do barramento OBDH.", 69 });
            gpio.driveLoad(OBDH);

            for(int i = 0; (i < 5000) && !auxExit; i++){
                if(adc->evaluateValue(BUS_3V3)){
                    createLog({+time, "....Leitura de tensão está fora do esperado, desabilitando carga e saindo.", 69 });
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
                    createLog({+time, "....Leitura de corrente está fora do esperado, desabilitando carga e saindo.", 69 });
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
                createLog({+time, "....Leituras dentro do esperado, desabilitando carga e trocando de barramento.", 69 });
                sendLog();
            }
            
            delete adc;
            currentState = READ_5V0_BUS_STATE;
                      
            break;
        case END_STATE:
            /**
              * Este é o estado onde o programa para, caso ocorram erros que possam danificar o Raspberry Pi Pico
              * ou pior, o RE²PS.
              * 
              */
            createLog({+time, "Fim do programa por problemas nos barramentos..", 69 });
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
