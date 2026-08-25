#ifndef RELAY_CONFIG_H_
#define RELAY_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

#define RELAY_FAN_GROUP        DIO_GroupD
#define RELAY_FAN_PIN          DIO_Pin5

#define RELAY_HEATER_GROUP     DIO_GroupD
#define RELAY_HEATER_PIN       DIO_Pin6

#define RELAY_PUMP_GROUP       DIO_GroupD
#define RELAY_PUMP_PIN         DIO_Pin7

#define RELAY_CONNECTION_TYPE  RELAY_SourceConnection

#endif 