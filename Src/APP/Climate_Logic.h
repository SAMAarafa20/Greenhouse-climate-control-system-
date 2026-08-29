#ifndef CLIMATE_LOGIC_H_
#define CLIMATE_LOGIC_H_

#include "../Commen/DEFINITIONS.h"

/*
 * Default Automatic Thresholds
 */

#define DEFAULT_MIN_TEMPERATURE       18U
#define DEFAULT_MAX_TEMPERATURE       40U
#define DEFAULT_MIN_MOISTURE          35U

/*
 * Hysteresis Values
 */

#define TEMPERATURE_HYSTERESIS        2U
#define MOISTURE_HYSTERESIS           5U

/*
 * Critical Alarm Thresholds
 */

#define CRITICAL_HIGH_TEMP            50U
#define CRITICAL_LOW_TEMP             10U
#define CRITICAL_LOW_MOISTURE         10U

/*
 * Valid Sensor Ranges
 */

#define SENSOR_MAX_TEMPERATURE        100U
#define SENSOR_MAX_MOISTURE           100U

/*
 * Allowed Configuration Values
 */

#define MIN_CONFIG_TEMPERATURE        10U
#define MAX_CONFIG_TEMPERATURE        50U

#define MIN_CONFIG_MOISTURE           10U
#define MAX_CONFIG_MOISTURE           90U

#define MIN_TEMPERATURE_GAP           2U

/*
 * Actuator States
 */

#define CLIMATE_ACTUATOR_OFF          0U
#define CLIMATE_ACTUATOR_ON           1U

typedef enum
{
    MODE_STANDBY = 0,
    MODE_MANUAL,
    MODE_AUTOMATIC

} SystemMode_t;

typedef enum
{
    CLIMATE_OK = 0,
    CLIMATE_HIGH_TEMP,
    CLIMATE_LOW_TEMP,
    CLIMATE_LOW_MOISTURE,
    CLIMATE_CRITICAL_EMERGENCY,
    CLIMATE_SENSOR_ERROR

} SystemState_t;

typedef enum
{
    CLIMATE_PUMP = 0,
    CLIMATE_FAN,
    CLIMATE_HEATER

} ClimateActuator_t;

void Climate_vInit(void);

void Climate_vSetMode(
    SystemMode_t Local_tenuMode);

SystemMode_t Climate_tenuGetMode(void);

/*
 * Returns 1 when all values are valid.
 * Returns 0 when any value is invalid.
 */
u8 Climate_u8SetAutomaticThresholds(
    u8 Local_u8MinimumTemperature,
    u8 Local_u8MaximumTemperature,
    u8 Local_u8MinimumMoisture);

u8 Climate_u8GetMinimumTemperature(void);

u8 Climate_u8GetMaximumTemperature(void);

u8 Climate_u8GetMinimumMoisture(void);

/*
 * Manual actuator control is accepted
 * only while the system is in Manual Mode.
 */
void Climate_vSetManualActuator(
    ClimateActuator_t Local_tenuActuator,
    u8 Local_u8State);

u8 Climate_u8GetPumpState(void);

u8 Climate_u8GetFanState(void);

u8 Climate_u8GetHeaterState(void);

void Climate_vUpdateSystem(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture);

SystemState_t Climate_tenuGetState(void);

void Climate_vHandleSensorError(void);

void Climate_vStopSystem(void);

#endif /* CLIMATE_LOGIC_H_ */