#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include <stdint.h>

/*
 * Initializes INT0 sense control.
 */
void EXTI_INT0_Init(void);

/*
 * Enables INT0 interrupt.
 */
void EXTI_INT0_Enable(void);

/*
 * Disables INT0 interrupt.
 */
void EXTI_INT0_Disable(void);

/*
 * Sets the function called when
 * the INT0 interrupt occurs.
 */
uint8_t EXTI_INT0_SetCallback(
    void (*CallbackFunction)(void));

#endif /* EXTI_INTERFACE_H_ */