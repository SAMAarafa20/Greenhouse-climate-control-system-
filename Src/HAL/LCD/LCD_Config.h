#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"


#define LCD_CTRL_GROUP    DIO_GroupC
#define LCD_RS_PIN        DIO_Pin0
#define LCD_EN_PIN        DIO_Pin1

#define LCD_DATA_GROUP    DIO_GroupC
#define LCD_D4_PIN        DIO_Pin2
#define LCD_D5_PIN        DIO_Pin3
#define LCD_D6_PIN        DIO_Pin4
#define LCD_D7_PIN        DIO_Pin5

#endif 