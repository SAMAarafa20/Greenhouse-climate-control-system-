#include "Climate_Logic.h"

#include "../HAL/BUZZER/BUZZER_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/LED/LED_Config.h"
#include "../HAL/RELAY/RELAY_Interface.h"

static SystemMode_t G_tenuSystemMode =
    MODE_STANDBY;

static SystemState_t G_tenuSystemState =
    CLIMATE_OK;

static u8 G_u8MinimumTemperature =
    DEFAULT_MIN_TEMPERATURE;

static u8 G_u8MaximumTemperature =
    DEFAULT_MAX_TEMPERATURE;

static u8 G_u8MinimumMoisture =
    DEFAULT_MIN_MOISTURE;

static u8 G_u8FanState = 0U;
static u8 G_u8HeaterState = 0U;
static u8 G_u8PumpState = 0U;

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
    Relay_TurnOn(RELAY_PUMP);
    G_u8PumpState = 1U;
}

static void Climate_vTurnPumpOff(void)
{
    Relay_TurnOff(RELAY_PUMP);
    G_u8PumpState = 0U;
}

static void Climate_vTurnAlarmOn(void)
{
    Buzzer_On();

    Led_On(
        ALARM_LED_GROUP,
        ALARM_LED_PIN,
        ALARM_LED_CONNECTION_TYPE);
}

static void Climate_vTurnAlarmOff(void)
{
    Buzzer_Off();

    Led_Off(
        ALARM_LED_GROUP,
        ALARM_LED_PIN,
        ALARM_LED_CONNECTION_TYPE);
}

static void Climate_vUpdateAutomaticTemperature(
    u8 Local_u8Temperature)
{
    if(Local_u8Temperature >=
       G_u8MaximumTemperature)
    {
        Climate_vTurnHeaterOff();
        Climate_vTurnFanOn();
    }
    else if(Local_u8Temperature <=
            G_u8MinimumTemperature)
    {
        Climate_vTurnFanOff();
        Climate_vTurnHeaterOn();
    }
    else
    {
        /*
         * Fan remains ON until temperature
         * falls below its OFF threshold.
         */
        if((G_u8FanState == 1U) &&
           (Local_u8Temperature <=
            (u8)(G_u8MaximumTemperature -
                 TEMPERATURE_HYSTERESIS)))
        {
            Climate_vTurnFanOff();
        }

        /*
         * Heater remains ON until temperature
         * rises above its OFF threshold.
         */
        if((G_u8HeaterState == 1U) &&
           (Local_u8Temperature >=
            (u8)(G_u8MinimumTemperature +
                 TEMPERATURE_HYSTERESIS)))
        {
            Climate_vTurnHeaterOff();
        }
    }
}

static void Climate_vUpdateAutomaticMoisture(
    u8 Local_u8Moisture)
{
    if(Local_u8Moisture <=
       G_u8MinimumMoisture)
    {
        Climate_vTurnPumpOn();
    }
    else if(Local_u8Moisture >=
            (u8)(G_u8MinimumMoisture +
                 MOISTURE_HYSTERESIS))
    {
        Climate_vTurnPumpOff();
    }
    else
    {
        /* Keep Previous Pump State */
    }
}

static u8 Climate_u8UpdateAlarm(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    u8 Local_u8CriticalState = 0U;

    if((Local_u8Temperature >=
        CRITICAL_HIGH_TEMP) ||
       (Local_u8Temperature <=
        CRITICAL_LOW_TEMP) ||
       (Local_u8Moisture <=
        CRITICAL_LOW_MOISTURE))
    {
        Climate_vTurnAlarmOn();

        G_tenuSystemState =
            CLIMATE_CRITICAL_EMERGENCY;

        Local_u8CriticalState = 1U;
    }
    else
    {
        Climate_vTurnAlarmOff();
    }

    return Local_u8CriticalState;
}

static void Climate_vUpdateState(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    if(Local_u8Temperature >=
       G_u8MaximumTemperature)
    {
        G_tenuSystemState =
            CLIMATE_HIGH_TEMP;
    }
    else if(Local_u8Temperature <=
            G_u8MinimumTemperature)
    {
        G_tenuSystemState =
            CLIMATE_LOW_TEMP;
    }
    else if(Local_u8Moisture <=
            G_u8MinimumMoisture)
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

    G_u8MinimumTemperature =
        DEFAULT_MIN_TEMPERATURE;

    G_u8MaximumTemperature =
        DEFAULT_MAX_TEMPERATURE;

    G_u8MinimumMoisture =
        DEFAULT_MIN_MOISTURE;

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

u8 Climate_u8SetAutomaticThresholds(
    u8 Local_u8MinimumTemperature,
    u8 Local_u8MaximumTemperature,
    u8 Local_u8MinimumMoisture)
{
    u8 Local_u8Status = 0U;

    if((Local_u8MinimumTemperature >=
        MIN_CONFIG_TEMPERATURE) &&
       (Local_u8MinimumTemperature <=
        MAX_CONFIG_TEMPERATURE) &&
       (Local_u8MaximumTemperature >=
        MIN_CONFIG_TEMPERATURE) &&
       (Local_u8MaximumTemperature <=
        MAX_CONFIG_TEMPERATURE) &&
       ((u8)(Local_u8MinimumTemperature +
             MIN_TEMPERATURE_GAP) <=
        Local_u8MaximumTemperature) &&
       (Local_u8MinimumMoisture >=
        MIN_CONFIG_MOISTURE) &&
       (Local_u8MinimumMoisture <=
        MAX_CONFIG_MOISTURE))
    {
        G_u8MinimumTemperature =
            Local_u8MinimumTemperature;

        G_u8MaximumTemperature =
            Local_u8MaximumTemperature;

        G_u8MinimumMoisture =
            Local_u8MinimumMoisture;

        Local_u8Status = 1U;
    }
    else
    {
        /* Invalid Threshold Values */
    }

    return Local_u8Status;
}

u8 Climate_u8GetMinimumTemperature(void)
{
    return G_u8MinimumTemperature;
}

u8 Climate_u8GetMaximumTemperature(void)
{
    return G_u8MaximumTemperature;
}

u8 Climate_u8GetMinimumMoisture(void)
{
    return G_u8MinimumMoisture;
}

void Climate_vSetManualActuator(
    ClimateActuator_t Local_tenuActuator,
    u8 Local_u8State)
{
    if((G_tenuSystemMode == MODE_MANUAL) &&
       ((Local_u8State ==
         CLIMATE_ACTUATOR_OFF) ||
        (Local_u8State ==
         CLIMATE_ACTUATOR_ON)))
    {
        if(Local_tenuActuator ==
           CLIMATE_PUMP)
        {
            if(Local_u8State ==
               CLIMATE_ACTUATOR_ON)
            {
                Climate_vTurnPumpOn();
            }
            else
            {
                Climate_vTurnPumpOff();
            }
        }
        else if(Local_tenuActuator ==
                CLIMATE_FAN)
        {
            if(Local_u8State ==
               CLIMATE_ACTUATOR_ON)
            {
                /*
                 * Fan and heater must not
                 * operate at the same time.
                 */
                Climate_vTurnHeaterOff();
                Climate_vTurnFanOn();
            }
            else
            {
                Climate_vTurnFanOff();
            }
        }
        else if(Local_tenuActuator ==
                CLIMATE_HEATER)
        {
            if(Local_u8State ==
               CLIMATE_ACTUATOR_ON)
            {
                /*
                 * Heater and fan must not
                 * operate at the same time.
                 */
                Climate_vTurnFanOff();
                Climate_vTurnHeaterOn();
            }
            else
            {
                Climate_vTurnHeaterOff();
            }
        }
        else
        {
            /* Invalid Actuator */
        }
    }
    else
    {
        /* Not Manual Mode or Invalid State */
    }
}

u8 Climate_u8GetPumpState(void)
{
    return G_u8PumpState;
}

u8 Climate_u8GetFanState(void)
{
    return G_u8FanState;
}

u8 Climate_u8GetHeaterState(void)
{
    return G_u8HeaterState;
}

void Climate_vUpdateSystem(
    u8 Local_u8Temperature,
    u8 Local_u8Moisture)
{
    u8 Local_u8CriticalState;

    if((Local_u8Temperature >
        SENSOR_MAX_TEMPERATURE) ||
       (Local_u8Moisture >
        SENSOR_MAX_MOISTURE))
    {
        Climate_vHandleSensorError();
    }
    else if(G_tenuSystemMode ==
            MODE_STANDBY)
    {
        Climate_vStopSystem();
    }
    else
    {
        if(G_tenuSystemMode ==
           MODE_AUTOMATIC)
        {
            Climate_vUpdateAutomaticTemperature(
                Local_u8Temperature);

            Climate_vUpdateAutomaticMoisture(
                Local_u8Moisture);
        }
        else
        {
            /*
             * Manual Mode:
             * Do not change actuator states.
             */
        }

        Local_u8CriticalState =
            Climate_u8UpdateAlarm(
                Local_u8Temperature,
                Local_u8Moisture);

        if(Local_u8CriticalState == 0U)
        {
            Climate_vUpdateState(
                Local_u8Temperature,
                Local_u8Moisture);
        }
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

    Climate_vTurnAlarmOn();

    G_tenuSystemState =
        CLIMATE_SENSOR_ERROR;
}

void Climate_vStopSystem(void)
{
    Climate_vTurnFanOff();
    Climate_vTurnHeaterOff();
    Climate_vTurnPumpOff();

    Climate_vTurnAlarmOff();

    G_tenuSystemState =
        CLIMATE_OK;
}