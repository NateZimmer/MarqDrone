/*
 * PWM.c
 *
 *  Created on: Dec 9, 2015
 *      Author: Z
 */

#include "Cpu.h"
#include "Events.h"
#include "TPM_PDD.h"
#include "PWM.h"


void Set_PWM_Reg(PWM_CHS PWM_CH,uint16_t Value)
{
	switch(PWM_CH)
	{
		case CH0:
			TPM_PDD_WriteChannelValueReg(TPM2_DEVICE,TPM_PDD_CHANNEL_0,Value);
			break;

		case CH1:
			TPM_PDD_WriteChannelValueReg(TPM2_DEVICE,TPM_PDD_CHANNEL_1,Value);
			break;

		case CH2:
			TPM_PDD_WriteChannelValueReg(TPM2_DEVICE,TPM_PDD_CHANNEL_2,Value);
			break;

		default:
			break;
	}
}
