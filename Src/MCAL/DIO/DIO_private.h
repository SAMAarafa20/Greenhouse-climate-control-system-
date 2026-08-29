#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include <stdint.h>

/*
 * ATmega32 Port A Registers
 */

#define PORTA_REG    (*((volatile uint8_t *)0x3B))
#define DDRA_REG     (*((volatile uint8_t *)0x3A))
#define PINA_REG     (*((volatile uint8_t *)0x39))

/*
 * ATmega32 Port B Registers
 */

#define PORTB_REG    (*((volatile uint8_t *)0x38))
#define DDRB_REG     (*((volatile uint8_t *)0x37))
#define PINB_REG     (*((volatile uint8_t *)0x36))

/*
 * ATmega32 Port C Registers
 */

#define PORTC_REG    (*((volatile uint8_t *)0x35))
#define DDRC_REG     (*((volatile uint8_t *)0x34))
#define PINC_REG     (*((volatile uint8_t *)0x33))

/*
 * ATmega32 Port D Registers
 */

#define PORTD_REG    (*((volatile uint8_t *)0x32))
#define DDRD_REG     (*((volatile uint8_t *)0x31))
#define PIND_REG     (*((volatile uint8_t *)0x30))

/*
 * JTAG Disable Registers
 */

#define DIO_MCUCSR_REG    \
    (*((volatile uint8_t *)0x54))

#define DIO_SREG_REG      \
    (*((volatile uint8_t *)0x5F))

#define DIO_JTD_BIT                   7U
#define DIO_GLOBAL_INTERRUPT_BIT      7U

#endif /* DIO_PRIVATE_H_ */