#ifndef _HBRIDGE_STRUCTS_H
#define _HBRIDGE_STRUCTS_H

#include <Arduino.h>

struct MotorPins_st 
{
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

#endif // _HBRIDGE_STRUCTS_H