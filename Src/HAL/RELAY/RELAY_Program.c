#include "RELAY_Interface.h"
#include "RELAY_Interface.h"
#include <stddef.h>


static uint8_t Relay_GetPinInfo(uint8_t RelayId,
                                uint8_t *GroupName,
                                uint8_t *PinNo)
{
    uint8_t RelayState = RELAY_VALID_ID;

    if(GroupName != NULL && PinNo != NULL)
    {
        switch(RelayId)
        {
            case RELAY_FAN:
                *GroupName = RELAY_FAN_GROUP;
                *PinNo = RELAY_FAN_PIN;
                break;

            case RELAY_HEATER:
                *GroupName = RELAY_HEATER_GROUP;
                *PinNo = RELAY_HEATER_PIN;
                break;

            case RELAY_PUMP:
                *GroupName = RELAY_PUMP_GROUP;
                *PinNo = RELAY_PUMP_PIN;
                break;

            default:
                RelayState = RELAY_INVALID_ID;
                break;
        }
    }
    else
    {
        RelayState = RELAY_INVALID_ID;
    }

    return RelayState;
}

void Relay_Init(void)
{
    DIO_DirectionSelectforPin(RELAY_FAN_GROUP,
                              RELAY_FAN_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(RELAY_HEATER_GROUP,
                              RELAY_HEATER_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(RELAY_PUMP_GROUP,
                              RELAY_PUMP_PIN,
                              DIO_Outputfor1Pin);

    Relay_TurnOff(RELAY_FAN);
    Relay_TurnOff(RELAY_HEATER);
    Relay_TurnOff(RELAY_PUMP);
}

void Relay_TurnOn(uint8_t RelayId)
{
    uint8_t GroupName = 0;
    uint8_t PinNo = 0;
    uint8_t RelayState = RELAY_INVALID_ID;

    RelayState = Relay_GetPinInfo(RelayId,
                                  &GroupName,
                                  &PinNo);

    if(RelayState == RELAY_VALID_ID)
    {
        if(RELAY_CONNECTION_TYPE == RELAY_SourceConnection)
        {
            DIO_WritePin(GroupName,
                         PinNo,
                         DIO_Highfor1Pin);
        }
        else if(RELAY_CONNECTION_TYPE == RELAY_SinkConnection)
        {
            DIO_WritePin(GroupName,
                         PinNo,
                         DIO_Lowfor1Pin);
        }
        else
        {
            /* Error */
        }
    }
}

void Relay_TurnOff(uint8_t RelayId)
{
    uint8_t GroupName = 0;
    uint8_t PinNo = 0;
    uint8_t RelayState = RELAY_INVALID_ID;

    RelayState = Relay_GetPinInfo(RelayId,
                                  &GroupName,
                                  &PinNo);

    if(RelayState == RELAY_VALID_ID)
    {
        if(RELAY_CONNECTION_TYPE == RELAY_SourceConnection)
        {
            DIO_WritePin(GroupName,
                         PinNo,
                         DIO_Lowfor1Pin);
        }
        else if(RELAY_CONNECTION_TYPE == RELAY_SinkConnection)
        {
            DIO_WritePin(GroupName,
                         PinNo,
                         DIO_Highfor1Pin);
        }
        else
        {
            /* Error */
        }
    }
}