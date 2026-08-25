#ifndef BUTTON_PRIVATE_H_
#define BUTTON_PRIVATE_H_


typedef enum
{
    BUTTON_InternalPullUp,
    BUTTON_ExternalPullUp,
    BUTTON_ExternalPullDown
} Button_ConnectionType_t;


typedef enum
{
    BUTTON_Pressed,
    BUTTON_NotPressed
} Button_State_t;

#endif 