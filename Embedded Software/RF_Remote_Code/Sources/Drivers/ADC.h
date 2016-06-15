/*
 * ADC.h
 *
 *  Created on: Jan 2, 2016
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_ADC_H_
#define SOURCES_DRIVERS_ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include <PE_Types.h>
#include "GPIO.h"
#include "MKL25Z4.h"
#include "ADC_PDD.h"

#define POT0 ADC_PDD_SINGLE_ENDED_DAD0
#define POT1 ADC_PDD_SINGLE_ENDED_AD4
#define POT2 ADC_PDD_SINGLE_ENDED_DAD3
#define POT3 ADC_PDD_SINGLE_ENDED_AD7

#define ADCH_CHANNEL_TOTAL 4 // ROLL PITCH YAW THROTTLE AKA our joystick number


typedef enum
{
	POT0_CH=0,
	POT1_CH=1,
	POT2_CH=2,
	POT3_CH=3
}POTS;


typedef enum
{
	R_THROTTLE=POT0_CH,
	R_YAW=POT1_CH,
	R_PITCH=POT2_CH,
	R_ROLL=POT3_CH
}REMOTE_POTS;

typedef struct
{
	uint16_t CH_VALUE;
	uint16_t CH_MIN;
	uint16_t CH_MAX;
	uint16_t CH_MID;
}POT_STRUCTS;

extern uint16_t ADC_CHANNELS[ADCH_CHANNEL_TOTAL];

void Set_ADC_Channel(POTS POT);




int16_t ABS_Limiter16(int16_t A,int16_t Threshold);



#endif /* SOURCES_DRIVERS_ADC_H_ */
