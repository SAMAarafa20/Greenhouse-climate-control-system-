#ifndef BUZZER_CONFIG_H_
#define BUZZER_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

/*
 * Greenhouse Buzzer Pin Mapping
 *
 * Buzzer -> PD6
 */

#define BUZZER_GROUP              DIO_GroupD
#define BUZZER_PIN                DIO_Pin6

#define BUZZER_CONNECTION_TYPE    BUZZER_SourceConnection

#define BUZZER_TONE_TIME_MS       500U

#endif /* BUZZER_CONFIG_H_ */