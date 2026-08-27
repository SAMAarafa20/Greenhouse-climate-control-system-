#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include <stdint.h>

/* ATmega32 ADC Registers */

#define ADMUX_REG    (*((volatile uint8_t *)0x27))
#define ADCSRA_REG   (*((volatile uint8_t *)0x26))
#define ADCH_REG     (*((volatile uint8_t *)0x25))
#define ADCL_REG     (*((volatile uint8_t *)0x24))

/* ADMUX Bits */

#define ADMUX_MUX0      0U
#define ADMUX_MUX1      1U
#define ADMUX_MUX2      2U
#define ADMUX_MUX3      3U
#define ADMUX_MUX4      4U
#define ADMUX_ADLAR     5U
#define ADMUX_REFS0     6U
#define ADMUX_REFS1     7U

/* ADCSRA Bits */

#define ADCSRA_ADPS0    0U
#define ADCSRA_ADPS1    1U
#define ADCSRA_ADPS2    2U
#define ADCSRA_ADIE     3U
#define ADCSRA_ADIF     4U
#define ADCSRA_ADATE    5U
#define ADCSRA_ADSC     6U
#define ADCSRA_ADEN     7U

/* Reference Voltage Options */

#define ADC_REFERENCE_AREF        0U
#define ADC_REFERENCE_AVCC        1U
#define ADC_REFERENCE_INTERNAL    3U

/* Prescaler Options */

#define ADC_PRESCALER_2           1U
#define ADC_PRESCALER_4           2U
#define ADC_PRESCALER_8           3U
#define ADC_PRESCALER_16          4U
#define ADC_PRESCALER_32          5U
#define ADC_PRESCALER_64          6U
#define ADC_PRESCALER_128         7U

#define ADC_CHANNEL_MASK          0xE0U
#define ADC_MAX_CHANNEL           7U

#endif /* ADC_PRIVATE_H */