#include "Climate_Logic.h"

#include "../HAL/BUZZER/BUZZER_Interface.h"
#include "../HAL/KEYPAD/KEYPAD_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/LED/LED_Config.h"
#include "../HAL/RELAY/RELAY_Interface.h"
#include "../HAL/SOIL_SENSOR/SOIL_SENSOR_Interface.h"
#include "../HAL/TEMP_SENSOR/TEMP_SENSOR_Interface.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/EXTI/EXTI_Interface.h"
#include "../MCAL/GIE/GIE_Interface.h"
#include "../MCAL/TIMER0/TIMER0_Interface.h"

#include <stdint.h>

#define APP_SENSOR_PERIOD_MS          500UL
#define APP_BUTTON_DEBOUNCE_MS        200UL

#define APP_MODE_BUTTON_GROUP         DIO_GroupD
#define APP_MODE_BUTTON_PIN           DIO_Pin2

typedef enum
{
    APP_MODE_MENU = 0,
    APP_MANUAL_SCREEN,
    APP_AUTOMATIC_SCREEN,
    APP_CONFIG_MENU,
    APP_EDIT_MIN_TEMP,
    APP_EDIT_MAX_TEMP,
    APP_EDIT_MIN_MOISTURE,
    APP_CONFIG_ERROR

} AppScreen_t;

static AppScreen_t G_tenuCurrentScreen =
    APP_MODE_MENU;

static uint8_t G_u8Temperature = 0U;
static uint8_t G_u8Moisture = 0U;

static uint8_t G_u8InputValue = 0U;
static uint8_t G_u8InputDigits = 0U;

static uint32_t G_u32LastSensorTime = 0UL;
static uint32_t G_u32LastDisplayTime = 0UL;
static uint32_t G_u32LastButtonTime = 0UL;

static volatile uint8_t
    G_u8ModeToggleRequest = 0U;

static void App_vWriteText(
    const char *Text)
{
    LCD_WriteString(
        (const uint8_t *)Text);
}

static void App_vClearLine(
    uint8_t Row)
{
    LCD_GoToXY(Row, 0U);

    App_vWriteText(
        "                ");

    LCD_GoToXY(Row, 0U);
}

static void App_vWriteNumber(
    uint8_t Number)
{
    if(Number >= 100U)
    {
        LCD_WriteChar(
            (uint8_t)('0' +
            (Number / 100U)));

        LCD_WriteChar(
            (uint8_t)('0' +
            ((Number / 10U) % 10U)));

        LCD_WriteChar(
            (uint8_t)('0' +
            (Number % 10U)));
    }
    else if(Number >= 10U)
    {
        LCD_WriteChar(
            (uint8_t)('0' +
            (Number / 10U)));

        LCD_WriteChar(
            (uint8_t)('0' +
            (Number % 10U)));
    }
    else
    {
        LCD_WriteChar(
            (uint8_t)('0' + Number));
    }
}

static void App_vWriteActuatorState(
    uint8_t State)
{
    if(State == CLIMATE_ACTUATOR_ON)
    {
        LCD_WriteChar('1');
    }
    else
    {
        LCD_WriteChar('0');
    }
}

static void App_vShowWelcome(void)
{
    uint32_t Local_u32StartTime;

    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("Welcome To");

    LCD_GoToXY(1U, 0U);
    App_vWriteText("Greenhouse");

    Local_u32StartTime =
        TIMER0_GetMilliseconds();

    while((TIMER0_GetMilliseconds() -
           Local_u32StartTime) < 1500UL)
    {
        /* Startup Welcome Screen */
    }
}

static void App_vShowModeMenu(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("1:Manual");

    LCD_GoToXY(1U, 0U);
    App_vWriteText("2:Auto C:Stop");
}

static void App_vShowManualScreen(void)
{
    App_vClearLine(0U);

    App_vWriteText("MAN P:");
    App_vWriteActuatorState(
        Climate_u8GetPumpState());

    App_vWriteText(" F:");
    App_vWriteActuatorState(
        Climate_u8GetFanState());

    App_vWriteText(" H:");
    App_vWriteActuatorState(
        Climate_u8GetHeaterState());

    App_vClearLine(1U);

    App_vWriteText("1:P 2:F 3:H =:S");
}

static void App_vWriteSystemState(void)
{
    SystemState_t Local_tenuState =
        Climate_tenuGetState();

    if(Local_tenuState == CLIMATE_OK)
    {
        App_vWriteText("OK");
    }
    else if(Local_tenuState ==
            CLIMATE_HIGH_TEMP)
    {
        App_vWriteText("HIGH");
    }
    else if(Local_tenuState ==
            CLIMATE_LOW_TEMP)
    {
        App_vWriteText("LOW");
    }
    else if(Local_tenuState ==
            CLIMATE_LOW_MOISTURE)
    {
        App_vWriteText("DRY");
    }
    else if(Local_tenuState ==
            CLIMATE_CRITICAL_EMERGENCY)
    {
        App_vWriteText("CRITICAL");
    }
    else if(Local_tenuState ==
            CLIMATE_SENSOR_ERROR)
    {
        App_vWriteText("SENSOR ERR");
    }
    else
    {
        App_vWriteText("UNKNOWN");
    }
}

static void App_vShowAutomaticScreen(void)
{
    App_vClearLine(0U);

    App_vWriteText("A T:");
    App_vWriteNumber(G_u8Temperature);

    App_vWriteText(" M:");
    App_vWriteNumber(G_u8Moisture);

    App_vClearLine(1U);

    App_vWriteSystemState();

    LCD_GoToXY(1U, 9U);
    App_vWriteText("=:S C:X");
}

static void App_vShowConfigMenu(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("1:MinT 2:MaxT");

    LCD_GoToXY(1U, 0U);
    App_vWriteText("3:Moist C:Back");
}

static void App_vShowInputScreen(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);

    if(G_tenuCurrentScreen ==
       APP_EDIT_MIN_TEMP)
    {
        App_vWriteText("Minimum Temp:");
    }
    else if(G_tenuCurrentScreen ==
            APP_EDIT_MAX_TEMP)
    {
        App_vWriteText("Maximum Temp:");
    }
    else
    {
        App_vWriteText("Minimum Moist:");
    }

    LCD_GoToXY(1U, 0U);

    if(G_u8InputDigits == 0U)
    {
        App_vWriteText("__");
    }
    else
    {
        App_vWriteNumber(
            G_u8InputValue);
    }

    LCD_GoToXY(1U, 5U);
    App_vWriteText("=:OK C:X");
}

static void App_vShowConfigError(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("Invalid Value");

    LCD_GoToXY(1U, 0U);
    App_vWriteText("C:Config Menu");
}

static void App_vReturnToOperatingScreen(void)
{
    if(Climate_tenuGetMode() ==
       MODE_MANUAL)
    {
        G_tenuCurrentScreen =
            APP_MANUAL_SCREEN;

        App_vShowManualScreen();
    }
    else if(Climate_tenuGetMode() ==
            MODE_AUTOMATIC)
    {
        G_tenuCurrentScreen =
            APP_AUTOMATIC_SCREEN;

        App_vShowAutomaticScreen();
    }
    else
    {
        G_tenuCurrentScreen =
            APP_MODE_MENU;

        App_vShowModeMenu();
    }
}

static void App_vUpdateSensors(void)
{
    uint32_t Local_u32CurrentTime =
        TIMER0_GetMilliseconds();

    uint8_t Local_u8TempStatus;
    uint8_t Local_u8MoistureStatus;

    if((Local_u32CurrentTime -
        G_u32LastSensorTime) >=
       APP_SENSOR_PERIOD_MS)
    {
        G_u32LastSensorTime =
            Local_u32CurrentTime;

        Local_u8TempStatus =
            TEMP_SENSOR_GetTemperature(
                &G_u8Temperature);

        Local_u8MoistureStatus =
            SOIL_SENSOR_GetMoisture(
                &G_u8Moisture);

        if((Local_u8TempStatus ==
            TEMP_SENSOR_READING_OK) &&
           (Local_u8MoistureStatus ==
            SOIL_SENSOR_READING_OK))
        {
            if(Climate_tenuGetMode() !=
               MODE_STANDBY)
            {
                Climate_vUpdateSystem(
                    G_u8Temperature,
                    G_u8Moisture);
            }
        }
        else
        {
            Climate_vHandleSensorError();
        }
    }
}

static void App_vUpdateDisplay(void)
{
    uint32_t Local_u32CurrentTime =
        TIMER0_GetMilliseconds();

    if((Local_u32CurrentTime -
        G_u32LastDisplayTime) >=
       APP_SENSOR_PERIOD_MS)
    {
        G_u32LastDisplayTime =
            Local_u32CurrentTime;

        if(G_tenuCurrentScreen ==
           APP_MANUAL_SCREEN)
        {
            App_vShowManualScreen();
        }
        else if(G_tenuCurrentScreen ==
                APP_AUTOMATIC_SCREEN)
        {
            App_vShowAutomaticScreen();
        }
        else
        {
            /* Static Screen */
        }
    }
}

static void App_vStartInput(
    AppScreen_t Local_tenuInputScreen)
{
    G_u8InputValue = 0U;
    G_u8InputDigits = 0U;

    G_tenuCurrentScreen =
        Local_tenuInputScreen;

    App_vShowInputScreen();
}

static void App_vSaveInput(void)
{
    uint8_t Local_u8Status = 0U;

    if(G_tenuCurrentScreen ==
       APP_EDIT_MIN_TEMP)
    {
        Local_u8Status =
            Climate_u8SetAutomaticThresholds(
                G_u8InputValue,
                Climate_u8GetMaximumTemperature(),
                Climate_u8GetMinimumMoisture());
    }
    else if(G_tenuCurrentScreen ==
            APP_EDIT_MAX_TEMP)
    {
        Local_u8Status =
            Climate_u8SetAutomaticThresholds(
                Climate_u8GetMinimumTemperature(),
                G_u8InputValue,
                Climate_u8GetMinimumMoisture());
    }
    else if(G_tenuCurrentScreen ==
            APP_EDIT_MIN_MOISTURE)
    {
        Local_u8Status =
            Climate_u8SetAutomaticThresholds(
                Climate_u8GetMinimumTemperature(),
                Climate_u8GetMaximumTemperature(),
                G_u8InputValue);
    }
    else
    {
        /* Invalid Input Screen */
    }

    if(Local_u8Status == 1U)
    {
        G_tenuCurrentScreen =
            APP_CONFIG_MENU;

        App_vShowConfigMenu();
    }
    else
    {
        G_tenuCurrentScreen =
            APP_CONFIG_ERROR;

        App_vShowConfigError();
    }
}

static void App_vHandleInputKey(
    uint8_t Local_u8PressedKey)
{
    if((Local_u8PressedKey >= '0') &&
       (Local_u8PressedKey <= '9'))
    {
        if(G_u8InputDigits < 2U)
        {
            G_u8InputValue =
                (uint8_t)(
                    (G_u8InputValue * 10U) +
                    (Local_u8PressedKey - '0'));

            G_u8InputDigits++;

            App_vShowInputScreen();
        }
    }
    else if(Local_u8PressedKey == 'C')
    {
        G_tenuCurrentScreen =
            APP_CONFIG_MENU;

        App_vShowConfigMenu();
    }
    else if(Local_u8PressedKey == '=')
    {
        if(G_u8InputDigits > 0U)
        {
            App_vSaveInput();
        }
    }
    else
    {
        /* Invalid Input Key */
    }
}

static void App_vToggleManualActuator(
    ClimateActuator_t Local_tenuActuator)
{
    uint8_t Local_u8CurrentState = 0U;

    if(Local_tenuActuator ==
       CLIMATE_PUMP)
    {
        Local_u8CurrentState =
            Climate_u8GetPumpState();
    }
    else if(Local_tenuActuator ==
            CLIMATE_FAN)
    {
        Local_u8CurrentState =
            Climate_u8GetFanState();
    }
    else if(Local_tenuActuator ==
            CLIMATE_HEATER)
    {
        Local_u8CurrentState =
            Climate_u8GetHeaterState();
    }
    else
    {
        /* Invalid Actuator */
    }

    Climate_vSetManualActuator(
        Local_tenuActuator,
        (uint8_t)(Local_u8CurrentState ^ 1U));

    App_vShowManualScreen();
}

static void App_vHandleKey(
    uint8_t Local_u8PressedKey)
{
    if(G_tenuCurrentScreen ==
       APP_MODE_MENU)
    {
        if(Local_u8PressedKey == '1')
        {
            Climate_vSetMode(
                MODE_MANUAL);

            G_tenuCurrentScreen =
                APP_MANUAL_SCREEN;

            App_vShowManualScreen();
        }
        else if(Local_u8PressedKey == '2')
        {
            Climate_vSetMode(
                MODE_AUTOMATIC);

            G_tenuCurrentScreen =
                APP_AUTOMATIC_SCREEN;

            App_vShowAutomaticScreen();
        }
        else if(Local_u8PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            App_vShowModeMenu();
        }
    }
    else if(G_tenuCurrentScreen ==
            APP_MANUAL_SCREEN)
    {
        if(Local_u8PressedKey == '1')
        {
            App_vToggleManualActuator(
                CLIMATE_PUMP);
        }
        else if(Local_u8PressedKey == '2')
        {
            App_vToggleManualActuator(
                CLIMATE_FAN);
        }
        else if(Local_u8PressedKey == '3')
        {
            App_vToggleManualActuator(
                CLIMATE_HEATER);
        }
        else if(Local_u8PressedKey == '=')
        {
            G_tenuCurrentScreen =
                APP_CONFIG_MENU;

            App_vShowConfigMenu();
        }
        else if(Local_u8PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            G_tenuCurrentScreen =
                APP_MODE_MENU;

            App_vShowModeMenu();
        }
    }
    else if(G_tenuCurrentScreen ==
            APP_AUTOMATIC_SCREEN)
    {
        if(Local_u8PressedKey == '=')
        {
            G_tenuCurrentScreen =
                APP_CONFIG_MENU;

            App_vShowConfigMenu();
        }
        else if(Local_u8PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            G_tenuCurrentScreen =
                APP_MODE_MENU;

            App_vShowModeMenu();
        }
    }
    else if(G_tenuCurrentScreen ==
            APP_CONFIG_MENU)
    {
        if(Local_u8PressedKey == '1')
        {
            App_vStartInput(
                APP_EDIT_MIN_TEMP);
        }
        else if(Local_u8PressedKey == '2')
        {
            App_vStartInput(
                APP_EDIT_MAX_TEMP);
        }
        else if(Local_u8PressedKey == '3')
        {
            App_vStartInput(
                APP_EDIT_MIN_MOISTURE);
        }
        else if(Local_u8PressedKey == 'C')
        {
            App_vReturnToOperatingScreen();
        }
    }
    else if((G_tenuCurrentScreen ==
             APP_EDIT_MIN_TEMP) ||
            (G_tenuCurrentScreen ==
             APP_EDIT_MAX_TEMP) ||
            (G_tenuCurrentScreen ==
             APP_EDIT_MIN_MOISTURE))
    {
        App_vHandleInputKey(
            Local_u8PressedKey);
    }
    else if(G_tenuCurrentScreen ==
            APP_CONFIG_ERROR)
    {
        if(Local_u8PressedKey == 'C')
        {
            G_tenuCurrentScreen =
                APP_CONFIG_MENU;

            App_vShowConfigMenu();
        }
    }
    else
    {
        /* Invalid Screen */
    }
}

static void App_vModeButtonCallback(void)
{
    /*
     * ISR callback only raises a flag.
     * No LCD or relay operation is
     * performed inside the interrupt.
     */
    G_u8ModeToggleRequest = 1U;
}

static void App_vHandleModeButton(void)
{
    uint32_t Local_u32CurrentTime;

    if(G_u8ModeToggleRequest == 1U)
    {
        G_u8ModeToggleRequest = 0U;

        Local_u32CurrentTime =
            TIMER0_GetMilliseconds();

        if((Local_u32CurrentTime -
            G_u32LastButtonTime) >=
           APP_BUTTON_DEBOUNCE_MS)
        {
            G_u32LastButtonTime =
                Local_u32CurrentTime;

            if(Climate_tenuGetMode() ==
               MODE_AUTOMATIC)
            {
                Climate_vSetMode(
                    MODE_MANUAL);

                G_tenuCurrentScreen =
                    APP_MANUAL_SCREEN;

                App_vShowManualScreen();
            }
            else
            {
                Climate_vSetMode(
                    MODE_AUTOMATIC);

                G_tenuCurrentScreen =
                    APP_AUTOMATIC_SCREEN;

                App_vShowAutomaticScreen();
            }
        }
    }
}

int main(void)
{
    uint8_t Local_u8PressedKey =
        KEYPAD_NO_KEY_PRESSED;

    uint8_t Local_u8PreviousKey =
        KEYPAD_NO_KEY_PRESSED;

    /*
     * Release PORTC JTAG pins before
     * initializing the LCD.
     */
    DIO_DisableJTAG();

    /*
     * Initialize Mode Button:
     * PD2 input with Internal Pull-up.
     */
    DIO_DirectionSelectforPin(
        APP_MODE_BUTTON_GROUP,
        APP_MODE_BUTTON_PIN,
        DIO_Inputfor1Pin);

    DIO_WritePin(
        APP_MODE_BUTTON_GROUP,
        APP_MODE_BUTTON_PIN,
        DIO_Highfor1Pin);

    /*
     * Initialize HAL Drivers.
     */
    LCD_Init();
    KeyPad_Init();

    Relay_Init();
    Buzzer_Init();

    Led_Init(
        ALARM_LED_GROUP,
        ALARM_LED_PIN);

    Led_Off(
        ALARM_LED_GROUP,
        ALARM_LED_PIN,
        ALARM_LED_CONNECTION_TYPE);

    TEMP_SENSOR_Init();
    SOIL_SENSOR_Init();

    /*
     * Initialize Timer0 and INT0
     * before enabling global interrupts.
     */
    TIMER0_Init();

    EXTI_INT0_Init();

    (void)EXTI_INT0_SetCallback(
        App_vModeButtonCallback);

    EXTI_INT0_Enable();

    GIE_Enable();
    TIMER0_Start();

    /*
     * Initialize Application Logic.
     */
    Climate_vInit();

    App_vShowWelcome();
    App_vShowModeMenu();

    G_u32LastSensorTime =
        TIMER0_GetMilliseconds();

    G_u32LastDisplayTime =
        TIMER0_GetMilliseconds();

    G_u32LastButtonTime =
        TIMER0_GetMilliseconds();

    while(1)
    {
        App_vHandleModeButton();

        App_vUpdateSensors();
        App_vUpdateDisplay();

        Local_u8PressedKey =
            KeyPad_GetPressedKey();

        if((Local_u8PressedKey !=
            KEYPAD_NO_KEY_PRESSED) &&
           (Local_u8PreviousKey ==
            KEYPAD_NO_KEY_PRESSED))
        {
            App_vHandleKey(
                Local_u8PressedKey);
        }

        Local_u8PreviousKey =
            Local_u8PressedKey;
    }

    return 0;
}