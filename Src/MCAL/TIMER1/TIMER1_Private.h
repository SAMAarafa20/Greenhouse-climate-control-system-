#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#include <stdint.h>

/*
 * ATmega32 Timer1 Registers
 * Data Memory Addresses
 */

#define TIMER1_TIFR_REG      *((volatile uint8_t  *)0x58U)
#define TIMER1_TIMSK_REG     *((volatile uint8_t  *)0x59U)

#define TIMER1_TCCR1A_REG    *((volatile uint8_t  *)0x4FU)
#define TIMER1_TCCR1B_REG    *((volatile uint8_t  *)0x4EU)

#define TIMER1_TCNT1H_REG    *((volatile uint8_t  *)0x4DU)
#define TIMER1_TCNT1L_REG    *((volatile uint8_t  *)0x4CU)

#define TIMER1_OCR1AH_REG    *((volatile uint8_t  *)0x4BU)
#define TIMER1_OCR1AL_REG    *((volatile uint8_t  *)0x4AU)

#define TIMER1_OCR1BH_REG    *((volatile uint8_t  *)0x49U)
#define TIMER1_OCR1BL_REG    *((volatile uint8_t  *)0x48U)

#define TIMER1_ICR1H_REG     *((volatile uint8_t  *)0x47U)
#define TIMER1_ICR1L_REG     *((volatile uint8_t  *)0x46U)

/* TCCR1A Bits */

#define TIMER1_COM1A1_BIT    7U
#define TIMER1_COM1A0_BIT    6U
#define TIMER1_COM1B1_BIT    5U
#define TIMER1_COM1B0_BIT    4U
#define TIMER1_FOC1A_BIT     3U
#define TIMER1_FOC1B_BIT     2U
#define TIMER1_WGM11_BIT     1U
#define TIMER1_WGM10_BIT     0U

/* TCCR1B Bits */

#define TIMER1_ICNC1_BIT     7U
#define TIMER1_ICES1_BIT     6U
#define TIMER1_WGM13_BIT     4U
#define TIMER1_WGM12_BIT     3U
#define TIMER1_CS12_BIT      2U
#define TIMER1_CS11_BIT      1U
#define TIMER1_CS10_BIT      0U

/* TIMSK Bits */

#define TIMER1_TICIE1_BIT    5U
#define TIMER1_OCIE1A_BIT    4U
#define TIMER1_OCIE1B_BIT    3U
#define TIMER1_TOIE1_BIT     2U

/*
 * ATmega32 Timer1 Compare Match A Interrupt:
 * Datasheet Vector Number = 7
 * avr-gcc Vector Symbol   = __vector_6
 */

#define TIMER1_COMPARE_MATCH_A_VECTOR    __vector_6

#endif /* TIMER1_PRIVATE_H_ */