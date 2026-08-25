#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include <stdint.h>

/* Group A Registers */
#define PORTA   *((volatile uint8_t*)0x3B)
#define DDRA    *((volatile uint8_t*)0x3A)
#define PINA    *((volatile uint8_t*)0x39)

/* Group B Registers */
#define PORTB   *((volatile uint8_t*)0x38)
#define DDRB    *((volatile uint8_t*)0x37)
#define PINB    *((volatile uint8_t*)0x36)

/* Group C Registers */
#define PORTC   *((volatile uint8_t*)0x35)
#define DDRC    *((volatile uint8_t*)0x34)
#define PINC    *((volatile uint8_t*)0x33)

/* Group D Registers */
#define PORTD   *((volatile uint8_t*)0x32)
#define DDRD    *((volatile uint8_t*)0x31)
#define PIND    *((volatile uint8_t*)0x30)

#endif /* DIO_PRIVATE_H_ */