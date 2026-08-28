#ifndef TEMP_SENSOR_PRIVATE_H_
#define TEMP_SENSOR_PRIVATE_H_

/*
 * ATmega32 ADC Resolution:
 * 10-bit = 1024 Levels
 */

#define TEMP_SENSOR_ADC_LEVELS          1024UL

/*
 * LM35 valid measurement range.
 */

#define TEMP_SENSOR_MAX_CELSIUS         150U

#endif /* TEMP_SENSOR_PRIVATE_H_ */