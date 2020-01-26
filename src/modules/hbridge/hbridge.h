#ifndef _HBRIDGE_H_
#define _HBRIDGE_H_
#include "libs/HBridge/HBridge.h"
#include <Arduino.h>

HBridge bridge;

void setupBridge() 
{
    MotorPins_st myMotorA;
    MotorPins_st myMotorB;
    MotorPins_st myMotorC;

    myMotorA.enable = 32;
    myMotorA.forward = 33;
    myMotorA.reversion = 0;

    myMotorB.enable = 25;
    myMotorB.forward = 26;
    myMotorB.reversion = 0;

    myMotorC.enable = 27;
    myMotorC.forward = 14;
    myMotorC.reversion =  0;

    try 
    {
        bridge.setup(myMotorA, myMotorB, myMotorC, true);
        bridge.selfTest();
    } catch (...) {
        Serial.print("ERRRORRRRR");
    }
};

#endif // _HBRIDGE_H_