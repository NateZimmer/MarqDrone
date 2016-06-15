/*
 * ADC.c
 *
 *  Created on: Jan 2, 2016
 *      Author: Z
 */


#include "ADC.h"
#include "ADC0.h"
#include <math.h>
#include <stdlib.h>

uint16_t ADC_CHANNELS[ADCH_CHANNEL_TOTAL];

void Set_ADC_Channel(POTS POT)
{
	//ADC_PDD_SelectChannelSet(ADC0_DEVICE,);
	switch(POT)
	{
	case POT0_CH:
		ADC_PDD_SetChannel(ADC0_DEVICE,0,POT0);
		break;
	case POT1_CH:
		ADC_PDD_SetChannel(ADC0_DEVICE,0,POT1);
		break;
	case POT2_CH:
		ADC_PDD_SetChannel(ADC0_DEVICE,0,POT2);
		break;
	case POT3_CH:
		ADC_PDD_SetChannel(ADC0_DEVICE,0,POT3);
		break;
	}

}


int16_t ABS_Limiter16(int16_t A,int16_t Threshold)
{
	int16_t tempValue = A;

	if( (abs(A) -abs(Threshold)) > 0 ) // Limit has been reached
	{
		if(A>0)
		{
			tempValue = abs(Threshold);
		}
		else
		{
			tempValue = -abs(Threshold);
		}
	}

	return tempValue;

}
