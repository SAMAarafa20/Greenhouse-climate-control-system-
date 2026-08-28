#ifndef SOIL_SENSOR_CONFIG_H_
#define SOIL_SENSOR_CONFIG_H_

#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

/*
 * Soil Moisture Sensor Analog Pin:
 * PA1 / ADC1
 */

#define SOIL_SENSOR_GROUP              DIO_GroupA
#define SOIL_SENSOR_PIN                DIO_Pin1
#define SOIL_SENSOR_ADC_CHANNEL        ADC_Channel1

/*
 * Initial calibration values.
 *
 * ADC = 0    means completely wet.
 * ADC = 1023 means completely dry.
 *
 * These values can be changed later
 * after testing the real sensor.
 */

#define SOIL_SENSOR_WET_VALUE          0U
#define SOIL_SENSOR_DRY_VALUE          1023U

#endif /* SOIL_SENSOR_CONFIG_H_ */