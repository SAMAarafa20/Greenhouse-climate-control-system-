#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#include <stdint.h>

/*
 * ATmega32 External Interrupt Registers
 */

#define MCUCR_REG     (*((volatile uint8_t *)0x55))
#define MCUCSR_REG    (*((volatile uint8_t *)0x54))
#define GICR_REG      (*((volatile uint8_t *)0x5B))
#define GIFR_REG      (*((volatile uint8_t *)0x5A))

/*
 * MCUCR Register Bits
 * INT0 Sense Control
 */

#define MCUCR_ISC00    0U
#define MCUCR_ISC01    1U

/*
 * MCUCSR Register Bits
 */

#define MCUCSR_JTD     7U

/*
 * GICR Register Bits
 */

#define GICR_INT0      6U

/*
 * GIFR Register Bits
 */

#define GIFR_INTF0     6U

#endif /* EXTI_PRIVATE_H_ */