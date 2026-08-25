#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

#include <stdint.h>
#include "../../Commen/BIT_MATH.h"
#include "../../Commen/DEFINITIONS.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "RELAY_Private.h"
#include "RELAY_Config.h"


void Relay_Init(void);


void Relay_TurnOn(uint8_t RelayId);


void Relay_TurnOff(uint8_t RelayId);

#endif /* RELAY_INTERFACE_H_ */