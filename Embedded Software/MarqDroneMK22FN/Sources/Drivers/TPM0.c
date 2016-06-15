/*
 * TPM0.c
 *
 *  Created on: Nov 16, 2015
 *      Author: Z
 */

#include "Cpu.h"
#include "Events.h"
#include "GPIO.h"
#include "../Application/Flight.h"

#ifdef MK22FN
#include "Init_Config.h"
#include "PDD_Includes.h"
#endif

uint32_t tenuS = 0;


uint8_t SystemTick = 0;

uint32_t Get_System_Tick()
{
	return SystemTick;
}

#ifdef KL25Z

PE_ISR(TPM2_ISR)
{
	SystemTick++;
	TPM2_SC   |= TPM_SC_TOF_MASK;
	updateQuadControl();
}
#endif


#ifdef MK22FN

PE_ISR(FT1)
{
	//SystemTick++;
	FTM_PDD_ClearOverflowInterruptFlag(FTM1_DEVICE);
}




void Pull_ESC_Outputs_Low()
{
	PORT_PCR_REG(PORTC_BASE_PTR,4) = OUTPUT_EN;
	PORT_PCR_REG(PORTC_BASE_PTR,3) = OUTPUT_EN;
	PORT_PCR_REG(PORTC_BASE_PTR,2) = OUTPUT_EN;
	PORT_PCR_REG(PORTC_BASE_PTR,1) = OUTPUT_EN;
	GPIOC_PDDR |= (0x0F<<1);
	GPIOC_PCOR = (0x0F<<1);
}


PE_ISR(FTM_ISR)
{
	Pull_ESC_Outputs_Low();
	FTM0_BASE_PTR->SC &= ~(0x1<<3);
	FTM0_BASE_PTR->CNT = 0;
	FTM0_BASE_PTR->PWMLOAD |= (0x1<<9);
	tenuS++;
	FTM_PDD_ClearChannelInterruptFlag(FTM0_DEVICE,FTM_PDD_CHANNEL_4);
	FTM_PDD_ClearOverflowInterruptFlag(FTM0_DEVICE);
	//FTM_PDD_SetFTMEnable(FTM0_DEVICE,PDD_DISABLE);

}

PE_ISR(FT2)
{
	tenuS++;
	FTM_PDD_ClearOverflowInterruptFlag(FTM2_DEVICE);
}

void Enable_ESC_Outputs()
{
	PORT_PCR_REG(PORTC_BASE_PTR,1) = PORT_PCR_MUX(4);
	PORT_PCR_REG(PORTC_BASE_PTR,2) = PORT_PCR_MUX(4);
	PORT_PCR_REG(PORTC_BASE_PTR,3) = PORT_PCR_MUX(4);
	PORT_PCR_REG(PORTC_BASE_PTR,4) = PORT_PCR_MUX(4);
}

PE_ISR(FT3)
{
	SystemTick++;
	FTM_PDD_ClearOverflowInterruptFlag(FTM3_DEVICE);
	updateQuadControl();
	Enable_ESC_Outputs();
	FTM0_BASE_PTR->SC |= (0x1<<3);
}


#endif

