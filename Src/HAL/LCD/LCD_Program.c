#include "LCD_Interface.h"

#include <util/delay.h>

static void LCD_SendNibble(uint8_t Nibble)
{
    DIO_WritePin(LCD_DATA_GROUP,
                 LCD_D4_PIN,
                 (uint8_t)((Nibble >> 0U) & 0x01U));

    DIO_WritePin(LCD_DATA_GROUP,
                 LCD_D5_PIN,
                 (uint8_t)((Nibble >> 1U) & 0x01U));

    DIO_WritePin(LCD_DATA_GROUP,
                 LCD_D6_PIN,
                 (uint8_t)((Nibble >> 2U) & 0x01U));

    DIO_WritePin(LCD_DATA_GROUP,
                 LCD_D7_PIN,
                 (uint8_t)((Nibble >> 3U) & 0x01U));

    DIO_WritePin(LCD_CTRL_GROUP,
                 LCD_EN_PIN,
                 DIO_Highfor1Pin);

    _delay_us(1);

    DIO_WritePin(LCD_CTRL_GROUP,
                 LCD_EN_PIN,
                 DIO_Lowfor1Pin);

    _delay_us(100);
}

static void LCD_SendByte(uint8_t Byte, uint8_t DataType)
{
    if(DataType == LCD_DATA)
    {
        DIO_WritePin(LCD_CTRL_GROUP,
                     LCD_RS_PIN,
                     DIO_Highfor1Pin);
    }
    else
    {
        DIO_WritePin(LCD_CTRL_GROUP,
                     LCD_RS_PIN,
                     DIO_Lowfor1Pin);
    }

    LCD_SendNibble((uint8_t)(Byte >> 4U));

    LCD_SendNibble((uint8_t)(Byte & 0x0FU));
}

static void LCD_SendCommand(uint8_t Command)
{
    LCD_SendByte(Command, LCD_COMMAND);

    if((Command == LCD_CMD_CLEAR_DISPLAY) ||
       (Command == LCD_CMD_RETURN_HOME))
    {
        _delay_ms(2);
    }
}

void LCD_Init(void)
{
    DIO_DirectionSelectforPin(LCD_CTRL_GROUP,
                              LCD_RS_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(LCD_CTRL_GROUP,
                              LCD_EN_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(LCD_DATA_GROUP,
                              LCD_D4_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(LCD_DATA_GROUP,
                              LCD_D5_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(LCD_DATA_GROUP,
                              LCD_D6_PIN,
                              DIO_Outputfor1Pin);

    DIO_DirectionSelectforPin(LCD_DATA_GROUP,
                              LCD_D7_PIN,
                              DIO_Outputfor1Pin);

    DIO_WritePin(LCD_CTRL_GROUP,
                 LCD_RS_PIN,
                 DIO_Lowfor1Pin);

    DIO_WritePin(LCD_CTRL_GROUP,
                 LCD_EN_PIN,
                 DIO_Lowfor1Pin);

    _delay_ms(20);

    LCD_SendNibble(0x03U);
    _delay_ms(5);

    LCD_SendNibble(0x03U);
    _delay_us(150);

    LCD_SendNibble(0x03U);

    LCD_SendNibble(0x02U);

    LCD_SendCommand(LCD_CMD_FUNCTION_SET_4BIT);

    LCD_SendCommand(LCD_CMD_DISPLAY_ON_CURSOR_OFF);

    LCD_SendCommand(LCD_CMD_ENTRY_MODE_INC);

    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
}

void LCD_WriteChar(uint8_t Character)
{
    LCD_SendByte(Character, LCD_DATA);
}

void LCD_WriteString(const uint8_t *String)
{
    if(String != NULL)
    {
        while(*String != '\0')
        {
            LCD_WriteChar(*String);

            String++;
        }
    }
}

void LCD_WriteNumber(uint16_t Number)
{
    uint8_t Digits[5];
    uint8_t DigitIndex = 0;

    if(Number == 0U)
    {
        LCD_WriteChar('0');
    }
    else
    {
        while(Number > 0U)
        {
            Digits[DigitIndex] = (uint8_t)(Number % 10U);

            Number = Number / 10U;

            DigitIndex++;
        }

        while(DigitIndex > 0U)
        {
            DigitIndex--;

            LCD_WriteChar((uint8_t)(Digits[DigitIndex] + '0'));
        }
    }
}

void LCD_GoToXY(uint8_t Row, uint8_t Column)
{
    uint8_t Address = 0;

    if(Column <= LCD_MAX_COLUMN)
    {
        if(Row == LCD_FIRST_ROW)
        {
            Address = (uint8_t)(LCD_ROW0_ADDR + Column);

            LCD_SendCommand(
                (uint8_t)(LCD_CMD_SET_DDRAM_ADDR | Address));
        }
        else if(Row == LCD_SECOND_ROW)
        {
            Address = (uint8_t)(LCD_ROW1_ADDR + Column);

            LCD_SendCommand(
                (uint8_t)(LCD_CMD_SET_DDRAM_ADDR | Address));
        }
        else
        {
            /* Error */
        }
    }
}

void LCD_Clear(void)
{
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
}