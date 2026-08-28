#ifndef TEMP_SENSOR_CONFIG_H_
#define TEMP_SENSOR_CONFIG_H_

#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

/*
 * LM35 Output Pin:
 * PA0 / ADC0
 */

#define TEMP_SENSOR_GROUP              DIO_GroupA
#define TEMP_SENSOR_PIN                DIO_Pin0
#define TEMP_SENSOR_ADC_CHANNEL        ADC_Channel0

/*
 * AVCC Reference Voltage = 5000 mV
 *
 * LM35 Sensitivity:
 * 10 mV for every 1 degree Celsius.
 */

#define TEMP_SENSOR_REFERENCE_MV       5000UL
#define TEMP_SENSOR_MV_PER_CELSIUS     10UL

#endif /* TEMP_SENSOR_CONFIG_H_ */