#ifndef TEMP_SENSOR_INTERFACE_H_
#define TEMP_SENSOR_INTERFACE_H_

#include <stdint.h>

#include "TEMP_SENSOR_Config.h"
#include "TEMP_SENSOR_Private.h"

typedef enum
{
    TEMP_SENSOR_READING_ERROR = 0,
    TEMP_SENSOR_READING_OK

} TEMP_SENSOR_ReadingStatus_t;

/*
 * Initialize the ADC and configure
 * the LM35 pin as input.
 */

void TEMP_SENSOR_Init(void);

/*
 * Read temperature in degrees Celsius.
 *
 * Returns:
 * TEMP_SENSOR_READING_OK
 * TEMP_SENSOR_READING_ERROR
 */

uint8_t TEMP_SENSOR_GetTemperature(
    uint8_t *Temperature);

#endif /* TEMP_SENSOR_INTERFACE_H_ */