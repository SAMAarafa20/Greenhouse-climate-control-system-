#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/*
 * System Clock = 8 MHz
 * Prescaler    = 64
 * Timer Tick   = 8 us
 * Compare Match every 1 ms
 *
 * OCR0 = 124
 */

#define TIMER0_COMPARE_MATCH_VALUE    124U

#endif /* TIMER0_CONFIG_H_ */