#ifndef RELAY_CONFIG_H_
#define RELAY_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

/*
 * Greenhouse Relay Pin Mapping
 *
 * Pump Relay   -> PD3
 * Fan Relay    -> PD4
 * Heater Relay -> PD5
 */

#define RELAY_PUMP_GROUP       DIO_GroupD
#define RELAY_PUMP_PIN         DIO_Pin3

#define RELAY_FAN_GROUP        DIO_GroupD
#define RELAY_FAN_PIN          DIO_Pin4

#define RELAY_HEATER_GROUP     DIO_GroupD
#define RELAY_HEATER_PIN       DIO_Pin5

/*
 * Relay module is Active High:
 *
 * HIGH -> Relay ON
 * LOW  -> Relay OFF
 */
#define RELAY_CONNECTION_TYPE  RELAY_SourceConnection

#endif /* RELAY_CONFIG_H_ */