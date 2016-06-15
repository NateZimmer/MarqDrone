/*
 * ADC.h
 *
 *  Created on: Jan 17, 2016
 *      Author: Z
 */

#ifndef SOURCES_APPLICATION_ADC_H_
#define SOURCES_APPLICATION_ADC_H_

#include "GPIO.h"
#include <stdint.h>

void Set_Channel(uint16_t Channel_Num);
void Init_ADC();
uint16_t Get_ADC_Value();

extern uint16_t ADC_Value;

#endif /* SOURCES_APPLICATION_ADC_H_ */
