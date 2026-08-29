#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

#include "../../Commen/BIT_MATH.h"

#include <avr/interrupt.h>
#include <stddef.h>

static void (*EXTI_INT0_Callback)(void) =
    NULL;

void EXTI_INT0_Init(void)
{
    /*
     * Disable INT0 while configuring it.
     */
    ClearBit(GICR_REG, GICR_INT0);

#if EXTI_INT0_SENSE_CONTROL == EXTI_LOW_LEVEL

    ClearBit(MCUCR_REG, MCUCR_ISC00);
    ClearBit(MCUCR_REG, MCUCR_ISC01);

#elif EXTI_INT0_SENSE_CONTROL == EXTI_ANY_CHANGE

    SetBit(MCUCR_REG, MCUCR_ISC00);
    ClearBit(MCUCR_REG, MCUCR_ISC01);

#elif EXTI_INT0_SENSE_CONTROL == EXTI_FALLING_EDGE

    ClearBit(MCUCR_REG, MCUCR_ISC00);
    SetBit(MCUCR_REG, MCUCR_ISC01);

#elif EXTI_INT0_SENSE_CONTROL == EXTI_RISING_EDGE

    SetBit(MCUCR_REG, MCUCR_ISC00);
    SetBit(MCUCR_REG, MCUCR_ISC01);

#else

#error "Invalid INT0 sense control configuration"

#endif

    /*
     * Clear any pending INT0 interrupt flag
     * by writing logic one to INTF0.
     */
    GIFR_REG =
        (uint8_t)(1U << GIFR_INTF0);
}

void EXTI_INT0_Enable(void)
{
    GIFR_REG =
        (uint8_t)(1U << GIFR_INTF0);

    SetBit(GICR_REG, GICR_INT0);
}

void EXTI_INT0_Disable(void)
{
    ClearBit(GICR_REG, GICR_INT0);
}

uint8_t EXTI_INT0_SetCallback(
    void (*CallbackFunction)(void))
{
    uint8_t Local_u8Status = 0U;

    if(CallbackFunction != NULL)
    {
        EXTI_INT0_Callback =
            CallbackFunction;

        Local_u8Status = 1U;
    }
    else
    {
        /* Invalid Callback */
    }

    return Local_u8Status;
}

ISR(INT0_vect)
{
    if(EXTI_INT0_Callback != NULL)
    {
        EXTI_INT0_Callback();
    }
    else
    {
        /* Callback is not configured */
    }
}