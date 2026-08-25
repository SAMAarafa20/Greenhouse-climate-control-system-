#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

/**
 * @brief 
 */
void LCD_Init(void);

/**
 * @brief 
 */
void LCD_WriteChar(uint8_t Character);

/**
 * @brief 
 */
void LCD_WriteString(const uint8_t *String);

/**
 * @brief 
 */
void LCD_GoToXY(uint8_t Row, uint8_t Column);

/**
 * @brief 
 */
void LCD_Clear(void);

#endif 