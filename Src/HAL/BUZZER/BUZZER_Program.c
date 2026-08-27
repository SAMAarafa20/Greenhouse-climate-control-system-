#include "BUZZER_Interface.h"
#include "BUZZER_Private.h"
#include "BUZZER_Config.h"

#include "../../MCAL/DIO/DIO_interface.h"

void Buzzer_Init(void)
{
    DIO_DirectionSelectforPin(BUZZER_GROUP,
                              BUZZER_PIN,
                              DIO_Outputfor1Pin);

    Buzzer_Off();
}

void Buzzer_On(void)
{
    if(BUZZER_CONNECTION_TYPE ==
       BUZZER_SourceConnection)
    {
        DIO_WritePin(BUZZER_GROUP,
                     BUZZER_PIN,
                     DIO_Highfor1Pin);
    }
    else if(BUZZER_CONNECTION_TYPE ==
            BUZZER_SinkConnection)
    {
        DIO_WritePin(BUZZER_GROUP,
                     BUZZER_PIN,
                     DIO_Lowfor1Pin);
    }
    else
    {
        /* Error */
    }
}

void Buzzer_Off(void)
{
    if(BUZZER_CONNECTION_TYPE ==
       BUZZER_SourceConnection)
    {
        DIO_WritePin(BUZZER_GROUP,
                     BUZZER_PIN,
                     DIO_Lowfor1Pin);
    }
    else if(BUZZER_CONNECTION_TYPE ==
            BUZZER_SinkConnection)
    {
        DIO_WritePin(BUZZER_GROUP,
                     BUZZER_PIN,
                     DIO_Highfor1Pin);
    }
    else
    {
        /* Error */
    }
}