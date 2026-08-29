#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

/*
 * LCD 16x2 - 4 Bit Mode
 *
 * RS -> PC2
 * EN -> PC3
 * RW -> GND
 *
 * D4 -> PC4
 * D5 -> PC5
 * D6 -> PC6
 * D7 -> PC7
 */

#define LCD_CTRL_GROUP    DIO_GroupC

#define LCD_RS_PIN        DIO_Pin2
#define LCD_EN_PIN        DIO_Pin3

#define LCD_DATA_GROUP    DIO_GroupC

#define LCD_D4_PIN        DIO_Pin4
#define LCD_D5_PIN        DIO_Pin5
#define LCD_D6_PIN        DIO_Pin6
#define LCD_D7_PIN        DIO_Pin7

#endif /* LCD_CONFIG_H_ */