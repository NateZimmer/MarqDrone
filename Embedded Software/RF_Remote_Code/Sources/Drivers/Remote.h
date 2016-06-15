/*
 * Remote.h
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */

#ifndef DRIVERS_REMOTE_H_
#define DRIVERS_REMOTE_H_

#include <stdint.h>
#include <PE_Types.h>
#include "GPIO.h"


typedef enum{
	BLUE = 0,
	RED = 1,
	GREEN = 2,
	POWER = 3
} LEDS;

extern GPIO_HANDLES POWER_LED;
extern GPIO_HANDLES GREEN_LED;
extern GPIO_HANDLES RED_LED;
extern GPIO_HANDLES BLUE_LED;
extern GPIO_HANDLES CC_CS_PIN;

void Setup_Remote_IO();

//void Turn_On_LED(LEDS led, bool on);
void Turn_On_LED(GPIO_HANDLES * GPIO_HANDLE, uint32_t on);


#endif /* DRIVERS_REMOTE_H_ */
