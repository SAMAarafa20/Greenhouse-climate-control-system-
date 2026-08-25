#include "BUZZER_Interface.h"
#include <util/delay.h>

void Buzzer_Init(void)
{
    DIO_DirectionSelectforPin(BUZZER_GROUP, BUZZER_PIN, DIO_Outputfor1Pin);
    Buzzer_Off();
}

void Buzzer_On(void)
{
    if (BUZZER_CONNECTION_TYPE == BUZZER_SourceConnection)
    {
        DIO_WritePin(BUZZER_GROUP, BUZZER_PIN, DIO_Highfor1Pin);
    }
    else
    {
        DIO_WritePin(BUZZER_GROUP, BUZZER_PIN, DIO_Lowfor1Pin);
    }
}

void Buzzer_Off(void)
{
    if (BUZZER_CONNECTION_TYPE == BUZZER_SourceConnection)
    {
        DIO_WritePin(BUZZER_GROUP, BUZZER_PIN, DIO_Lowfor1Pin);
    }
    else
    {
        DIO_WritePin(BUZZER_GROUP, BUZZER_PIN, DIO_Highfor1Pin);
    }
}

void Buzzer_Tone(void)
{
    uint16_t Local_u16Counter;

    Buzzer_On();

    
    for (Local_u16Counter = 0U; Local_u16Counter < BUZZER_TONE_TIME_MS; Local_u16Counter++)
    {
        _delay_ms(1);
    }

    Buzzer_Off();
}