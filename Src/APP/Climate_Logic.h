#ifndef CLIMATE_LOGIC_H
#define CLIMATE_LOGIC_H

#include "../Commen/DEFINITIONS.h"

/* Automatic Temperature Hysteresis */

#define AUTO_FAN_ON_TEMP               40U
#define AUTO_FAN_OFF_TEMP              35U

#define AUTO_HEATER_ON_TEMP            18U
#define AUTO_HEATER_OFF_TEMP           22U

/* Automatic Moisture Hysteresis */

#define AUTO_PUMP_ON_MOISTURE          35U
#define AUTO_PUMP_OFF_MOISTURE         55U

/* Critical Alarm Thresholds */

#define CRITICAL_HIGH_TEMP             50U
#define CRITICAL_LOW_TEMP              10U
#define CRITICAL_LOW_MOISTURE          10U

/* Sensor Valid Ranges */

#define SENSOR_MAX_TEMPERATURE         100U
#define SENSOR_MAX_MOISTURE            100U

/* Default Manual Targets */

#define DEFAULT_TARGET_TEMP            25U
#define DEFAULT_TARGET_MOISTURE        50U

/* Manual Hysteresis */

#define MANUAL_TEMP_TOLERANCE          2U
#define MANUAL_MOIST_TOLERANCE         5U

/* Allowed Manual Targets */

#define MIN_TARGET_TEMP                10U
#define MAX_TARGET_TEMP                50U

#define MIN_TARGET_MOISTURE            10U
#define MAX_TARGET_MOISTURE            90U

/*
 * Pump Safety Times.
 *
 * Maximum continuous operation = 10 seconds.
 * Cooldown before restart      = 5 seconds.
 *
 * Values are short for Proteus testing
 * and can be changed later.
 */

#define PUMP_MAX_RUN_TIME_MS           10000UL
#define PUMP_COOLDOWN_TIME_MS          5000UL

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

void Climate_vInit(void);

void Climate_vSetMode(
    SystemMode_t Local_tenuMode);

SystemMode_t Climate_tenuGetMode(void);

void Climate_vSetManualTargets(
    u8 Local_u8TargetTemperature,
    u8 Local_u8TargetMoisture);

u8 Climate_u8GetTargetTemperature(void);

u8 Climate_u8GetTargetMoisture(void);

void Climate_vUpdateSystem(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture);

SystemState_t Climate_tenuGetState(void);

void Climate_vHandleSensorError(void);

void Climate_vStopSystem(void);

#endif /* CLIMATE_LOGIC_H */