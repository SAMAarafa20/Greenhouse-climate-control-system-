#ifndef SOIL_SENSOR_INTERFACE_H_
#define SOIL_SENSOR_INTERFACE_H_

#include <stdint.h>

#include "SOIL_SENSOR_Config.h"
#include "SOIL_SENSOR_Private.h"

typedef enum
{
    SOIL_SENSOR_READING_ERROR = 0,
    SOIL_SENSOR_READING_OK

} SOIL_SENSOR_ReadingStatus_t;

/*
 * Initialize the ADC and configure
 * the soil sensor pin as input.
 */

void SOIL_SENSOR_Init(void);

/*
 * Read soil moisture percentage.
 *
 * 0%   = Completely Dry
 * 100% = Completely Wet
 *
 * Returns:
 * SOIL_SENSOR_READING_OK
 * SOIL_SENSOR_READING_ERROR
 */

uint8_t SOIL_SENSOR_GetMoisture(
    uint8_t *MoisturePercentage);

#endif /* SOIL_SENSOR_INTERFACE_H_ */