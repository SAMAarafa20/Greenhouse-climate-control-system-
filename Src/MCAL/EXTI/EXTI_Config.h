#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*
 * INT0 Sense Control Options
 */

#define EXTI_LOW_LEVEL       0U
#define EXTI_ANY_CHANGE      1U
#define EXTI_FALLING_EDGE    2U
#define EXTI_RISING_EDGE     3U

/*
 * The mode button is connected between
 * PD2 / INT0 and GND using Internal Pull-up.
 *
 * Released -> HIGH
 * Pressed  -> Falling Edge
 */

#define EXTI_INT0_SENSE_CONTROL    EXTI_FALLING_EDGE

#endif /* EXTI_CONFIG_H_ */