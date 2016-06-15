/*
 * PWM.h
 *
 *  Created on: Dec 9, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_PWM_H_
#define SOURCES_DRIVERS_PWM_H_

#include <stdint.h>

typedef enum {
	CH0=0,
	CH1=1,
	CH2=2
}PWM_CHS;

void Set_PWM_Reg(PWM_CHS PWM_CH,uint16_t Value);

#endif /* SOURCES_DRIVERS_PWM_H_ */
