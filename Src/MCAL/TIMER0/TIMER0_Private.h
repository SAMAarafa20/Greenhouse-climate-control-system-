#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#include <stdint.h>

/* Timer0 Registers - ATmega32 Data Memory Addresses */

#define OCR0_REG     *((volatile uint8_t *)0x5CU)
#define TIMSK_REG    *((volatile uint8_t *)0x59U)
#define TIFR_REG     *((volatile uint8_t *)0x58U)
#define TCCR0_REG    *((volatile uint8_t *)0x53U)
#define TCNT0_REG    *((volatile uint8_t *)0x52U)

/* TCCR0 Bits */

#define TIMER0_FOC0_BIT     7U
#define TIMER0_WGM00_BIT    6U
#define TIMER0_COM01_BIT    5U
#define TIMER0_COM00_BIT    4U
#define TIMER0_WGM01_BIT    3U
#define TIMER0_CS02_BIT     2U
#define TIMER0_CS01_BIT     1U
#define TIMER0_CS00_BIT     0U

/* TIMSK Bits */

#define TIMER0_OCIE0_BIT    1U
#define TIMER0_TOIE0_BIT    0U

/* Timer0 Compare Match ISR */

#define TIMER0_COMPARE_MATCH_VECTOR    __vector_10

#endif /* TIMER0_PRIVATE_H_ */