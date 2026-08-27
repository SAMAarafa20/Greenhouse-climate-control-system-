#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

#include <stdint.h>

#define KEYPAD_NO_KEY_PRESSED    0xFFU

void KeyPad_Init(void);

uint8_t KeyPad_GetPressedKey(void);

#endif /* KEYPAD_INTERFACE_H */