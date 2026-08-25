#include "BUTTON_Interface.h"

void Btn_Init(uint8_t ButtonGroup, uint8_t ButtonPin, uint8_t Connection)
{
    DIO_DirectionSelectforPin(ButtonGroup, ButtonPin, DIO_Inputfor1Pin);

    if (Connection == BUTTON_InternalPullUp)
    {
        
        DIO_WritePin(ButtonGroup, ButtonPin, DIO_Highfor1Pin);
    }
    else
    {
        
        DIO_WritePin(ButtonGroup, ButtonPin, DIO_Lowfor1Pin);
    }
}

uint8_t Btn_ReadState(uint8_t ButtonGroup, uint8_t ButtonPin, uint8_t Connection)
{
    uint8_t RawPinState;
    uint8_t ButtonState;

    DIO_ReadPin(ButtonGroup, ButtonPin, &RawPinState);

    if ((Connection == BUTTON_InternalPullUp) || (Connection == BUTTON_ExternalPullUp))
    {
        
        ButtonState = (RawPinState == DIO_Lowfor1Pin) ? BUTTON_Pressed : BUTTON_NotPressed;
    }
    else 
    {
        
        ButtonState = (RawPinState == DIO_Highfor1Pin) ? BUTTON_Pressed : BUTTON_NotPressed;
    }

    return ButtonState;
}