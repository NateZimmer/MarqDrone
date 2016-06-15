/*
 * ADC.c
 *
 *  Created on: Jan 17, 2016
 *      Author: Z
 */

#include "ADC.h"
#include "ADC0.h"
#include "ADC_PDD.h"

uint16_t ADC_Value = 0;

void Set_Channel(uint16_t Channel_Num)
{
	ADC_PDD_SetChannel(ADC0_DEVICE,0,Channel_Num);
}

void Init_ADC()
{
	Set_Channel(12);
}

uint16_t Get_ADC_Value()
{
	ADC_Value = ADC0_RA;
	return ADC_Value;
}

