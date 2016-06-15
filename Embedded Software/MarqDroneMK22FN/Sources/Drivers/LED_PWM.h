/*
 * LED_PWM.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_EXTERNAL_LED_PWM_H_
#define SOURCES_DRIVERS_EXTERNAL_LED_PWM_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	LED_FADE=0,
	LED_ON=1,
	LED_OFF=2
}LED_STATES;

extern LED_STATES GLED_STATES;
extern LED_STATES RLED_STATES;

void Handle_LED_Fade();


#endif /* SOURCES_DRIVERS_EXTERNAL_LED_PWM_H_ */
