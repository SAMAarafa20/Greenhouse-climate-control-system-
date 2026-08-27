#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*
 * ADC Reference Voltage:
 *
 * ADC_REFERENCE_AREF
 * ADC_REFERENCE_AVCC
 * ADC_REFERENCE_INTERNAL
 */
#define ADC_REFERENCE_VOLTAGE    ADC_REFERENCE_AVCC

/*
 * ATmega32 Clock = 8 MHz
 * ADC Prescaler  = 64
 * ADC Clock      = 125 kHz
 */
#define ADC_PRESCALER             ADC_PRESCALER_64

/*
 * Prevent infinite waiting if the ADC
 * conversion does not finish.
 */
#define ADC_TIMEOUT_COUNT         50000UL

#endif /* ADC_CONFIG_H */