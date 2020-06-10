#ifndef _HBRIDGE_H_
#define _HBRIDGE_H_
#include <HBridge.h>
#include <Arduino.h>

HBridge bridge;

MotorPins_st setupPinsMotor (uint8_t enable, uint8_t forward, uint8_t reversion)
{
    MotorPins_st myMotor;

    myMotor.enable = enable;
    myMotor.forward = forward;
    myMotor.reversion = reversion;

    return myMotor;
}

void setupBridge() 
{
    try 
    {
        bridge.setup(
            setupPinsMotor(32, 33, 25), 
            setupPinsMotor(26, 27, 14), 
            setupPinsMotor(1, 3, 17), 
            true
        );
        bridge.selfTest();
    } catch (...) {
        Serial.print("ERRRORRRRR");
    }
};
#endif // _HBRIDGE_H_