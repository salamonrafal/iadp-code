#ifndef _HBRIDGE_H_
#define _HBRIDGE_H_
#include <HBridge.h>
#include <Arduino.h>

HBridge bridge;

void setupBridge() 
{
    MotorPins_st myMotorA;
    MotorPins_st myMotorB;
    MotorPins_st myMotorC;

    myMotorA.enable = 32;
    myMotorA.forward = 33;
    myMotorA.reversion = 25;

    myMotorB.enable = 26;
    myMotorB.forward = 27;
    myMotorB.reversion = 14;

    myMotorC.enable = 12;
    myMotorC.forward = 13;
    myMotorC.reversion =  1;

    try 
    {
        bridge.setup(myMotorA, myMotorB, myMotorC, true);
        bridge.selfTest();
    } catch (...) {
        Serial.print("ERRRORRRRR");
    }
};

#endif // _HBRIDGE_H_