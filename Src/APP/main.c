#include "Climate_Logic.h"

#include "../HAL/BUZZER/BUZZER_Interface.h"
#include "../HAL/KEYPAD/KEYPAD_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/RELAY/RELAY_Interface.h"
#include "../HAL/SOIL_SENSOR/SOIL_SENSOR_Interface.h"
#include "../HAL/TEMP_SENSOR/TEMP_SENSOR_Interface.h"

#include "../MCAL/GIE/GIE_Interface.h"
#include "../MCAL/TIMER0/TIMER0_Interface.h"

#include <stdint.h>

/* Sensor Reading Period */

#define APP_SENSOR_PERIOD_MS        500UL

typedef enum
{
    APP_MODE_MENU = 0,
    APP_MANUAL_SCREEN,
    APP_AUTOMATIC_SCREEN,
    APP_EDIT_TEMPERATURE,
    APP_EDIT_MOISTURE

} AppScreen_t;

static AppScreen_t G_tenuCurrentScreen =
    APP_MODE_MENU;

static uint8_t G_u8Temperature = 0U;
static uint8_t G_u8Moisture = 0U;

static uint8_t G_u8InputValue = 0U;
static uint8_t G_u8InputDigits = 0U;

static uint32_t G_u32LastSensorTime = 0UL;
static uint32_t G_u32LastDisplayTime = 0UL;

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

static void App_vShowWelcome(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("Welcome To");

    LCD_GoToXY(1U, 0U);
    App_vWriteText("Greenhouse");

    /*
     * Timer0 continues operating.
     * This delay is only for the
     * startup welcome screen.
     */

    {
        uint32_t LocalStartTime =
            TIMER0_GetMilliseconds();

        while((TIMER0_GetMilliseconds() -
               LocalStartTime) < 1500UL)
        {
            /* Welcome Screen */
        }
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

    App_vWriteText("T:");
    App_vWriteNumber(G_u8Temperature);

    App_vWriteText(">");
    App_vWriteNumber(
        Climate_u8GetTargetTemperature());

    App_vWriteText(" M:");
    App_vWriteNumber(G_u8Moisture);

    App_vWriteText(">");
    App_vWriteNumber(
        Climate_u8GetTargetMoisture());

    App_vClearLine(1U);

    App_vWriteText("1:T 2:M C:Back");
}

static void App_vWriteSystemState(void)
{
    SystemState_t LocalState =
        Climate_tenuGetState();

    if(LocalState == CLIMATE_OK)
    {
        App_vWriteText("OK");
    }
    else if(LocalState ==
            CLIMATE_HIGH_TEMP)
    {
        App_vWriteText("HIGH TEMP");
    }
    else if(LocalState ==
            CLIMATE_LOW_TEMP)
    {
        App_vWriteText("LOW TEMP");
    }
    else if(LocalState ==
            CLIMATE_LOW_MOISTURE)
    {
        App_vWriteText("DRY SOIL");
    }
    else if(LocalState ==
            CLIMATE_CRITICAL_EMERGENCY)
    {
        App_vWriteText("CRITICAL");
    }
    else if(LocalState ==
            CLIMATE_SENSOR_ERROR)
    {
        App_vWriteText("SENSOR ERROR");
    }
    else
    {
        App_vWriteText("UNKNOWN");
    }
}

static void App_vShowAutomaticScreen(void)
{
    App_vClearLine(0U);

    App_vWriteText("AUTO T:");
    App_vWriteNumber(G_u8Temperature);

    App_vWriteText(" M:");
    App_vWriteNumber(G_u8Moisture);

    App_vClearLine(1U);

    App_vWriteSystemState();

    LCD_GoToXY(1U, 10U);
    App_vWriteText("C:Back");
}

static void App_vShowTemperatureInput(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("Target Temp:");

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

static void App_vShowMoistureInput(void)
{
    LCD_Clear();

    LCD_GoToXY(0U, 0U);
    App_vWriteText("Target Moist:");

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

static void App_vUpdateSensors(void)
{
    uint32_t LocalCurrentTime =
        TIMER0_GetMilliseconds();

    uint8_t LocalTempStatus;
    uint8_t LocalMoistureStatus;

    if((LocalCurrentTime -
        G_u32LastSensorTime) >=
       APP_SENSOR_PERIOD_MS)
    {
        G_u32LastSensorTime =
            LocalCurrentTime;

        LocalTempStatus =
            TEMP_SENSOR_GetTemperature(
                &G_u8Temperature);

        LocalMoistureStatus =
            SOIL_SENSOR_GetMoisture(
                &G_u8Moisture);

        if((LocalTempStatus ==
            TEMP_SENSOR_READING_OK) &&
           (LocalMoistureStatus ==
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
    uint32_t LocalCurrentTime =
        TIMER0_GetMilliseconds();

    if((LocalCurrentTime -
        G_u32LastDisplayTime) >=
       APP_SENSOR_PERIOD_MS)
    {
        G_u32LastDisplayTime =
            LocalCurrentTime;

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
    AppScreen_t InputScreen)
{
    G_u8InputValue = 0U;
    G_u8InputDigits = 0U;

    G_tenuCurrentScreen =
        InputScreen;

    if(InputScreen ==
       APP_EDIT_TEMPERATURE)
    {
        App_vShowTemperatureInput();
    }
    else
    {
        App_vShowMoistureInput();
    }
}

static void App_vHandleInputKey(
    uint8_t PressedKey)
{
    if((PressedKey >= '0') &&
       (PressedKey <= '9'))
    {
        if(G_u8InputDigits < 2U)
        {
            G_u8InputValue =
                (uint8_t)(
                    (G_u8InputValue * 10U) +
                    (PressedKey - '0'));

            G_u8InputDigits++;

            if(G_tenuCurrentScreen ==
               APP_EDIT_TEMPERATURE)
            {
                App_vShowTemperatureInput();
            }
            else
            {
                App_vShowMoistureInput();
            }
        }
    }
    else if(PressedKey == 'C')
    {
        G_tenuCurrentScreen =
            APP_MANUAL_SCREEN;

        App_vShowManualScreen();
    }
    else if(PressedKey == '=')
    {
        if(G_u8InputDigits > 0U)
        {
            if(G_tenuCurrentScreen ==
               APP_EDIT_TEMPERATURE)
            {
                Climate_vSetManualTargets(
                    G_u8InputValue,
                    Climate_u8GetTargetMoisture());
            }
            else
            {
                Climate_vSetManualTargets(
                    Climate_u8GetTargetTemperature(),
                    G_u8InputValue);
            }
        }

        G_tenuCurrentScreen =
            APP_MANUAL_SCREEN;

        App_vShowManualScreen();
    }
    else
    {
        /* Invalid Input Key */
    }
}

static void App_vHandleKey(
    uint8_t PressedKey)
{
    if(G_tenuCurrentScreen ==
       APP_MODE_MENU)
    {
        if(PressedKey == '1')
        {
            Climate_vSetMode(
                MODE_MANUAL);

            G_tenuCurrentScreen =
                APP_MANUAL_SCREEN;

            App_vShowManualScreen();
        }
        else if(PressedKey == '2')
        {
            Climate_vSetMode(
                MODE_AUTOMATIC);

            G_tenuCurrentScreen =
                APP_AUTOMATIC_SCREEN;

            App_vShowAutomaticScreen();
        }
        else if(PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            App_vShowModeMenu();
        }
        else
        {
            /* Invalid Menu Key */
        }
    }
    else if(G_tenuCurrentScreen ==
            APP_MANUAL_SCREEN)
    {
        if(PressedKey == '1')
        {
            App_vStartInput(
                APP_EDIT_TEMPERATURE);
        }
        else if(PressedKey == '2')
        {
            App_vStartInput(
                APP_EDIT_MOISTURE);
        }
        else if(PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            G_tenuCurrentScreen =
                APP_MODE_MENU;

            App_vShowModeMenu();
        }
        else
        {
            /* Invalid Manual Key */
        }
    }
    else if(G_tenuCurrentScreen ==
            APP_AUTOMATIC_SCREEN)
    {
        if(PressedKey == 'C')
        {
            Climate_vSetMode(
                MODE_STANDBY);

            G_tenuCurrentScreen =
                APP_MODE_MENU;

            App_vShowModeMenu();
        }
        else
        {
            /* Invalid Automatic Key */
        }
    }
    else if((G_tenuCurrentScreen ==
             APP_EDIT_TEMPERATURE) ||
            (G_tenuCurrentScreen ==
             APP_EDIT_MOISTURE))
    {
        App_vHandleInputKey(
            PressedKey);
    }
    else
    {
        /* Invalid Screen */
    }
}

int main(void)
{
    uint8_t LocalPressedKey =
        KEYPAD_NO_KEY_PRESSED;

    uint8_t LocalPreviousKey =
        KEYPAD_NO_KEY_PRESSED;

    /*
     * Initialize HAL Drivers.
     */

    LCD_Init();
    KeyPad_Init();

    Relay_Init();
    Buzzer_Init();

    TEMP_SENSOR_Init();
    SOIL_SENSOR_Init();

    /*
     * Initialize Timer0 System Tick.
     */

    TIMER0_Init();
    GIE_Enable();
    TIMER0_Start();

    /*
     * Initialize Application Logic
     * after actuator drivers.
     */

    Climate_vInit();

    App_vShowWelcome();
    App_vShowModeMenu();

    G_u32LastSensorTime =
        TIMER0_GetMilliseconds();

    G_u32LastDisplayTime =
        TIMER0_GetMilliseconds();

    while(1)
    {
        App_vUpdateSensors();
        App_vUpdateDisplay();

        LocalPressedKey =
            KeyPad_GetPressedKey();

        /*
         * Execute the key only once when
         * it changes from released to pressed.
         */

        if((LocalPressedKey !=
            KEYPAD_NO_KEY_PRESSED) &&
           (LocalPreviousKey ==
            KEYPAD_NO_KEY_PRESSED))
        {
            App_vHandleKey(
                LocalPressedKey);
        }

        LocalPreviousKey =
            LocalPressedKey;
    }

    return 0;
}