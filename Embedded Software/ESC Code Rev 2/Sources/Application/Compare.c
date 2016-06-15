/*
 * Compare.c
 *
 *  Created on: Feb 4, 2015
 *      Author: 5016zimmern
 */

#include "Compare.h"
#include "MKL25Z4.h"


#ifdef REV2
#define CMP_PHASE_A 	CMP_INPUT4 // See Schematic 
#define CMP_PHASE_B 	CMP_INPUT1
#define CMP_PHASE_C 	CMP_INPUT0
#endif

#ifdef REV1
#define CMP_PHASE_A 	CMP_INPUT1 // See Schematic 
#define CMP_PHASE_B 	CMP_INPUT0
#define CMP_PHASE_C 	CMP_INPUT4
#endif 

void inline CMP_OFF()
{
	CMP0_CR1 &=~CMP_CR1_EN_MASK;
}

void inline CMP_ON()
{
	CMP0_CR1 |=CMP_CR1_EN_MASK;
}


void inline CMP_Clear_Pos_Input()
{
	CMP0_MUXCR &=~(0x7<<CMP_MUXCR_PSEL_SHIFT); // writes select bits to 0
}

void inline Set_Positive_CMP_Input(CMP_INPUTS CMP_Input)
{
	CMP0_MUXCR |=(CMP_Input<<CMP_MUXCR_PSEL_SHIFT);
}

void inline Set_Edge_Trigger_Rising()
{
	CMP0_SCR &=~ (CMP_SCR_IEF_MASK | CMP_SCR_IER_MASK);
	CMP0_SCR |= CMP_SCR_IER_MASK;
}

void inline Set_Edge_Trigger_Falling()
{
	CMP0_SCR &=~ (CMP_SCR_IEF_MASK | CMP_SCR_IER_MASK);
	CMP0_SCR |= CMP_SCR_IEF_MASK;	
}

void inline Set_Both_Edge_Interrupts()
{
	CMP0_SCR |= CMP_SCR_IER_MASK | CMP_SCR_IEF_MASK;
}

void inline CMP_Enable_Phase_A(bool ER)
{
	CMP_OFF();
	CMP_Clear_Pos_Input();
	Set_Positive_CMP_Input(CMP_PHASE_A);
	//ER ? Set_Edge_Trigger_Rising() : Set_Edge_Trigger_Falling();
	CMP_ON();
}

void inline CMP_Enable_Phase_B(bool ER)
{
	CMP_OFF();
	CMP_Clear_Pos_Input();
	Set_Positive_CMP_Input(CMP_PHASE_B);
	//ER ? Set_Edge_Trigger_Rising() : Set_Edge_Trigger_Falling();
	CMP_ON();
}

void inline CMP_Enable_Phase_C(bool ER)
{
	CMP_OFF();
	CMP_Clear_Pos_Input();
	Set_Positive_CMP_Input(CMP_PHASE_C);
	//ER ? Set_Edge_Trigger_Rising() : Set_Edge_Trigger_Falling();
	CMP_ON();
}
