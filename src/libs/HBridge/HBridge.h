/******************************************************************
 * H-bridge motor DC 12V Enable/Disbale Forward/Revision 3 motors
 * 
 * Item: https://aliexpress.com/item/738657859.html
 ******************************************************************/
#ifndef _HBRIDGE_H_LIBS_
#define _HBRIDGE_H_LIBS_

#include <Arduino.h>

struct MotorPins_st {
    uint8_t enable;
    uint8_t forward;
    uint8_t reversion;
};

struct MotorsPins_st 
{
    struct MotorPins_st motorA;
    struct MotorPins_st motorB;
    struct MotorPins_st motorC;
};


typedef enum {
    MOTOR_A = 0,
    MOTOR_B = 1,
    MOTOR_C = 2
}
MOTOR_TYPE_t;

class HBridge
{
    public:
        /**
         * @brief Setup H-bridge
         * 
         * @param motorAPins Pins for motor A
         * @param motorBPins Pins for motor B
         * @param motorCPins Pins for motor C
         */
        void setup(MotorPins_st motorAPins, MotorPins_st motorBPins, MotorPins_st motorCPins);

    protected:
        MotorsPins_st motorPins;

        /**
         * @brief set pins for specific motor type
         * 
         * @param motorType type of motor (enum)
         * @param pins pins
         */
        void setPin (MOTOR_TYPE_t motorType, MotorPins_st pins);

    private:

};

#endif // _HBRIDGE_H_LIBS_