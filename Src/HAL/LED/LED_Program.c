#include "LED_Interface.h"

void Led_Init(uint8_t LedGroup, uint8_t LedPin)
{
    DIO_DirectionSelectforPin(LedGroup, LedPin, DIO_Outputfor1Pin);
}

void Led_On(uint8_t LedGroup, uint8_t LedPin, uint8_t ConnectionType)
{
    if (ConnectionType == LED_SOURCE_CONNECTION)
    {
        DIO_WritePin(LedGroup, LedPin, DIO_Highfor1Pin);
    }
    else if (ConnectionType == LED_SINK_CONNECTION)
    {
        DIO_WritePin(LedGroup, LedPin, DIO_Lowfor1Pin);
    }
    else
    {
        
    }
}

void Led_Off(uint8_t LedGroup, uint8_t LedPin, uint8_t ConnectionType)
{
    if (ConnectionType == LED_SOURCE_CONNECTION)
    {
        DIO_WritePin(LedGroup, LedPin, DIO_Lowfor1Pin);
    }
    else if (ConnectionType == LED_SINK_CONNECTION)
    {
        DIO_WritePin(LedGroup, LedPin, DIO_Highfor1Pin);
    }
    else
    {
        
    }
}

void Led_Toggle(uint8_t LedGroup, uint8_t LedPin)
{
    DIO_TogglePin(LedGroup, LedPin);
}