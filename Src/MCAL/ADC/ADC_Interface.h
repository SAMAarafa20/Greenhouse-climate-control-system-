#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include <stdint.h>

typedef enum
{
    ADC_Channel0 = 0,
    ADC_Channel1,
    ADC_Channel2,
    ADC_Channel3,
    ADC_Channel4,
    ADC_Channel5,
    ADC_Channel6,
    ADC_Channel7

} ADC_Channel_t;

typedef enum
{
    ADC_READING_ERROR = 0,
    ADC_READING_OK

} ADC_ReadingStatus_t;

void ADC_Init(void);

/*
 * Returns:
 *
 * ADC_READING_OK:
 * Conversion completed successfully.
 *
 * ADC_READING_ERROR:
 * Invalid channel, null pointer,
 * or ADC conversion timeout.
 */
uint8_t ADC_ReadChannel(uint8_t Channel,
                        uint16_t *Reading);

#endif /* ADC_INTERFACE_H */