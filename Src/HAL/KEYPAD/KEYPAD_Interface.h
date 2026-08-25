#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_Private.h"
#include "KEYPAD_Config.h"

/**
 * @brief 
 */
void KeyPad_Init(void);

/**
 * @brief 
 * @return 
 */
uint8_t KeyPad_GetPressedKey(void);

#endif 