/**
 * @file gpio_module.h
 *
 * @brief This file contains the header declaring the class for the GPIO module.
 *
 * @details Contains declarations of the class and functionalities related to the 
 * General Purpose Input/Output (GPIO) module.
 *
 * @author João Cláudio Elsen Barcellos <joao.barcellos@posgrad.ufsc.br>
 * @version 0.0.0
 *
 * @date 12/11/2023
 */

#ifndef GPIO_MODULE_H_
#define GPIO_MODULE_H_

/**
 * Forward declaration of the friend-type class
 */
class VigilantCompanion;

/**
 * Some macros for the GPIO configuration
 */
#define GPIO_INIT_PINS 0x121603C0
#define GPIO_DIR_PINS 0x21603C0
#define GPIO_CONFIG_MASK 0x1FFFFFFE
#define ADC_PIN 28
#define LOAD_SEL_MASK 0x160000
#define BUS_SEL_MASK 0x3C0

/**
 * Enum for the buses to be selected
 */
enum BusType {
    BUS_5V0 = (0x00 << 6),
    BUS_3V3 = (0x01 << 6),
    ANT_DEP = (0x02 << 6),
    BEACON = (0x03 << 6),
    OBDH = (0x04 << 6),
    PAYLOAD = (0x05 << 6),
    RADIO_MAIN = (0x06 << 6),
    RADIO_BEACON = (0x07 << 6),
    NONE = BUS_5V0
};

/**
 * Enum for the loads to be connected (it is a simplification
 * as in a real application, it would be necessary at least 6 channels)
 */
enum LoadType {
    DISABLE_LOAD = (0x00 << 17),
    FIRST_LOAD = (0x01 << 17),
    SECOND_LOAD = (0x02 << 17),
    THIRD_LOAD = (0x08 << 17)
};

/**
 * @class GPIOModule
 *
 * @brief An class for the GPIO module.
 *
 * @details This class is used to control the MUXes that exist in the RE²PS, as well as to
 * enable the loads on each of the power buses.
 */
class GPIOModule {
private:   
    static int sErrorStatus; 
public:
    GPIOModule();        
    ~GPIOModule();
    
    /**
     * @brief Declares the class VigilantCompanion as a friend.
     *
     * @details This establishes VigilantCompanion as a friend, granting access
     * to private and protected members.
     */
    friend class VigilantCompanion;

    /**
     * @brief Choose a specific bus to read from.
     *
     * @param[in] bus is the bus to be read.
     *
     * @details It is used to control the MUXes, selecting a specific analog signal
     * which is going to be read and evaluated by the system.
     */          
    void chooseBus(BusType bus);
    /**
     * @brief Drives a load associated with a specific bus.
     *
     * @param[in] bus is the load to be connected to the EPS.
     *
     * @details It is used to activate a specific GPIO (17, 18 or 20, for now)
     * to connect a load to the EPS. Some type of MOSFET-based drive should be used
     * to activate these loads.
     */ 
    void driveLoad(BusType bus);
    /**
     * @brief Used for monitoring purposes.
     *
     * @details It blinks the LED connected to the GPIO25 of the Raspberry Pi Pico.
     */ 
    void heartBeat();
};

#endif /* GPIO_MODULE_H_ */
