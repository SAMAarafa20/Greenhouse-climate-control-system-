#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include <stdint.h>

#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "LCD_Private.h"
#include "LCD_Config.h"

void LCD_Init(void);

void LCD_WriteChar(uint8_t Character);

void LCD_WriteString(const uint8_t *String);

void LCD_WriteNumber(uint16_t Number);

void LCD_GoToXY(uint8_t Row, uint8_t Column);

void LCD_Clear(void);

#endif /* LCD_INTERFACE_H_ */