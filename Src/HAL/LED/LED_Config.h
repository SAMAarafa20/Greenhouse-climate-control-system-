#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

/*
 * Critical Alarm Red LED
 *
 * Red LED -> PD7
 */

#define ALARM_LED_GROUP              DIO_GroupD
#define ALARM_LED_PIN                DIO_Pin7

#define ALARM_LED_CONNECTION_TYPE    LED_SOURCE_CONNECTION

#endif /* LED_CONFIG_H_ */