/* ###################################################################
**     Filename    : Events.c
**     Project     : ESC_Code
**     Processor   : MKL25Z64VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-28, 20:20, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

#include "PIT.h"
#include "PIT_PDD.h"


/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


void AD1_OnEnd(void)
{
  /* Write your code here ... */
	//GPIOB_PTOR = (0x1<<19);
}

//TPM1_ISR
#include "TPM_PDD.h"
#include "../Sources/Application/Timer_App.h"
#include "Drivers/ESC.h"
#include "Application/Compare.h"

uint16_t counter2 = 0;


#define MAX_SPEED 1000

volatile int i = 0; 
volatile int j = 0; 

PE_ISR(TPM1_ISR) // This ISR controls the gate signals periodically. Period is determined by zero crossings 
{
	TPM_PDD_ClearOverflowInterruptFlag(TPM1_DEVICE);
	//Handle_Starting_Sequence();
	Handle_Starting();
}

PE_ISR(TEST_IRQ) // PIT counter for scheduler, not related to motor control 
{
	//Time2++;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;     // Enable timer
	PIT_PDD_ClearInterruptFlag(PIT_DEVICE,0);
	PIT_PDD_ClearInterruptFlag(PIT_DEVICE,1);

}

void Reset_TPM(uint16_t Set_Point)
{
	TPM1_SC &=~(0x1<<3);
	TPM1_CNT = 1;
	TPM1_MOD = Set_Point;
	TPM1_SC |=(0x1<<3);
}

PE_ISR(TPM2_ISR) // Timer used for ZC time, is reset at the start of each ZC 
{
	TPM_PDD_ClearOverflowInterruptFlag(TPM2_DEVICE);
	
	if(STARTING_SEQUENCE!=ALIGNMEANT_PHASE)
	{
		//STARTING_SEQUENCE = ALIGNMEANT_PHASE;
		//Reset_TPM(8000);
		Handle_Commutation();
	}
	

}

bool Is_Rising_ZC() // is ZC from low to high or high to low 
{
	bool Return_Value = FALSE;
	if((uint16_t)PRIMARY_COMMUTATION & 0x1)
		Return_Value = TRUE; 
	return Return_Value;
}

#define Timing_Rejection 15 //10%


bool CMP_Is_Fallinge(uint32_t CMP0_Source)
{
	bool Return_Value = FALSE;
	if((CMP0_Source & CMP_SCR_CFF_MASK) == CMP_SCR_CFF_MASK)
	{
		Return_Value = TRUE;
	}
	return Return_Value;
}

#include "PTB.h"

static uint16_t Previous_Timing = 5000;


#include "TPM_PDD.h"


static float filter = 0;

void CMP_Simple()
{
	if(TPM2_CNT>100)
	{
		if(TPM2_CNT > Previous_Timing/10)
		{
			if(!ZeroFound)
			{
				filter = filter+(float)0.1*(TPM2_CNT - filter); 
				if(filter<20)
				{
					filter = 20; 
				}
				Reset_TPM((uint16_t)filter-20);
				Previous_Timing = filter;
				ZeroFound = TRUE;
				GPIOB_PCOR = (0x1<<17); // 2L Extern // Top Left
			}
		}
	}
}


void Multi_Sensor_Compare()
{
	if(STARTING_SEQUENCE==AQUIRED_ZERO_CROSSING)
	{
		//Collect_ZC_Data(CMP_Is_Fallinge(CMP0_SCR));
		CMP_Simple();
	}
	
}

PE_ISR(INT_CMP2)
{
	//Single_Sensor_Compare(); // Check for ZC 
	Multi_Sensor_Compare();
	CMP0_SCR |= CMP_SCR_CFR_MASK + CMP_SCR_CFF_MASK; // Reset Flag
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
