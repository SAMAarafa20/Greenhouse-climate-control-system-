/**
 * @file climate_logic.c
 * @brief Application layer implementation for climate control logic module.
 * @author Team Leader
 * @date 2026
 * @target ATmega32 (AVR 8-bit)
 */

#include "climate_logic.h"

/* HAL Actuator Drivers */
#include "../HAL/RELAY/RELAY_Interface.h"
#include "../HAL/BUZZER/BUZZER_Interface.h"

/* Private File-Scope Variables (static + volatile as per training notes) */
static volatile SystemMode_t  G_u8SystemMode  = MODE_AUTOMATIC;
static volatile SystemState_t G_u8SystemState = CLIMATE_OK;

/**
 * @brief Initializes the climate control module variables.
 */
void Climate_vInit(void) {
    G_u8SystemMode  = MODE_AUTOMATIC;
    G_u8SystemState = CLIMATE_OK;
}

/**
 * @brief Sets the system operating mode.
 * @param[in] Local_u8Mode Target operating mode.
 */
void Climate_vSetMode(SystemMode_t Local_u8Mode) {
    G_u8SystemMode = Local_u8Mode;
}

/**
 * @brief Retrieves current climate system state.
 * @return SystemState_t Current state of the system.
 */
SystemState_t Climate_tenuGetState(void) {
    return G_u8SystemState;
}

/**
 * @brief Updates actuator states based on sensor inputs.
 * @param[in] Local_u8Temperature Current ambient temperature reading.
 * @param[in] Local_u8Moisture Current soil moisture percentage reading.
 */
void Climate_vUpdateSystem(u8 Local_u8Temperature, u8 Local_u8Moisture) {
    if (G_u8SystemMode == MODE_AUTOMATIC) {
        
        /* 1. Temperature Logic */
        if (Local_u8Temperature > TEMP_MAX_THRESHOLD) {
            Relay_TurnOn(RELAY_FAN);
            Relay_TurnOff(RELAY_HEATER);
            G_u8SystemState = CLIMATE_HIGH_TEMP;
        } 
        else if (Local_u8Temperature < TEMP_MIN_THRESHOLD) {
            Relay_TurnOff(RELAY_FAN);
            Relay_TurnOn(RELAY_HEATER);
            G_u8SystemState = CLIMATE_LOW_TEMP;
        } 
        else {
            Relay_TurnOff(RELAY_FAN);
            Relay_TurnOff(RELAY_HEATER);
            G_u8SystemState = CLIMATE_OK;
        }

        /* 2. Soil Moisture Logic */
        if (Local_u8Moisture < MOIST_MIN_THRESHOLD) {
            Relay_TurnOn(RELAY_PUMP);
            Buzzer_On();
        } 
        else {
            Relay_TurnOff(RELAY_PUMP);
            Buzzer_Off();
        }
    }
}