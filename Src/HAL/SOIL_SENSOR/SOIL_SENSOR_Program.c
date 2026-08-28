#include "SOIL_SENSOR_Interface.h"

#include <stddef.h>
#include <stdint.h>

void SOIL_SENSOR_Init(void)
{
    /*
     * Configure PA1 / ADC1 as input.
     */

    DIO_DirectionSelectforPin(
        SOIL_SENSOR_GROUP,
        SOIL_SENSOR_PIN,
        DIO_Inputfor1Pin);

    /*
     * Disable the internal pull-up resistor.
     */

    DIO_WritePin(
        SOIL_SENSOR_GROUP,
        SOIL_SENSOR_PIN,
        DIO_Lowfor1Pin);

    ADC_Init();
}

uint8_t SOIL_SENSOR_GetMoisture(
    uint8_t *MoisturePercentage)
{
    uint16_t ADCReading = 0U;
    uint32_t MoistureValue = 0UL;

    uint8_t ReadingStatus =
        SOIL_SENSOR_READING_ERROR;

    if(MoisturePercentage != NULL)
    {
        *MoisturePercentage =
            SOIL_SENSOR_MIN_PERCENTAGE;

        /*
         * Prevent division by zero or
         * invalid calibration values.
         */

        if(SOIL_SENSOR_DRY_VALUE >
           SOIL_SENSOR_WET_VALUE)
        {
            if(ADC_ReadChannel(
                   SOIL_SENSOR_ADC_CHANNEL,
                   &ADCReading) ==
               ADC_READING_OK)
            {
                if(ADCReading <=
                   SOIL_SENSOR_WET_VALUE)
                {
                    MoistureValue =
                        SOIL_SENSOR_MAX_PERCENTAGE;
                }
                else if(ADCReading >=
                        SOIL_SENSOR_DRY_VALUE)
                {
                    MoistureValue =
                        SOIL_SENSOR_MIN_PERCENTAGE;
                }
                else
                {
                    /*
                     * Convert ADC reading to:
                     * 0% Dry to 100% Wet.
                     */

                    MoistureValue =
                        ((uint32_t)
                         (SOIL_SENSOR_DRY_VALUE -
                          ADCReading) *
                         SOIL_SENSOR_MAX_PERCENTAGE) /
                        (SOIL_SENSOR_DRY_VALUE -
                         SOIL_SENSOR_WET_VALUE);
                }

                *MoisturePercentage =
                    (uint8_t)MoistureValue;

                ReadingStatus =
                    SOIL_SENSOR_READING_OK;
            }
        }
    }

    return ReadingStatus;
}