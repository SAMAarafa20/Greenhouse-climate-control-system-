#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#include "../../MCAL/DIO/DIO_interface.h"

/* Proteus Keypad Rows: A, B, C, D */
#define KEYPAD_ROWS_GROUP     DIO_GroupB

#define KEYPAD_ROW0_PIN       DIO_Pin0
#define KEYPAD_ROW1_PIN       DIO_Pin1
#define KEYPAD_ROW2_PIN       DIO_Pin2
#define KEYPAD_ROW3_PIN       DIO_Pin3

/* Proteus Keypad Columns: 1, 2, 3, 4 */
#define KEYPAD_COLS_GROUP     DIO_GroupB

#define KEYPAD_COL0_PIN       DIO_Pin4
#define KEYPAD_COL1_PIN       DIO_Pin5
#define KEYPAD_COL2_PIN       DIO_Pin6
#define KEYPAD_COL3_PIN       DIO_Pin7

#define KEYPAD_DEFAULT_MAP       \
{                                \
    {'7', '8', '9', '/'},        \
    {'4', '5', '6', '*'},        \
    {'1', '2', '3', '-'},        \
    {'C', '0', '=', '+'}         \
}

#endif /* KEYPAD_CONFIG_H */