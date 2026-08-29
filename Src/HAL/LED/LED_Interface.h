#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include <stdint.h>

#include "../../MCAL/DIO/DIO_interface.h"

#define LED_SINK_CONNECTION      0U
#define LED_SOURCE_CONNECTION    1U

void Led_Init(uint8_t LedGroup,
              uint8_t LedPin);

void Led_On(uint8_t LedGroup,
            uint8_t LedPin,
            uint8_t ConnectionType);

void Led_Off(uint8_t LedGroup,
             uint8_t LedPin,
             uint8_t ConnectionType);

void Led_Toggle(uint8_t LedGroup,
                uint8_t LedPin);

#endif /* LED_INTERFACE_H_ */