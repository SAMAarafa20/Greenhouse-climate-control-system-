#include "Climate_Logic.h"

#include "../HAL/RELAY/RELAY_Interface.h"
#include "../HAL/BUZZER/BUZZER_Interface.h"

#include "../MCAL/TIMER0/TIMER0_Interface.h"

#include <stdint.h>

static SystemMode_t G_tenuSystemMode =
    MODE_STANDBY;

static SystemState_t G_tenuSystemState =
    CLIMATE_OK;

static u8 G_u8TargetTemperature =
    DEFAULT_TARGET_TEMP;

static u8 G_u8TargetMoisture =
    DEFAULT_TARGET_MOISTURE;

static u8 G_u8FanState = 0U;
static u8 G_u8HeaterState = 0U;
static u8 G_u8PumpState = 0U;

static u8 G_u8PumpCooldownActive = 0U;

static uint32_t G_u32PumpStartTime = 0UL;
static uint32_t G_u32PumpCooldownStartTime = 0UL;

static void Climate_vTurnFanOn(void)
{
    Relay_TurnOn(RELAY_FAN);

    G_u8FanState = 1U;
}

static void Climate_vTurnFanOff(void)
{
    Relay_TurnOff(RELAY_FAN);

    G_u8FanState = 0U;
}

static void Climate_vTurnHeaterOn(void)
{
    Relay_TurnOn(RELAY_HEATER);

    G_u8HeaterState = 1U;
}

static void Climate_vTurnHeaterOff(void)
{
    Relay_TurnOff(RELAY_HEATER);

    G_u8HeaterState = 0U;
}

static void Climate_vTurnPumpOn(void)
{
    /*
     * Do not start the pump during
     * its protection cooldown period.
     */

    if((G_u8PumpState == 0U) &&
       (G_u8PumpCooldownActive == 0U))
    {
        Relay_TurnOn(RELAY_PUMP);

        G_u8PumpState = 1U;

        G_u32PumpStartTime =
            TIMER0_GetMilliseconds();
    }
}

static void Climate_vTurnPumpOff(void)
{
    Relay_TurnOff(RELAY_PUMP);

    G_u8PumpState = 0U;
}

static void Climate_vResetPumpProtection(void)
{
    G_u8PumpCooldownActive = 0U;

    G_u32PumpStartTime = 0UL;
    G_u32PumpCooldownStartTime = 0UL;
}

static void Climate_vUpdatePumpProtection(void)
{
    uint32_t Local_u32CurrentTime;

    Local_u32CurrentTime =
        TIMER0_GetMilliseconds();

    /*
     * Stop the pump if it has operated
     * continuously for too long.
     */

    if(G_u8PumpState == 1U)
    {
        if((Local_u32CurrentTime -
            G_u32PumpStartTime) >=
           PUMP_MAX_RUN_TIME_MS)
        {
            Climate_vTurnPumpOff();

            G_u8PumpCooldownActive = 1U;

            G_u32PumpCooldownStartTime =
                Local_u32CurrentTime;
        }
    }

    /*
     * Allow the pump to start again
     * after the cooldown period.
     */

    if(G_u8PumpCooldownActive == 1U)
    {
        if((Local_u32CurrentTime -
            G_u32PumpCooldownStartTime) >=
           PUMP_COOLDOWN_TIME_MS)
        {
            G_u8PumpCooldownActive = 0U;
        }
    }
}

static void Climate_vUpdateAutomaticTemperature(
    u8 Local_u8Temperature)
{
    if(Local_u8Temperature >=
       AUTO_FAN_ON_TEMP)
    {
        Climate_vTurnFanOn();
        Climate_vTurnHeaterOff();
    }
    else if(Local_u8Temperature <=
            AUTO_HEATER_ON_TEMP)
    {
        Climate_vTurnFanOff();
        Climate_vTurnHeaterOn();
    }
    else
    {
        if((G_u8FanState == 1U) &&
           (Local_u8Temperature <=
            AUTO_FAN_OFF_TEMP))
        {
            Climate_vTurnFanOff();
        }

        if((G_u8HeaterState == 1U) &&
           (Local_u8Temperature >=
            AUTO_HEATER_OFF_TEMP))
        {
            Climate_vTurnHeaterOff();
        }
    }
}

static void Climate_vUpdateAutomaticMoisture(
    u8 Local_u8Moisture)
{
    if(Local_u8Moisture <=
       AUTO_PUMP_ON_MOISTURE)
    {
        Climate_vTurnPumpOn();
    }
    else if(Local_u8Moisture >=
            AUTO_PUMP_OFF_MOISTURE)
    {
        Climate_vTurnPumpOff();
    }
    else
    {
        /* Keep Previous Pump State */
    }
}

static void Climate_vUpdateManualTemperature(
    u8 Local_u8Temperature)
{
    /*
     * Example when target is 40:
     *
     * Fan ON at 42 and OFF at 40.
     * Heater ON at 38 and OFF at 40.
     */

    if(Local_u8Temperature >=
       (u8)(G_u8TargetTemperature +
            MANUAL_TEMP_TOLERANCE))
    {
        Climate_vTurnFanOn();
        Climate_vTurnHeaterOff();
    }
    else if((Local_u8Temperature +
             MANUAL_TEMP_TOLERANCE) <=
            G_u8TargetTemperature)
    {
        Climate_vTurnFanOff();
        Climate_vTurnHeaterOn();
    }
    else
    {
        if((G_u8FanState == 1U) &&
           (Local_u8Temperature <=
            G_u8TargetTemperature))
        {
            Climate_vTurnFanOff();
        }

        if((G_u8HeaterState == 1U) &&
           (Local_u8Temperature >=
            G_u8TargetTemperature))
        {
            Climate_vTurnHeaterOff();
        }
    }
}

static void Climate_vUpdateManualMoisture(
    u8 Local_u8Moisture)
{
    /*
     * Example when target is 50:
     *
     * Pump ON at 45 and OFF at 50.
     */

    if((Local_u8Moisture +
        MANUAL_MOIST_TOLERANCE) <=
       G_u8TargetMoisture)
    {
        Climate_vTurnPumpOn();
    }
    else if(Local_u8Moisture >=
            G_u8TargetMoisture)
    {
        Climate_vTurnPumpOff();
    }
    else
    {
        /* Keep Previous Pump State */
    }
}

static void Climate_vUpdateAlarm(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    if((Local_u8Temperature >=
        CRITICAL_HIGH_TEMP) ||
       (Local_u8Temperature <=
        CRITICAL_LOW_TEMP) ||
       (Local_u8Moisture <=
        CRITICAL_LOW_MOISTURE))
    {
        Buzzer_On();

        G_tenuSystemState =
            CLIMATE_CRITICAL_EMERGENCY;
    }
    else
    {
        Buzzer_Off();
    }
}

static void Climate_vUpdateAutomaticState(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    if(Local_u8Temperature >=
       AUTO_FAN_ON_TEMP)
    {
        G_tenuSystemState =
            CLIMATE_HIGH_TEMP;
    }
    else if(Local_u8Temperature <=
            AUTO_HEATER_ON_TEMP)
    {
        G_tenuSystemState =
            CLIMATE_LOW_TEMP;
    }
    else if(Local_u8Moisture <=
            AUTO_PUMP_ON_MOISTURE)
    {
        G_tenuSystemState =
            CLIMATE_LOW_MOISTURE;
    }
    else
    {
        G_tenuSystemState =
            CLIMATE_OK;
    }
}

static void Climate_vUpdateManualState(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    if(Local_u8Temperature >=
       (u8)(G_u8TargetTemperature +
            MANUAL_TEMP_TOLERANCE))
    {
        G_tenuSystemState =
            CLIMATE_HIGH_TEMP;
    }
    else if((Local_u8Temperature +
             MANUAL_TEMP_TOLERANCE) <=
            G_u8TargetTemperature)
    {
        G_tenuSystemState =
            CLIMATE_LOW_TEMP;
    }
    else if((Local_u8Moisture +
             MANUAL_MOIST_TOLERANCE) <=
            G_u8TargetMoisture)
    {
        G_tenuSystemState =
            CLIMATE_LOW_MOISTURE;
    }
    else
    {
        G_tenuSystemState =
            CLIMATE_OK;
    }
}

void Climate_vInit(void)
{
    G_tenuSystemMode =
        MODE_STANDBY;

    G_tenuSystemState =
        CLIMATE_OK;

    G_u8TargetTemperature =
        DEFAULT_TARGET_TEMP;

    G_u8TargetMoisture =
        DEFAULT_TARGET_MOISTURE;

    Climate_vResetPumpProtection();

    Climate_vStopSystem();
}

void Climate_vSetMode(
    SystemMode_t Local_tenuMode)
{
    if((Local_tenuMode == MODE_STANDBY) ||
       (Local_tenuMode == MODE_MANUAL) ||
       (Local_tenuMode == MODE_AUTOMATIC))
    {
        Climate_vStopSystem();

        G_tenuSystemMode =
            Local_tenuMode;
    }
    else
    {
        /* Invalid Mode */
    }
}

SystemMode_t Climate_tenuGetMode(void)
{
    return G_tenuSystemMode;
}

void Climate_vSetManualTargets(
    u8 Local_u8TargetTemperature,
    u8 Local_u8TargetMoisture)
{
    if((Local_u8TargetTemperature >=
        MIN_TARGET_TEMP) &&
       (Local_u8TargetTemperature <=
        MAX_TARGET_TEMP))
    {
        G_u8TargetTemperature =
            Local_u8TargetTemperature;
    }

    if((Local_u8TargetMoisture >=
        MIN_TARGET_MOISTURE) &&
       (Local_u8TargetMoisture <=
        MAX_TARGET_MOISTURE))
    {
        G_u8TargetMoisture =
            Local_u8TargetMoisture;
    }
}

u8 Climate_u8GetTargetTemperature(void)
{
    return G_u8TargetTemperature;
}

u8 Climate_u8GetTargetMoisture(void)
{
    return G_u8TargetMoisture;
}

void Climate_vUpdateSystem(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    if((Local_u8Temperature >
        SENSOR_MAX_TEMPERATURE) ||
       (Local_u8Moisture >
        SENSOR_MAX_MOISTURE))
    {
        Climate_vHandleSensorError();
    }
    else
    {
        G_tenuSystemState =
            CLIMATE_OK;

        Climate_vUpdatePumpProtection();

        if(G_tenuSystemMode ==
           MODE_AUTOMATIC)
        {
            Climate_vUpdateAutomaticTemperature(
                Local_u8Temperature);

            Climate_vUpdateAutomaticMoisture(
                Local_u8Moisture);

            Climate_vUpdateAlarm(
                Local_u8Temperature,
                Local_u8Moisture);

            if(G_tenuSystemState !=
               CLIMATE_CRITICAL_EMERGENCY)
            {
                Climate_vUpdateAutomaticState(
                    Local_u8Temperature,
                    Local_u8Moisture);
            }
        }
        else if(G_tenuSystemMode ==
                MODE_MANUAL)
        {
            Climate_vUpdateManualTemperature(
                Local_u8Temperature);

            Climate_vUpdateManualMoisture(
                Local_u8Moisture);

            Climate_vUpdateAlarm(
                Local_u8Temperature,
                Local_u8Moisture);

            if(G_tenuSystemState !=
               CLIMATE_CRITICAL_EMERGENCY)
            {
                Climate_vUpdateManualState(
                    Local_u8Temperature,
                    Local_u8Moisture);
            }
        }
        else
        {
            Climate_vStopSystem();
        }

        /*
         * Check again because the pump may
         * have started during this update.
         */

        Climate_vUpdatePumpProtection();
    }
}

SystemState_t Climate_tenuGetState(void)
{
    return G_tenuSystemState;
}

void Climate_vHandleSensorError(void)
{
    Climate_vTurnFanOff();
    Climate_vTurnHeaterOff();
    Climate_vTurnPumpOff();

    Climate_vResetPumpProtection();

    Buzzer_On();

    G_tenuSystemState =
        CLIMATE_SENSOR_ERROR;
}

void Climate_vStopSystem(void)
{
    Climate_vTurnFanOff();
    Climate_vTurnHeaterOff();
    Climate_vTurnPumpOff();

    Climate_vResetPumpProtection();

    Buzzer_Off();

    G_tenuSystemState =
        CLIMATE_OK;
}