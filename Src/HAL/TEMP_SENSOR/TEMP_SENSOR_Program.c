#include "TEMP_SENSOR_Interface.h"

#include <stddef.h>
#include <stdint.h>

void TEMP_SENSOR_Init(void)
{
    /*
     * Configure PA0 / ADC0 as input.
     */

    DIO_DirectionSelectforPin(
        TEMP_SENSOR_GROUP,
        TEMP_SENSOR_PIN,
        DIO_Inputfor1Pin);

    /*
     * Disable the internal pull-up resistor.
     */

    DIO_WritePin(
        TEMP_SENSOR_GROUP,
        TEMP_SENSOR_PIN,
        DIO_Lowfor1Pin);

    ADC_Init();
}

uint8_t TEMP_SENSOR_GetTemperature(
    uint8_t *Temperature)
{
    uint16_t ADCReading = 0U;
    uint32_t SensorVoltageMv = 0UL;
    uint32_t TemperatureValue = 0UL;

    uint8_t ReadingStatus =
        TEMP_SENSOR_READING_ERROR;

    if(Temperature != NULL)
    {
        *Temperature = 0U;

        if(ADC_ReadChannel(
               TEMP_SENSOR_ADC_CHANNEL,
               &ADCReading) ==
           ADC_READING_OK)
        {
            /*
             * Convert ADC reading to millivolts:
             *
             * Voltage =
             * ADCReading * 5000 / 1024
             */

            SensorVoltageMv =
                ((uint32_t)ADCReading *
                 TEMP_SENSOR_REFERENCE_MV) /
                TEMP_SENSOR_ADC_LEVELS;

            /*
             * LM35:
             * Temperature = Voltage / 10
             */

            TemperatureValue =
                SensorVoltageMv /
                TEMP_SENSOR_MV_PER_CELSIUS;

            /*
             * Reject readings outside
             * the LM35 measurement range.
             */

            if(TemperatureValue <=
               TEMP_SENSOR_MAX_CELSIUS)
            {
                *Temperature =
                    (uint8_t)TemperatureValue;

                ReadingStatus =
                    TEMP_SENSOR_READING_OK;
            }
            else
            {
                ReadingStatus =
                    TEMP_SENSOR_READING_ERROR;
            }
        }
    }

    return ReadingStatus;
}