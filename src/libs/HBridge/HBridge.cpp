/******************************************************************
 * H-bridge motor DC 12V Enable/Disbale Forward/Revision 3 motors
 * 
 * Item: https://aliexpress.com/item/738657859.html
 ******************************************************************/
#include "libs/HBridge/HBridge.h"

void HBridge::setup(MotorPins_st motorAPins, MotorPins_st motorBPins, MotorPins_st motorCPins)
{
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_A, motorAPins);
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_B, motorBPins);
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_C, motorCPins);
}

void HBridge::setPin(MOTOR_TYPE_t motorType, MotorPins_st pins)
{
    switch (motorType)
    {
        case MOTOR_TYPE_t::MOTOR_A:
            HBridge::motorPins.motorA = pins;
            break;
        case MOTOR_TYPE_t::MOTOR_B:
            HBridge::motorPins.motorB = pins;
            break;
        case MOTOR_TYPE_t::MOTOR_C:
            HBridge::motorPins.motorC = pins;
            break;
    }
}