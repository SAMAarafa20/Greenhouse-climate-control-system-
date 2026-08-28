#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include <stdint.h>

#include "../../Commen/BIT_MATH.h"

#include "TIMER0_Config.h"
#include "TIMER0_Private.h"

/*
 * Initializes Timer0 in CTC mode.
 * Compare Match occurs every 1 ms.
 */
void TIMER0_Init(void);

/*
 * Starts Timer0 using Prescaler = 64.
 */
void TIMER0_Start(void);

/*
 * Stops Timer0 without clearing elapsed time.
 */
void TIMER0_Stop(void);

/*
 * Returns elapsed time in milliseconds.
 */
uint32_t TIMER0_GetMilliseconds(void);

/*
 * Resets elapsed milliseconds to zero.
 */
void TIMER0_ResetMilliseconds(void);

#endif /* TIMER0_INTERFACE_H_ */