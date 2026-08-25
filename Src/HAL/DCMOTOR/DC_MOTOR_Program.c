#include "DC_MOTOR_Interface.h"

void DCMotor_Init(uint8_t MotorGroup, uint8_t MotorPin1, uint8_t MotorPin2)
{
    DIO_DirectionSelectforPin(MotorGroup, MotorPin1, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(MotorGroup, MotorPin2, DIO_Outputfor1Pin);

    DCMotor_SetState(MotorGroup, MotorPin1, MotorPin2, DCMOTOR_Stop);
}

void DCMotor_SetState(uint8_t MotorGroup, uint8_t MotorPin1, uint8_t MotorPin2, uint8_t State)
{
    switch (State)
    {
        case DCMOTOR_Forward:
            DIO_WritePin(MotorGroup, MotorPin1, DIO_Highfor1Pin);
            DIO_WritePin(MotorGroup, MotorPin2, DIO_Lowfor1Pin);
            break;

        case DCMOTOR_Backward:
            DIO_WritePin(MotorGroup, MotorPin1, DIO_Lowfor1Pin);
            DIO_WritePin(MotorGroup, MotorPin2, DIO_Highfor1Pin);
            break;

        case DCMOTOR_Stop:
        default:
            DIO_WritePin(MotorGroup, MotorPin1, DIO_Lowfor1Pin);
            DIO_WritePin(MotorGroup, MotorPin2, DIO_Lowfor1Pin);
            break;
    }
}