#ifndef RELAY_PRIVATE_H_
#define RELAY_PRIVATE_H_


typedef enum
{
    RELAY_FAN = 0,
    RELAY_HEATER,
    RELAY_PUMP
} Relay_Id_t;


typedef enum
{
    RELAY_SinkConnection,
    RELAY_SourceConnection
} Relay_ConnectionType_t;

#endif 