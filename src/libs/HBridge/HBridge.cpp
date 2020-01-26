/******************************************************************
 * H-bridge motor DC 12V Enable/Disbale Forward/Revision 3 motors
 * 
 * Item: https://aliexpress.com/item/738657859.html
 ******************************************************************/
#include "libs/HBridge/HBridge.h"
#include <stdexcept>

void HBridge::setup(MotorPins_st motorAPins, MotorPins_st motorBPins, MotorPins_st motorCPins, bool debug)
{
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_A, motorAPins);
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_B, motorBPins);
    HBridge::setPin(MOTOR_TYPE_t::MOTOR_C, motorCPins);
    HBridge::debug = debug;
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

void HBridge::setPinsMode()
{
    HBridge::setPinMode(MOTOR_TYPE_t::MOTOR_A);
    HBridge::setPinMode(MOTOR_TYPE_t::MOTOR_B);
    HBridge::setPinMode(MOTOR_TYPE_t::MOTOR_C);
}

void HBridge::setPinMode(MOTOR_TYPE_t motorType)
{
    uint8_t men = HBridge::getPin(motorType, PIN_TYPE_t::ENABLE);
    uint8_t mfw = HBridge::getPin(motorType, PIN_TYPE_t::FORWARD);
    uint8_t mrv = HBridge::getPin(motorType, PIN_TYPE_t::REVERSION);


    if (HBridge::debug) {
        Serial.println("------ setPinsMode --------");
        Serial.print("Motor: ");
        Serial.println(motorType);

        Serial.print("enable: ");
        Serial.println(men);

        Serial.print("forward: ");
        Serial.println(mfw);

        Serial.print("reversion: ");
        Serial.println(mrv);
        Serial.println("------ setPinsMode -- END. ---");
    }

    pinMode(men, OUTPUT);
    pinMode(mfw, OUTPUT);

    if (mrv != 0)
        pinMode(mrv, OUTPUT);

}

MotorPins_st HBridge::getPins(MOTOR_TYPE_t motorType) 
{
    switch (motorType)
    {
        case MOTOR_TYPE_t::MOTOR_A:
            return HBridge::motorPins.motorA;
            break;

        case MOTOR_TYPE_t::MOTOR_B:
            return HBridge::motorPins.motorB;
            break;

        case MOTOR_TYPE_t::MOTOR_C:
            return HBridge::motorPins.motorC;
            break;

        default:
            throw std::runtime_error("WRONG MOTOR TYPE");
    }
}

uint8_t HBridge::getPin(MOTOR_TYPE_t motorType, PIN_TYPE_t pinType) 
{
    MotorPins_st tmpPins = HBridge::getPins(motorType);
    
    switch (pinType)
    {
        case PIN_TYPE_t::ENABLE:
            return tmpPins.enable;

        case PIN_TYPE_t::FORWARD :
            return tmpPins.forward;

        case PIN_TYPE_t::REVERSION :
            return tmpPins.reversion;

        default:
            throw std::runtime_error("WRONG PIN TYPE");
    }
}

void HBridge::controlMotor(MOTOR_TYPE_t motorType, MOTOR_DIRECTION_t direction, bool enable)
{
    uint8_t enablePin = HBridge::getPin(motorType, PIN_TYPE_t::ENABLE);
    uint8_t directionPin = HBridge::getPin(motorType, HBridge::tranformDirectionToPinType(direction));

    HBridge::setPinMode(motorType);

    if (enable == true) 
    {
        if (HBridge::debug) 
        {
            Serial.println("------- controlMotor ENABLE ---------");
        }
        digitalWrite(enablePin, HIGH);
        delay(1000);
        digitalWrite(directionPin, HIGH);
    } else {

        if (HBridge::debug) 
        {
            Serial.println("------- controlMotor DISABLE ---------");
        }
        digitalWrite(enablePin, LOW);
        delay(1000);
        digitalWrite(directionPin, LOW);
    }

    if (HBridge::debug) 
    {
        Serial.print("Motor Type: ");
        Serial.println(motorType);

        Serial.print("Motor direction: ");
        Serial.println(direction);

        Serial.print("enablePin: ");
        Serial.println(enablePin);

        Serial.print("directionPin: ");
        Serial.println(directionPin);

        Serial.print("enable: ");
        Serial.println(enable);

        Serial.println("------ controlMotor ENABLE -- END. ---");
    }
}

void HBridge::selfTest()
{
    controlMotor(MOTOR_TYPE_t::MOTOR_A, MOTOR_DIRECTION_t::FORWARD, true);
    delay(1000);


    controlMotor(MOTOR_TYPE_t::MOTOR_B, MOTOR_DIRECTION_t::FORWARD, true);
    delay(1000);
    

    controlMotor(MOTOR_TYPE_t::MOTOR_C, MOTOR_DIRECTION_t::FORWARD, true);
    delay(1000);

    controlMotor(MOTOR_TYPE_t::MOTOR_A, MOTOR_DIRECTION_t::FORWARD, false);
    delay(200);
    controlMotor(MOTOR_TYPE_t::MOTOR_B, MOTOR_DIRECTION_t::FORWARD, false);
    delay(200);
    controlMotor(MOTOR_TYPE_t::MOTOR_C, MOTOR_DIRECTION_t::FORWARD, false);
    delay(200);
}