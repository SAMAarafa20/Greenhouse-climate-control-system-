#ifndef RELAY_CONFIG_H_
#define RELAY_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"
#include "RELAY_Private.h"

/* Fan Relay Configuration */
#define RELAY_FAN_GROUP        DIO_GroupD
#define RELAY_FAN_PIN          DIO_Pin5

/* Heater Relay Configuration */
#define RELAY_HEATER_GROUP     DIO_GroupD
#define RELAY_HEATER_PIN       DIO_Pin6

/* Pump Relay Configuration */
#define RELAY_PUMP_GROUP       DIO_GroupD
#define RELAY_PUMP_PIN         DIO_Pin7

/*
 * RELAY_SourceConnection:
 * High turns relay ON.
 *
 * RELAY_SinkConnection:
 * Low turns relay ON.
 */
#define RELAY_CONNECTION_TYPE  RELAY_SourceConnection

#endif /* RELAY_CONFIG_H_ */