/*
 * Compare.c
 *
 *  Created on: Feb 4, 2015
 *      Author: 5016zimmern
 */

#include "Compare.h"
#include "MKL25Z4.h"

//Phase A --> Channel 0
//Phase B --> Channel 1
//Phase C --> Channel 4
//Neutral --> Channel 5

void CMP_Enable_Phase_B()
{
	CMP0_MUXCR &=~((0x7)<<CMP_MUXCR_PSEL_SHIFT);
}

void CMP_Enable_Phase_A()
{
	CMP0_MUXCR &=~(0x7<<CMP_MUXCR_PSEL_SHIFT);
	CMP0_MUXCR |=(0x1<<CMP_MUXCR_PSEL_SHIFT);
}

void CMP_Enable_Phase_C()
{
	CMP0_MUXCR &=~(0x7<<CMP_MUXCR_PSEL_SHIFT);
	CMP0_MUXCR |=(0x4<<CMP_MUXCR_PSEL_SHIFT);
}

