#include "TIMER0_Interface.h"

#include "../GIE/GIE_Interface.h"

/*
 * Counts the elapsed time in milliseconds.
 * volatile because its value changes inside ISR.
 */
static volatile uint32_t TIMER0_Milliseconds = 0UL;

void TIMER0_Init(void)
{
    /*
     * Stop Timer0 before configuration.
     * CS02:CS00 = 000
     */
    ClearBit(TCCR0_REG, TIMER0_CS02_BIT);
    ClearBit(TCCR0_REG, TIMER0_CS01_BIT);
    ClearBit(TCCR0_REG, TIMER0_CS00_BIT);

    /*
     * Select CTC Mode.
     * WGM01 = 1
     * WGM00 = 0
     */
    SetBit(TCCR0_REG, TIMER0_WGM01_BIT);
    ClearBit(TCCR0_REG, TIMER0_WGM00_BIT);

    /*
     * Disconnect OC0 Pin.
     * COM01:COM00 = 00
     */
    ClearBit(TCCR0_REG, TIMER0_COM01_BIT);
    ClearBit(TCCR0_REG, TIMER0_COM00_BIT);

    /*
     * Start counting from zero.
     */
    TCNT0_REG = 0U;

    /*
     * Compare Match every 1 ms.
     */
    OCR0_REG = TIMER0_COMPARE_MATCH_VALUE;

    /*
     * Enable Timer0 Compare Match Interrupt.
     */
    SetBit(TIMSK_REG, TIMER0_OCIE0_BIT);

    TIMER0_Milliseconds = 0UL;
}

void TIMER0_Start(void)
{
    /*
     * Prescaler = 64
     * CS02:CS00 = 011
     */
    ClearBit(TCCR0_REG, TIMER0_CS02_BIT);
    SetBit(TCCR0_REG, TIMER0_CS01_BIT);
    SetBit(TCCR0_REG, TIMER0_CS00_BIT);
}

void TIMER0_Stop(void)
{
    /*
     * No Clock Source.
     * CS02:CS00 = 000
     */
    ClearBit(TCCR0_REG, TIMER0_CS02_BIT);
    ClearBit(TCCR0_REG, TIMER0_CS01_BIT);
    ClearBit(TCCR0_REG, TIMER0_CS00_BIT);
}

uint32_t TIMER0_GetMilliseconds(void)
{
    uint32_t LocalMilliseconds;
    uint8_t LocalSREG;

    /*
     * Save the current SREG state, then temporarily disable
     * interrupts while reading the 32-bit variable.
     */
    LocalSREG = SREG_REG;

    GIE_Disable();

    LocalMilliseconds = TIMER0_Milliseconds;

    /*
     * Restore SREG exactly as it was.
     */
    SREG_REG = LocalSREG;

    return LocalMilliseconds;
}

void TIMER0_ResetMilliseconds(void)
{
    uint8_t LocalSREG;

    LocalSREG = SREG_REG;

    GIE_Disable();

    TIMER0_Milliseconds = 0UL;

    SREG_REG = LocalSREG;
}

/*
 * Timer0 Compare Match Interrupt Service Routine.
 * Datasheet Vector Number 11 = GCC __vector_10.
 */
void TIMER0_COMPARE_MATCH_VECTOR(void) __attribute__((signal));

void TIMER0_COMPARE_MATCH_VECTOR(void)
{
    TIMER0_Milliseconds++;
}