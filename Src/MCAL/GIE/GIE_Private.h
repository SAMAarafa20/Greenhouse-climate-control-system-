#ifndef GIE_PRIVATE_H_
#define GIE_PRIVATE_H_

#include <stdint.h>

/* ATmega32 Status Register */
#define SREG_REG    *((volatile uint8_t *)0x5FU)

/* Global Interrupt Enable Bit */
#define GIE_BIT     7U

#endif /* GIE_PRIVATE_H_ */