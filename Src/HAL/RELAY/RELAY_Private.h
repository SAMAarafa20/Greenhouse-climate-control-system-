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
    RELAY_SinkConnection = 0,
    RELAY_SourceConnection

} Relay_ConnectionType_t;

#define RELAY_VALID_ID      (1U)
#define RELAY_INVALID_ID    (0U)

#endif /* RELAY_PRIVATE_H_ */