#include "TIMER1_Interface.h"

#include "../GIE/GIE_Interface.h"

/*
 * Incremented every 1 millisecond
 * inside Timer1 Compare Match A ISR.
 */

static volatile uint32_t TIMER1_Milliseconds = 0UL;

static void TIMER1_SetCounterValue(uint16_t CounterValue)
{
    /*
     * For 16-bit register access:
     * Write High Byte first, then Low Byte.
     */

    TIMER1_TCNT1H_REG =
        (uint8_t)(CounterValue >> 8U);

    TIMER1_TCNT1L_REG =
        (uint8_t)(CounterValue & 0x00FFU);
}

static void TIMER1_SetCompareAValue(uint16_t CompareValue)
{
    /*
     * For 16-bit register access:
     * Write High Byte first, then Low Byte.
     */

    TIMER1_OCR1AH_REG =
        (uint8_t)(CompareValue >> 8U);

    TIMER1_OCR1AL_REG =
        (uint8_t)(CompareValue & 0x00FFU);
}

void TIMER1_Init(void)
{
    /*
     * Stop Timer1 before configuration.
     * CS12:CS10 = 000
     */

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS12_BIT);

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS11_BIT);

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS10_BIT);

    /*
     * Select CTC Mode:
     *
     * WGM13 = 0
     * WGM12 = 1
     * WGM11 = 0
     * WGM10 = 0
     *
     * TOP = OCR1A
     */

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_WGM13_BIT);

    SetBit(TIMER1_TCCR1B_REG,
           TIMER1_WGM12_BIT);

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_WGM11_BIT);

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_WGM10_BIT);

    /*
     * Normal Port Operation.
     * OC1A and OC1B are disconnected.
     */

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_COM1A1_BIT);

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_COM1A0_BIT);

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_COM1B1_BIT);

    ClearBit(TIMER1_TCCR1A_REG,
             TIMER1_COM1B0_BIT);

    /*
     * Reset Timer1 counter.
     */

    TIMER1_SetCounterValue(0U);

    /*
     * Compare Match every 1 millisecond.
     */

    TIMER1_SetCompareAValue(
        TIMER1_COMPARE_MATCH_VALUE);

    /*
     * Enable Timer1 Compare Match A Interrupt.
     */

    SetBit(TIMER1_TIMSK_REG,
           TIMER1_OCIE1A_BIT);

    TIMER1_Milliseconds = 0UL;
}

void TIMER1_Start(void)
{
    /*
     * Start Timer1 using Prescaler 64.
     *
     * CS12 = 0
     * CS11 = 1
     * CS10 = 1
     */

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS12_BIT);

    SetBit(TIMER1_TCCR1B_REG,
           TIMER1_CS11_BIT);

    SetBit(TIMER1_TCCR1B_REG,
           TIMER1_CS10_BIT);
}

void TIMER1_Stop(void)
{
    /*
     * Stop Timer1:
     * CS12:CS10 = 000
     */

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS12_BIT);

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS11_BIT);

    ClearBit(TIMER1_TCCR1B_REG,
             TIMER1_CS10_BIT);
}

uint32_t TIMER1_GetMilliseconds(void)
{
    uint32_t LocalMilliseconds;
    uint8_t LocalSREG;

    /*
     * Protect the 32-bit variable because
     * ATmega32 is an 8-bit microcontroller.
     */

    LocalSREG = SREG_REG;

    GIE_Disable();

    LocalMilliseconds =
        TIMER1_Milliseconds;

    /*
     * Restore the previous interrupt state.
     */

    SREG_REG = LocalSREG;

    return LocalMilliseconds;
}

void TIMER1_ResetMilliseconds(void)
{
    uint8_t LocalSREG;

    LocalSREG = SREG_REG;

    GIE_Disable();

    TIMER1_Milliseconds = 0UL;

    /*
     * Restore the previous interrupt state.
     */

    SREG_REG = LocalSREG;
}

/*
 * Timer1 Compare Match A ISR
 */

void TIMER1_COMPARE_MATCH_A_VECTOR(void)
    __attribute__((signal));

void TIMER1_COMPARE_MATCH_A_VECTOR(void)
{
    TIMER1_Milliseconds++;
}