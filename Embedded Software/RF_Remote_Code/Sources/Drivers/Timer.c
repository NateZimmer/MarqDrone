/*
 * Timer.c
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */

#include "Timer.h"
#include "MKL25Z4.h"
#include "GPIO.h"

static uint8_t System_Tick = 0;
uint32_t CPU_Tick = 0;
uint32_t CPU_USAGE = 0;

/*
void TPM1_ISR()
{
	TPM1_SC   |= TPM_SC_TOF_MASK;
	System_Tick++;
}
*/


#define COUNTS_PER_255_TICKS 612000 // calculated in SMATH

PE_ISR(TPM1_ISR)
{
	TPM1_SC   |= TPM_SC_TOF_MASK;
	System_Tick++;
	if(System_Tick==0xFF) // 255 Ticks * 5 ms = 1.275 seconds. 1.275 seconds
	{
		CPU_USAGE = CPU_Tick / COUNTS_PER_255_TICKS;
		CPU_USAGE = 100 - CPU_USAGE;
		CPU_Tick = 0;
	}
}


uint8_t Get_System_Tick()
{
	return System_Tick;
}


PE_ISR(TPM2_ISR)
{
	TPM2_SC   |= TPM_SC_TOF_MASK;
}


