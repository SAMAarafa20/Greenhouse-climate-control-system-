#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "DC_MOTOR_Private.h"
#include "DC_MOTOR_Config.h"

/**
 * @brief 
 */
void DCMotor_Init(uint8_t MotorGroup, uint8_t MotorPin1, uint8_t MotorPin2);

/**
 * @brief 
 * @param State  DCMOTOR_Stop / DCMOTOR_Forward / DCMOTOR_Backward
 */
void DCMotor_SetState(uint8_t MotorGroup, uint8_t MotorPin1, uint8_t MotorPin2, uint8_t State);

#endif 