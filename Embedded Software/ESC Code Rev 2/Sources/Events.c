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
	FailurePoint = 1<<10;
	TPM_PDD_ClearOverflowInterruptFlag(TPM1_DEVICE);
	//Handle_Starting_Sequence();
	Handle_Starting();
}

PE_ISR(TEST_IRQ) // PIT counter for scheduler, not related to motor control 
{
	//Time2++;
	FailurePoint = 1<<11;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;     // Enable timer
	PIT_PDD_ClearInterruptFlag(PIT_DEVICE,0);
	PIT_PDD_ClearInterruptFlag(PIT_DEVICE,1);

}

void Reset_TPM(uint16_t Set_Point)
{
	FailurePoint = 1<<19;
	TPM1_SC &=~(0x1<<3);
	TPM1_CNT = 1;
	TPM1_MOD = Set_Point;
	TPM1_SC |=(0x1<<3);
}

PE_ISR(TPM2_ISR) // Timer used for ZC time, is reset at the start of each ZC 
{
	FailurePoint = 1<<12;
	TPM_PDD_ClearOverflowInterruptFlag(TPM2_DEVICE);
	
	if(STARTING_SEQUENCE==AQUIRED_ZERO_CROSSING)
	{
		//STARTING_SEQUENCE = ALIGNMEANT_PHASE;
		//Reset_TPM(8000);
		Handle_Commutation();
	}
	else
	{
		STARTING_SEQUENCE = ALIGNMEANT_PHASE;
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






bool Is_Correct_Edge()
{
	if(PRIMARY_COMMUTATION & 0x1) // If phase is odd
	{
		if(CMP0_SCR & CMP_SCR_CFF_MASK)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(CMP0_SCR & CMP_SCR_CFF_MASK)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

}

static float filter = 1000;

static uint16_t edge_failure = 0;


/*
void CMP_Simple()
{
	Set_Pin(&LED,1);
	if(TPM2_CNT>100)
	{
		if(TPM2_CNT > Previous_Timing/10)
		{
			if(!ZeroFound)
			{
				if((PRIMARY_COMMUTATION==2)||(PRIMARY_COMMUTATION==3)||(PRIMARY_COMMUTATION==4))
				{
					//if(Is_Correct_Edge())
					//{
						filter = filter+(float)0.1*(TPM2_CNT - filter); 
						if(filter<100)
						{
							filter = 100; 
						}
						edge_failure = 0;
					//}
					//else
					//{
						//edge_failure++;
						//if(edge_failure>4)
						//{
						//	STARTING_SEQUENCE = ALIGNMEANT_PHASE;
						//}
					//}
				}
				//if(filter>15000)
				//{
				//	filter = 15000;
				//}
				Reset_TPM((uint16_t)filter-90);
				Previous_Timing = filter;
				ZeroFound = TRUE;
			}
		}
	}
	Set_Pin(&LED,0);
}
*/

static uint16_t Timeout = 1000;


void CMP_Simple()
{
	FailurePoint = 1<<14;
	if(TPM2_CNT>100)
	{
		if(TPM2_CNT > ((uint16_t)(Previous_Timing/10)))
		{
			FailurePoint = 1<<15;
			if(!ZeroFound)
			{
				FailurePoint = 1<<16;
				filter = filter+(float)0.1*(TPM2_CNT - filter); 
				if(filter<20)
				{
					filter = 20; 
				}
				if(filter>9000)
				{
					filter =9000;
				}
				FailurePoint = 1<<17;
				Reset_TPM((uint16_t)filter-20);
				Previous_Timing = filter;
				ZeroFound = TRUE;

			}
			}
		}
	}



void Multi_Sensor_Compare()
{
	//if(STARTING_SEQUENCE==AQUIRED_ZERO_CROSSING)
	if(STARTING_SEQUENCE==ALIGNMEANT_PHASE)
	{
		//Collect_ZC_Data(CMP_Is_Fallinge(CMP0_SCR));
		CMP_Simple();
		if(CMP0_SCR & CMP_SCR_CFF_MASK)
		{
			//ZeroCrosses[6] |= 1<<PRIMARY_COMMUTATION;
		}
		else
		{
			//ZeroCrosses[6] &=~(1<<PRIMARY_COMMUTATION);
		}
	}
}

#include "CMP_PDD.h"

PE_ISR(INT_CMP2)
{
	//Single_Sensor_Compare(); // Check for ZC 
	//CMP0_CR1 &=~CMP_CR1_EN_MASK;
	FailurePoint = 1<<13;

	if(CMP0_SCR & CMP_SCR_CFR_MASK)
	{
		CMP_PDD_ClearInterruptFlags(CMP0_DEVICE,CMP_SCR_CFR_MASK);
	}
	if(CMP0_SCR & CMP_SCR_CFF_MASK)
	{
		CMP_PDD_ClearInterruptFlags(CMP0_DEVICE,CMP_SCR_CFF_MASK);
	}
	CMP0_CR0 =0;
	CMP0_CR1 =0;
	
	
	FailurePoint = 1<<23;
	Multi_Sensor_Compare();
	FailurePoint = 1<<22;
	//CMP0_CR1 |=CMP_CR1_EN_MASK;
	CMP0_CR0 =0x7<<4;
	CMP0_CR1 =0x1<<4 | 0x1<<0;
	
	FailurePoint = 1<<31;
	
	
}

/*
** ===================================================================
**     Event       :  Cpu_OnLowVoltageINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when Low Voltage interrupt had occured.
**         This event is automatically enabled when either [LVD
**         interrupt] is set to 'Enabled' and [LVD reset] is set to
**         'Disabled' or [LVW interrupt] is set to 'Enabled'.
**     @param
**         Reason          - The parameter defines the reason of
**                           the low voltage interrupt. You can use
**                           predefined constants LVDSRC_* defined in
**                           generated PE_Const.h file to determine a
**                           reason of the last reset. See definition of
**                           these constants in this file for details.
*/
/* ===================================================================*/
void Cpu_OnLowVoltageINT(uint8_t Reason)
{
  /* Write your code here ... */
	SetPhase(0,0,0);
	Set_Outputs(0,0,0);
	Set_Pin(&LED,1);
	while(1);
}

/*
** ===================================================================
**     Event       :  Cpu_OnHardFault (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Hard Fault exception had
**         occurred. This event is automatically enabled when the [Hard
**         Fault] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnHardFault(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnSupervisorCall (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Supervisor Call exception had
**         occurred. This event is automatically enabled when the
**         [Supervisor Call] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnSupervisorCall(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnPendableService (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Pendable Service exception had
**         occurred. This event is automatically enabled when the
**         [Pendable Service] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnPendableService(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnLossOfLockINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when Loss of Lock interrupt had occured.
**         This event is automatically enabled when either [Loss of
**         lock interrupt] is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnLossOfLockINT(void)
{
  /* Write your code here ... */
}

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
