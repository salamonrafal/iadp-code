#ifndef _HBRIDGE_H_
#define _HBRIDGE_H_
#include "libs/HBridge/HBridge.h"

HBridge bridge; 
MotorPins_st myMotorA;
MotorPins_st myMotorB;
MotorPins_st myMotorC;

void setupBridge() {
    myMotorA.enable = 34;
    myMotorA.forward = 35;
    myMotorA.reversion = 25;

    myMotorB.enable = 26;
    myMotorB.forward = 27;
    myMotorB.reversion = 1;

    myMotorC.enable = 3;
    myMotorC.forward = 17;
    myMotorC.reversion = 16;

    bridge.setup(myMotorA, myMotorB, myMotorC);
};

#endif // _HBRIDGE_H_