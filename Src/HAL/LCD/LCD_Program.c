#include "LCD_Interface.h"
#include <util/delay.h>


static void LCD_SendNibble(uint8_t Nibble)
{
    DIO_WritePin(LCD_DATA_GROUP, LCD_D4_PIN, (uint8_t)((Nibble >> 0U) & 0x01U));
    DIO_WritePin(LCD_DATA_GROUP, LCD_D5_PIN, (uint8_t)((Nibble >> 1U) & 0x01U));
    DIO_WritePin(LCD_DATA_GROUP, LCD_D6_PIN, (uint8_t)((Nibble >> 2U) & 0x01U));
    DIO_WritePin(LCD_DATA_GROUP, LCD_D7_PIN, (uint8_t)((Nibble >> 3U) & 0x01U));

    
    DIO_WritePin(LCD_CTRL_GROUP, LCD_EN_PIN, DIO_Highfor1Pin);
    _delay_us(1);
    DIO_WritePin(LCD_CTRL_GROUP, LCD_EN_PIN, DIO_Lowfor1Pin);
    _delay_us(100);
}


static void LCD_SendByte(uint8_t Byte, uint8_t IsData)
{
    DIO_WritePin(LCD_CTRL_GROUP, LCD_RS_PIN, IsData ? DIO_Highfor1Pin : DIO_Lowfor1Pin);

    LCD_SendNibble((uint8_t)(Byte >> 4U));   
    LCD_SendNibble((uint8_t)(Byte & 0x0FU)); 
}

static void LCD_SendCommand(uint8_t Command)
{
    LCD_SendByte(Command, 0U);

    if ((Command == LCD_CMD_CLEAR_DISPLAY) || (Command == LCD_CMD_RETURN_HOME))
    {
        _delay_ms(2); 
    }
}

void LCD_Init(void)
{
   
    DIO_DirectionSelectforPin(LCD_CTRL_GROUP, LCD_RS_PIN, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(LCD_CTRL_GROUP, LCD_EN_PIN, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(LCD_DATA_GROUP, LCD_D4_PIN, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(LCD_DATA_GROUP, LCD_D5_PIN, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(LCD_DATA_GROUP, LCD_D6_PIN, DIO_Outputfor1Pin);
    DIO_DirectionSelectforPin(LCD_DATA_GROUP, LCD_D7_PIN, DIO_Outputfor1Pin);

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
    LCD_SendByte(Character, 1U);
}

void LCD_WriteString(const uint8_t *String)
{
    while (*String != '\0')
    {
        LCD_WriteChar(*String);
        String++;
    }
}

void LCD_GoToXY(uint8_t Row, uint8_t Column)
{
    uint8_t Address;

    if (Row == 0U)
    {
        Address = (uint8_t)(LCD_ROW0_ADDR + Column);
    }
    else
    {
        Address = (uint8_t)(LCD_ROW1_ADDR + Column);
    }

    LCD_SendCommand((uint8_t)(LCD_CMD_SET_DDRAM_ADDR | Address));
}

void LCD_Clear(void)
{
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
}