#include "DIO_interface.h"
#include "DIO_private.h"

#include "../../Commen/BIT_MATH.h"

#include <stddef.h>
#include <stdint.h>

void DIO_DisableJTAG(void)
{
    uint8_t Local_u8SREGValue =
        DIO_SREG_REG;

    /*
     * Disable Global Interrupt temporarily.
     */
    ClearBit(
        DIO_SREG_REG,
        DIO_GLOBAL_INTERRUPT_BIT);

    /*
     * According to the ATmega32 datasheet,
     * JTD must be written to logic one twice
     * within four CPU clock cycles.
     */
    SetBit(
        DIO_MCUCSR_REG,
        DIO_JTD_BIT);

    SetBit(
        DIO_MCUCSR_REG,
        DIO_JTD_BIT);

    /*
     * Restore the previous SREG value.
     */
    DIO_SREG_REG =
        Local_u8SREGValue;
}

void DIO_DirectionSelectforPin(
    const uint8_t GroupName,
    const uint8_t PinNo,
    const uint8_t DirectionState)
{
    if(PinNo <= DIO_Pin7)
    {
        if(DirectionState ==
           DIO_Outputfor1Pin)
        {
            switch(GroupName)
            {
                case DIO_GroupA:
                    SetBit(DDRA_REG, PinNo);
                    break;

                case DIO_GroupB:
                    SetBit(DDRB_REG, PinNo);
                    break;

                case DIO_GroupC:
                    SetBit(DDRC_REG, PinNo);
                    break;

                case DIO_GroupD:
                    SetBit(DDRD_REG, PinNo);
                    break;

                default:
                    /* Invalid Group */
                    break;
            }
        }
        else if(DirectionState ==
                DIO_Inputfor1Pin)
        {
            switch(GroupName)
            {
                case DIO_GroupA:
                    ClearBit(DDRA_REG, PinNo);
                    break;

                case DIO_GroupB:
                    ClearBit(DDRB_REG, PinNo);
                    break;

                case DIO_GroupC:
                    ClearBit(DDRC_REG, PinNo);
                    break;

                case DIO_GroupD:
                    ClearBit(DDRD_REG, PinNo);
                    break;

                default:
                    /* Invalid Group */
                    break;
            }
        }
        else
        {
            /* Invalid Direction */
        }
    }
    else
    {
        /* Invalid Pin */
    }
}

void DIO_DirectionSelectforGroup(
    const uint8_t GroupName,
    const uint8_t DirectionState)
{
    switch(GroupName)
    {
        case DIO_GroupA:
            DDRA_REG = DirectionState;
            break;

        case DIO_GroupB:
            DDRB_REG = DirectionState;
            break;

        case DIO_GroupC:
            DDRC_REG = DirectionState;
            break;

        case DIO_GroupD:
            DDRD_REG = DirectionState;
            break;

        default:
            /* Invalid Group */
            break;
    }
}

void DIO_WritePin(
    const uint8_t GroupName,
    const uint8_t PinNo,
    const uint8_t OutputValue)
{
    if(PinNo <= DIO_Pin7)
    {
        if(OutputValue ==
           DIO_Highfor1Pin)
        {
            switch(GroupName)
            {
                case DIO_GroupA:
                    SetBit(PORTA_REG, PinNo);
                    break;

                case DIO_GroupB:
                    SetBit(PORTB_REG, PinNo);
                    break;

                case DIO_GroupC:
                    SetBit(PORTC_REG, PinNo);
                    break;

                case DIO_GroupD:
                    SetBit(PORTD_REG, PinNo);
                    break;

                default:
                    /* Invalid Group */
                    break;
            }
        }
        else if(OutputValue ==
                DIO_Lowfor1Pin)
        {
            switch(GroupName)
            {
                case DIO_GroupA:
                    ClearBit(PORTA_REG, PinNo);
                    break;

                case DIO_GroupB:
                    ClearBit(PORTB_REG, PinNo);
                    break;

                case DIO_GroupC:
                    ClearBit(PORTC_REG, PinNo);
                    break;

                case DIO_GroupD:
                    ClearBit(PORTD_REG, PinNo);
                    break;

                default:
                    /* Invalid Group */
                    break;
            }
        }
        else
        {
            /* Invalid Output Value */
        }
    }
    else
    {
        /* Invalid Pin */
    }
}

void DIO_WriteGroup(
    const uint8_t GroupName,
    const uint8_t OutputValue)
{
    switch(GroupName)
    {
        case DIO_GroupA:
            PORTA_REG = OutputValue;
            break;

        case DIO_GroupB:
            PORTB_REG = OutputValue;
            break;

        case DIO_GroupC:
            PORTC_REG = OutputValue;
            break;

        case DIO_GroupD:
            PORTD_REG = OutputValue;
            break;

        default:
            /* Invalid Group */
            break;
    }
}

void DIO_ReadPin(
    const uint8_t GroupName,
    const uint8_t PinNo,
    uint8_t *InputState)
{
    if((PinNo <= DIO_Pin7) &&
       (InputState != NULL))
    {
        switch(GroupName)
        {
            case DIO_GroupA:
                *InputState =
                    ReadBit(PINA_REG, PinNo);
                break;

            case DIO_GroupB:
                *InputState =
                    ReadBit(PINB_REG, PinNo);
                break;

            case DIO_GroupC:
                *InputState =
                    ReadBit(PINC_REG, PinNo);
                break;

            case DIO_GroupD:
                *InputState =
                    ReadBit(PIND_REG, PinNo);
                break;

            default:
                /* Invalid Group */
                break;
        }
    }
    else
    {
        /* Invalid Pin or Null Pointer */
    }
}

void DIO_ReadGroup(
    const uint8_t GroupName,
    uint8_t *InputState)
{
    if(InputState != NULL)
    {
        switch(GroupName)
        {
            case DIO_GroupA:
                *InputState = PINA_REG;
                break;

            case DIO_GroupB:
                *InputState = PINB_REG;
                break;

            case DIO_GroupC:
                *InputState = PINC_REG;
                break;

            case DIO_GroupD:
                *InputState = PIND_REG;
                break;

            default:
                /* Invalid Group */
                break;
        }
    }
    else
    {
        /* Null Pointer */
    }
}

void DIO_TogglePin(
    const uint8_t GroupName,
    const uint8_t PinNo)
{
    if(PinNo <= DIO_Pin7)
    {
        switch(GroupName)
        {
            case DIO_GroupA:
                ToggleBit(PORTA_REG, PinNo);
                break;

            case DIO_GroupB:
                ToggleBit(PORTB_REG, PinNo);
                break;

            case DIO_GroupC:
                ToggleBit(PORTC_REG, PinNo);
                break;

            case DIO_GroupD:
                ToggleBit(PORTD_REG, PinNo);
                break;

            default:
                /* Invalid Group */
                break;
        }
    }
    else
    {
        /* Invalid Pin */
    }
}

void DIO_ToggleGroup(
    const uint8_t GroupName)
{
    switch(GroupName)
    {
        case DIO_GroupA:
            PORTA_REG =
                (uint8_t)(~PORTA_REG);
            break;

        case DIO_GroupB:
            PORTB_REG =
                (uint8_t)(~PORTB_REG);
            break;

        case DIO_GroupC:
            PORTC_REG =
                (uint8_t)(~PORTC_REG);
            break;

        case DIO_GroupD:
            PORTD_REG =
                (uint8_t)(~PORTD_REG);
            break;

        default:
            /* Invalid Group */
            break;
    }
}