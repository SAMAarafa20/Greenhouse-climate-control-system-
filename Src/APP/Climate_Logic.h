/**
 * @file climate_logic.h
 * @brief Application layer header file for climate control logic module.
 * @author Team Leader
 * @date 2026
 * @target ATmega32 (AVR 8-bit)
 */

#ifndef CLIMATE_LOGIC_H_
#define CLIMATE_LOGIC_H_

/* 1. Core Library Inclusion */
#include "../Commen/DEFINITIONS.h"
#include "../Commen/BIT_MATH.h"

/* 2. System Threshold Macros */
#define TEMP_MAX_THRESHOLD    30   /**< Maximum temperature threshold in Celsius */
#define TEMP_MIN_THRESHOLD    18   /**< Minimum temperature threshold in Celsius */
#define MOIST_MIN_THRESHOLD   40   /**< Minimum soil moisture percentage */

/* 3. System States & Modes Enumerations */
/**
 * @brief Enumeration for system operating modes.
 */
typedef enum {
    MODE_AUTOMATIC = 0, /**< System automatically controls actuators based on sensor data */
    MODE_MANUAL         /**< System actuators are manually overridden */
} SystemMode_t;

/**
 * @brief Enumeration for system status states.
 */
typedef enum {
    CLIMATE_OK = 0,              /**< Parameters are within normal ranges */
    CLIMATE_HIGH_TEMP,           /**< High temperature detected */
    CLIMATE_LOW_TEMP,            /**< Low temperature detected */
    CLIMATE_LOW_MOISTURE,        /**< Dry soil detected */
    CLIMATE_CRITICAL_EMERGENCY   /**< Critical hardware or environmental state */
} SystemState_t;

/* 4. Function Prototypes */

/**
 * @brief Initializes the climate control module variables.
 * @return void
 */
void Climate_vInit(void);

/**
 * @brief Updates actuator states based on sensor inputs.
 * @param[in] Local_u8Temperature Current ambient temperature reading.
 * @param[in] Local_u8Moisture Current soil moisture percentage reading.
 * @return void
 */
void Climate_vUpdateSystem(u8 Local_u8Temperature, u8 Local_u8Moisture);

/**
 * @brief Sets the system operating mode.
 * @param[in] Local_u8Mode Target operating mode (MODE_AUTOMATIC or MODE_MANUAL).
 * @return void
 */
void Climate_vSetMode(SystemMode_t Local_u8Mode);

/**
 * @brief Retrieves current climate system state.
 * @return SystemState_t Current state of the system.
 */
SystemState_t Climate_tenuGetState(void);

#endif /* CLIMATE_LOGIC_H_ */