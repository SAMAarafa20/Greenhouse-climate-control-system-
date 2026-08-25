#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include <stdint.h>

/* Enums */
typedef enum
{
    DIO_GroupA,
    DIO_GroupB,
    DIO_GroupC,
    DIO_GroupD,
}DIO_Groups_t;

typedef enum
{
    DIO_Pin0,
    DIO_Pin1,
    DIO_Pin2,
    DIO_Pin3,
    DIO_Pin4,
    DIO_Pin5,
    DIO_Pin6,
    DIO_Pin7,
}DIO_Pins_t;

typedef enum
{
    DIO_Inputfor1Pin,
    DIO_Outputfor1Pin,
    DIO_Inputfor1Group=0x00,
    DIO_Outputfor1Group=0xFF,
}DIO_DirectionState_t;

typedef enum
{
    DIO_Lowfor1Pin,
    DIO_Highfor1Pin,
    DIO_Lowfor1Group=0x00,
    DIO_Highfor1Group=0xFF,
}DIO_OutputValue_t;

/* Function Prototypes */
void DIO_DirectionSelectforPin(const uint8_t GroupName, const uint8_t PinNo, const uint8_t DirectionState);
void DIO_DirectionSelectforGroup(const uint8_t GroupName, const uint8_t DirectionState);
void DIO_WritePin(const uint8_t GroupName, const uint8_t PinNo, const uint8_t OutputValue);
void DIO_WriteGroup(const uint8_t GroupName, const uint8_t OutputValue);
void DIO_ReadPin(const uint8_t GroupName, const uint8_t PinNo, uint8_t *InputState);
void DIO_ReadGroup(const uint8_t GroupName, uint8_t *InputState);
void DIO_TogglePin(const uint8_t GroupName, const uint8_t PinNo);
void DIO_ToggleGroup(const uint8_t GroupName);

#endif /* DIO_INTERFACE_H_ */