#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define LCD_CMD_CLEAR_DISPLAY          0x01U
#define LCD_CMD_RETURN_HOME            0x02U
#define LCD_CMD_ENTRY_MODE_INC         0x06U
#define LCD_CMD_DISPLAY_ON_CURSOR_OFF  0x0CU
#define LCD_CMD_FUNCTION_SET_4BIT      0x28U
#define LCD_CMD_SET_DDRAM_ADDR         0x80U

#define LCD_ROW0_ADDR                  0x00U
#define LCD_ROW1_ADDR                  0x40U

#define LCD_FIRST_ROW                  0U
#define LCD_SECOND_ROW                 1U
#define LCD_MAX_COLUMN                 15U

#define LCD_COMMAND                    0U
#define LCD_DATA                       1U

#endif /* LCD_PRIVATE_H_ */