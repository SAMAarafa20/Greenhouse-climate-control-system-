#include <stdint.h>
#include "../COMMON/STD_DEFINITIONS.h"
#include "../COMMON/BIT_MATH.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

void DIO_DirectionSelectforPin(const uint8_t GroupName, const uint8_t PinNo, const uint8_t DirectionState)
{
    if (DirectionState == DIO_Outputfor1Pin)
    {
        switch (GroupName)
        {
            case DIO_GroupA: SetBit(DDRA, PinNo); break;
            case DIO_GroupB: SetBit(DDRB, PinNo); break;
            case DIO_GroupC: SetBit(DDRC, PinNo); break;
            case DIO_GroupD: SetBit(DDRD, PinNo); break;
        }
    }
    else if (DirectionState == DIO_Inputfor1Pin)
    {
        switch (GroupName)
        {
            case DIO_GroupA: ClearBit(DDRA, PinNo); break;
            case DIO_GroupB: ClearBit(DDRB, PinNo); break;
            case DIO_GroupC: ClearBit(DDRC, PinNo); break;
            case DIO_GroupD: ClearBit(DDRD, PinNo); break;
        }
    }
}

void DIO_DirectionSelectforGroup(const uint8_t GroupName, const uint8_t DirectionState)
{
    switch (GroupName)
    {
        case DIO_GroupA: DDRA = DirectionState; break;
        case DIO_GroupB: DDRB = DirectionState; break;
        case DIO_GroupC: DDRC = DirectionState; break;
        case DIO_GroupD: DDRD = DirectionState; break;
    }
}

void DIO_WritePin(const uint8_t GroupName, const uint8_t PinNo, const uint8_t OutputValue)
{
    if (OutputValue == DIO_Highfor1Pin)
    {
        switch (GroupName)
        {
            case DIO_GroupA: SetBit(PORTA, PinNo); break;
            case DIO_GroupB: SetBit(PORTB, PinNo); break;
            case DIO_GroupC: SetBit(PORTC, PinNo); break;
            case DIO_GroupD: SetBit(PORTD, PinNo); break;
        }
    }
    else if (OutputValue == DIO_Lowfor1Pin)
    {
        switch (GroupName)
        {
            case DIO_GroupA: ClearBit(PORTA, PinNo); break;
            case DIO_GroupB: ClearBit(PORTB, PinNo); break;
            case DIO_GroupC: ClearBit(PORTC, PinNo); break;
            case DIO_GroupD: ClearBit(PORTD, PinNo); break;
        }
    }
}

void DIO_WriteGroup(const uint8_t GroupName, const uint8_t OutputValue)
{
    switch (GroupName)
    {
        case DIO_GroupA: PORTA = OutputValue; break;
        case DIO_GroupB: PORTB = OutputValue; break;
        case DIO_GroupC: PORTC = OutputValue; break;
        case DIO_GroupD: PORTD = OutputValue; break;
    }
}

void DIO_ReadPin(const uint8_t GroupName, const uint8_t PinNo, uint8_t *InputState)
{
    if (InputState != NULL)
    {
        switch (GroupName)
        {
            case DIO_GroupA: *InputState = ReadBit(PINA, PinNo); break;
            case DIO_GroupB: *InputState = ReadBit(PINB, PinNo); break;
            case DIO_GroupC: *InputState = ReadBit(PINC, PinNo); break;
            case DIO_GroupD: *InputState = ReadBit(PIND, PinNo); break;
        }
    }
}

void DIO_ReadGroup(const uint8_t GroupName, uint8_t *InputState)
{
    if (InputState != NULL)
    {
        switch (GroupName)
        {
            case DIO_GroupA: *InputState = PINA; break;
            case DIO_GroupB: *InputState = PINB; break;
            case DIO_GroupC: *InputState = PINC; break;
            case DIO_GroupD: *InputState = PIND; break;
        }
    }
}

void DIO_TogglePin(const uint8_t GroupName, const uint8_t PinNo)
{
    switch (GroupName)
    {
        case DIO_GroupA: ToggleBit(PORTA, PinNo); break;
        case DIO_GroupB: ToggleBit(PORTB, PinNo); break;
        case DIO_GroupC: ToggleBit(PORTC, PinNo); break;
        case DIO_GroupD: ToggleBit(PORTD, PinNo); break;
    }
}

void DIO_ToggleGroup(const uint8_t GroupName)
{
    switch (GroupName)
    {
        case DIO_GroupA: PORTA = ~PORTA; break;
        case DIO_GroupB: PORTB = ~PORTB; break;
        case DIO_GroupC: PORTC = ~PORTC; break;
        case DIO_GroupD: PORTD = ~PORTD; break;
    }
}