#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

#include "../../Commen/BIT_MATH.h"

#include <stddef.h>
#include <stdint.h>

void ADC_Init(void)
{
    /*
     * Select ADC Reference Voltage.
     */
    if(ADC_REFERENCE_VOLTAGE ==
       ADC_REFERENCE_AREF)
    {
        ClearBit(ADMUX_REG, ADMUX_REFS0);
        ClearBit(ADMUX_REG, ADMUX_REFS1);
    }
    else if(ADC_REFERENCE_VOLTAGE ==
            ADC_REFERENCE_AVCC)
    {
        SetBit(ADMUX_REG, ADMUX_REFS0);
        ClearBit(ADMUX_REG, ADMUX_REFS1);
    }
    else if(ADC_REFERENCE_VOLTAGE ==
            ADC_REFERENCE_INTERNAL)
    {
        SetBit(ADMUX_REG, ADMUX_REFS0);
        SetBit(ADMUX_REG, ADMUX_REFS1);
    }
    else
    {
        /* Invalid Reference Configuration */
    }

    /*
     * Right-adjust the 10-bit ADC result.
     */
    ClearBit(ADMUX_REG, ADMUX_ADLAR);

    /*
     * Configure ADC Prescaler.
     */
    ADCSRA_REG =
        (uint8_t)((ADCSRA_REG & 0xF8U) |
                  ADC_PRESCALER);

    /*
     * Use Single Conversion Mode.
     */
    ClearBit(ADCSRA_REG, ADCSRA_ADATE);

    /*
     * Disable ADC Interrupt.
     */
    ClearBit(ADCSRA_REG, ADCSRA_ADIE);

    /*
     * Enable ADC.
     */
    SetBit(ADCSRA_REG, ADCSRA_ADEN);
}

uint8_t ADC_ReadChannel(uint8_t Channel,
                        uint16_t *Reading)
{
    uint8_t ReadingStatus =
        ADC_READING_ERROR;

    uint8_t LowByte = 0;
    uint8_t HighByte = 0;

    uint32_t TimeoutCounter = 0UL;

    if((Channel <= ADC_MAX_CHANNEL) &&
       (Reading != NULL))
    {
        /*
         * Initialize output to a safe value.
         */
        *Reading = 0U;

        /*
         * Keep ADMUX upper bits and select
         * the requested ADC channel.
         */
        ADMUX_REG =
            (uint8_t)((ADMUX_REG &
                       ADC_CHANNEL_MASK) |
                      Channel);

        /*
         * Start ADC conversion.
         */
        SetBit(ADCSRA_REG, ADCSRA_ADSC);

        /*
         * Wait for conversion with timeout.
         */
        while((ReadBit(ADCSRA_REG,
                       ADCSRA_ADSC) == 1U) &&
              (TimeoutCounter <
               ADC_TIMEOUT_COUNT))
        {
            TimeoutCounter++;
        }

        if(TimeoutCounter <
           ADC_TIMEOUT_COUNT)
        {
            /*
             * ADCL must be read before ADCH.
             */
            LowByte = ADCL_REG;
            HighByte = ADCH_REG;

            *Reading =
                (uint16_t)LowByte |
                ((uint16_t)HighByte << 8U);

            ReadingStatus =
                ADC_READING_OK;
        }
        else
        {
            /*
             * Recover ADC after timeout.
             */
            ClearBit(ADCSRA_REG,
                     ADCSRA_ADEN);

            SetBit(ADCSRA_REG,
                   ADCSRA_ADEN);

            ReadingStatus =
                ADC_READING_ERROR;
        }
    }
    else
    {
        /* Invalid Channel or Null Pointer */
    }

    return ReadingStatus;
}