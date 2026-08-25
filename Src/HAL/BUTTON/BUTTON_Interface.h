#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "BUTTON_Private.h"
#include "BUTTON_Config.h"

/**
 * @brief 
 * @param ButtonGroup, ButtonPin  
 * @param Connection  BUTTON_InternalPullUp / BUTTON_ExternalPullUp / BUTTON_ExternalPullDown
 */
void Btn_Init(uint8_t ButtonGroup, uint8_t ButtonPin, uint8_t Connection);

/**
 * @brief 
 * @return BUTTON_Pressed أو BUTTON_NotPressed
 */
uint8_t Btn_ReadState(uint8_t ButtonGroup, uint8_t ButtonPin, uint8_t Connection);

#endif 