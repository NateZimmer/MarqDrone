/*
 * FC.h
 *
 *  Created on: Nov 14, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_FC_H_
#define SOURCES_DRIVERS_FC_H_

#include "GPIO.h"

void Init_FC_IO();

extern GPIO_HANDLES BLUE_PIN;
extern GPIO_HANDLES RED_PIN;
extern GPIO_HANDLES GREEN_PIN;

extern GPIO_HANDLES AUX1;
extern GPIO_HANDLES AUX2;

extern GPIO_HANDLES PWM0;
extern GPIO_HANDLES PWM1;
extern GPIO_HANDLES PWM2;
extern GPIO_HANDLES PWM3;

extern GPIO_HANDLES A1;
extern GPIO_HANDLES A2;

//MPU92500 SPI :: SPI0
extern GPIO_HANDLES SCLK2;
extern GPIO_HANDLES MOSI2;
extern GPIO_HANDLES MISO2;
extern GPIO_HANDLES MPU_INT;
extern GPIO_HANDLES MPU9250_CS;

//CC2500 SPI1
extern GPIO_HANDLES CC_CS_PIN;
extern GPIO_HANDLES GDO0;
extern GPIO_HANDLES GDO2;
extern GPIO_HANDLES SCLK1;
extern GPIO_HANDLES MOSI1;
extern GPIO_HANDLES MISO1;

typedef enum
{
	PASS=0,
	FAILED=1
}FUNC_RESULTS;

extern uint8_t USB_RDY;

#endif /* SOURCES_DRIVERS_FC_H_ */
