/******************************************************************
 * H-bridge motor DC 12V Enable/Disbale Forward/Revision 3 motors
 * 
 * Item: https://aliexpress.com/item/738657859.html
 ******************************************************************/
#ifndef _HBRIDGE_H_LIBS_
#define _HBRIDGE_H_LIBS_

#include <Arduino.h>
#include "enums.h"
#include "structs.h"

class HBridge
{
    public:
        typedef enum {
            FORWARD,
            REVERSION
        }
        MOTOR_DIRECTION_t;

        typedef enum {
            MOTOR_A,
            MOTOR_B,
            MOTOR_C
        }
        MOTOR_TYPE_t;

        /**
         * @brief Setup H-bridge
         * 
         * @param motorAPins Pins for motor A
         * @param motorBPins Pins for motor B
         * @param motorCPins Pins for motor C
         * @param debug  enable debug mode
         */
        void setup(MotorPins_st motorAPins, MotorPins_st motorBPins, MotorPins_st motorCPins, bool debug = false);

        /**
         * @brief Enable motor for specific direction
         * 
         * @param motorType type of motor (enum)
         * @param direction wich direction should be run
         */
        void run(MOTOR_TYPE_t motorType, MOTOR_DIRECTION_t direction);

        /**
         * @brief Enable motor for specific direction and time (in seconds)
         * 
         * @param motorType type of motor (enum)
         * @param direction wich direction should be run
         * @param time how long motor should be run
         */
        void run(MOTOR_TYPE_t motorType, MOTOR_DIRECTION_t direction, int time);

        /**
         * @brief Disable motor
         * 
         * @param motorType type of motor (enum)
         */
        void stop(MOTOR_TYPE_t motorType);

        /**
         * @brief test correct working
         */
        void selfTest();

    protected:
        MotorsPins_st motorPins;

        /**
         * @brief set pins for specific motor type
         * 
         * @param motorType type of motor (enum)
         * @param pins pins
         */
        void setPin (MOTOR_TYPE_t motorType, MotorPins_st pins);

        /**
         * @brief Set for all pins mode output 
         */
        void setPinsMode();

        /**
         * @brief Set pin mode for specific motor type
         * 
         * @param motorType type of motor (enum)
         */
        void setPinMode(MOTOR_TYPE_t motorType);

        /**
         * @brief Control specific motor enable and direction
         * 
         * @param motorType type of motor (enum)
         * @param direction wich direction should be run
         * @param enable is motor should be run
         */
        void controlMotor(MOTOR_TYPE_t motorType, MOTOR_DIRECTION_t direction, bool enable);

        /**
         * @brief Get pin number for spercific motor and pin type
         * 
         * @param motorType type of motor (enum)
         * @param pinType type of pin (enum)
         */
        uint8_t getPin(MOTOR_TYPE_t motorType, PIN_TYPE_t pinType);

        /**
         * @brief Transform direction type to pin type representation 
         * 
         * @param direction wich direction should be run
         */
        inline PIN_TYPE_t tranformDirectionToPinType(MOTOR_DIRECTION_t direction) { if (direction == MOTOR_DIRECTION_t::FORWARD) return PIN_TYPE_t::FORWARD; else return PIN_TYPE_t::REVERSION; }

        /**
         * @brief Get pins numbers for specific motor type
         * 
         * @param motorType type of motor (enum)
         */
        MotorPins_st getPins(MOTOR_TYPE_t motorType);

    private:
        bool debug = false;

};

#endif // _HBRIDGE_H_LIBS_