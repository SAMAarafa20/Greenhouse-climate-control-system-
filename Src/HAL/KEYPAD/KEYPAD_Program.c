#include "KEYPAD_Interface.h"
#include "KEYPAD_Private.h"
#include "KEYPAD_Config.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include <util/delay.h>

static const uint8_t KeyPad_RowPins[KEYPAD_ROWS] =
{
    KEYPAD_ROW0_PIN,
    KEYPAD_ROW1_PIN,
    KEYPAD_ROW2_PIN,
    KEYPAD_ROW3_PIN
};

static const uint8_t KeyPad_ColPins[KEYPAD_COLS] =
{
    KEYPAD_COL0_PIN,
    KEYPAD_COL1_PIN,
    KEYPAD_COL2_PIN,
    KEYPAD_COL3_PIN
};

static const uint8_t
KeyPad_Map[KEYPAD_ROWS][KEYPAD_COLS] =
KEYPAD_DEFAULT_MAP;

void KeyPad_Init(void)
{
    uint8_t RowIndex = 0;
    uint8_t ColIndex = 0;

    /* Rows are Outputs and start High */
    for(RowIndex = 0U;
        RowIndex < KEYPAD_ROWS;
        RowIndex++)
    {
        DIO_DirectionSelectforPin(
            KEYPAD_ROWS_GROUP,
            KeyPad_RowPins[RowIndex],
            DIO_Outputfor1Pin);

        DIO_WritePin(
            KEYPAD_ROWS_GROUP,
            KeyPad_RowPins[RowIndex],
            DIO_Highfor1Pin);
    }

    /* Columns are Inputs with Internal Pull-Up */
    for(ColIndex = 0U;
        ColIndex < KEYPAD_COLS;
        ColIndex++)
    {
        DIO_DirectionSelectforPin(
            KEYPAD_COLS_GROUP,
            KeyPad_ColPins[ColIndex],
            DIO_Inputfor1Pin);

        DIO_WritePin(
            KEYPAD_COLS_GROUP,
            KeyPad_ColPins[ColIndex],
            DIO_Highfor1Pin);
    }
}

uint8_t KeyPad_GetPressedKey(void)
{
    uint8_t RowIndex = 0;
    uint8_t ColIndex = 0;
    uint8_t ColState = DIO_Highfor1Pin;

    for(RowIndex = 0U;
        RowIndex < KEYPAD_ROWS;
        RowIndex++)
    {
        DIO_WritePin(
            KEYPAD_ROWS_GROUP,
            KeyPad_RowPins[RowIndex],
            DIO_Lowfor1Pin);

        for(ColIndex = 0U;
            ColIndex < KEYPAD_COLS;
            ColIndex++)
        {
            DIO_ReadPin(
                KEYPAD_COLS_GROUP,
                KeyPad_ColPins[ColIndex],
                &ColState);

            if(ColState == DIO_Lowfor1Pin)
            {
                /* Debouncing */
                _delay_ms(20);

                DIO_ReadPin(
                    KEYPAD_COLS_GROUP,
                    KeyPad_ColPins[ColIndex],
                    &ColState);

                if(ColState == DIO_Lowfor1Pin)
                {
                    /*
                     * Wait until the user releases
                     * the pressed button.
                     */
                    while(ColState == DIO_Lowfor1Pin)
                    {
                        DIO_ReadPin(
                            KEYPAD_COLS_GROUP,
                            KeyPad_ColPins[ColIndex],
                            &ColState);
                    }

                    DIO_WritePin(
                        KEYPAD_ROWS_GROUP,
                        KeyPad_RowPins[RowIndex],
                        DIO_Highfor1Pin);

                    return KeyPad_Map[RowIndex]
                                     [ColIndex];
                }
            }
        }

        DIO_WritePin(
            KEYPAD_ROWS_GROUP,
            KeyPad_RowPins[RowIndex],
            DIO_Highfor1Pin);
    }

    return KEYPAD_NO_KEY_PRESSED;
}