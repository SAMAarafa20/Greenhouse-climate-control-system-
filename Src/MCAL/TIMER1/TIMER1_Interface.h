#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include <stdint.h>

#include "../../Commen/BIT_MATH.h"

#include "TIMER1_Config.h"
#include "TIMER1_Private.h"

/*
 * Initialize Timer1 in CTC Mode.
 */

void TIMER1_Init(void);

/*
 * Start Timer1 using Prescaler 64.
 */

void TIMER1_Start(void);

/*
 * Stop Timer1.
 */

void TIMER1_Stop(void);

/*
 * Return elapsed time in milliseconds.
 */

uint32_t TIMER1_GetMilliseconds(void);

/*
 * Reset elapsed milliseconds.
 */

void TIMER1_ResetMilliseconds(void);

#endif /* TIMER1_INTERFACE_H_ */