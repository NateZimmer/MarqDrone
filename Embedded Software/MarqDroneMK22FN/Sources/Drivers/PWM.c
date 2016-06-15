/*
 * PWM.c
 *
 *  Created on: Dec 9, 2015
 *      Author: Z
 */

#include "Cpu.h"
#include "Events.h"
#include "GPIO.h"

#ifdef MK22FN
#include "Init_Config.h"
#include "PDD_Includes.h"
#endif

#ifdef KL25Z

#include "TPM_PDD.h"

#define FTM0_DEVICE TPM0_DEVICE
#define FTM1_DEVICE TPM1_DEVICE
#define FTM_PDD_CHANNEL_0 TPM_PDD_CHANNEL_0
#define FTM_PDD_CHANNEL_1 TPM_PDD_CHANNEL_1
#define FTM_PDD_CHANNEL_2 TPM_PDD_CHANNEL_2
#define FTM_PDD_CHANNEL_3 TPM_PDD_CHANNEL_3
#define FTM_PDD_WriteChannelValueReg TPM_PDD_WriteChannelValueReg

#endif


#include "PWM.h"


void Set_PWM_Reg(PWM_CHS PWM_CH,uint16_t Value)
{
	switch(PWM_CH)
	{
		case CH0:
			FTM_PDD_WriteChannelValueReg(FTM0_DEVICE,FTM_PDD_CHANNEL_0,Value);
			break;

		case CH1:
			FTM_PDD_WriteChannelValueReg(FTM0_DEVICE,FTM_PDD_CHANNEL_1,Value);
			break;

		case CH2:
			FTM_PDD_WriteChannelValueReg(FTM0_DEVICE,FTM_PDD_CHANNEL_2,Value);
			break;

		case CH3:
			FTM_PDD_WriteChannelValueReg(FTM0_DEVICE,FTM_PDD_CHANNEL_3,Value);
			break;

		default:
			break;
	}
}


/*
 * Sets PPM Channel between 1ms & 2ms
 */

#define PWM_FREQ	7500000UL // Set this to CLK
#define MIN_PWM		1000UL // 1ms, adjustable
#define MAX_PWM		2000UL

#define MIN_PWM_V		((((PWM_FREQ / 1000) * MIN_PWM) / 1000) - 1)
#define MAX_PWM_V		((((PWM_FREQ / 1000) * MAX_PWM) / 1000) - 1)
#define RANGE			(MAX_PWM_V - MIN_PWM_V)
#define	SCALE			1000 // 1000 degrees of resolution

volatile uint32_t PWM_FREQ_1 = 0x393870;
volatile uint32_t MIN_PWM_V1 =		(PWM_FREQ/1000UL) * (MIN_PWM / 1000UL) - 1UL;
volatile uint32_t MAX_PWM_V1 =		((uint32_t)PWM_FREQ/(uint32_t)1000) * ((uint32_t)MAX_PWM / 1000) - (uint32_t)1;
uint32_t RANGE1 =			MAX_PWM_V - MIN_PWM_V;
uint32_t SCALE1 =			1000; // 1000 degrees of resolution

void Set_PPM_Reg(PWM_CHS PWM_CH, uint32_t Value)
{
	volatile uint32_t PPM_Val = 0;
	if(Value>SCALE)
	{
		Value = SCALE;
	}

	if((FTM0_BASE_PTR->PWMLOAD & (0x1<<9))==0) // Ensure load bit is set, unsure why this is getting cleared.
	{
		FTM0_BASE_PTR->PWMLOAD |= (0x1<<9);
	}
	PPM_Val = RANGE * Value;
	PPM_Val = PPM_Val / SCALE + MIN_PWM_V;
	Set_PWM_Reg(PWM_CH,PPM_Val);
}

