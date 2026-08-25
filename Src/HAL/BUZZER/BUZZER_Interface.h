#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "BUZZER_Private.h"
#include "BUZZER_Config.h"

/**
 * @brief 
 */
void Buzzer_Init(void);

/**
 * @brief 
 */
void Buzzer_On(void);

/**
 * @brief 
 */
void Buzzer_Off(void);

/**
 * @brief BUZZER_TONE_TIME_MS 
 */
void Buzzer_Tone(void);

#endif 