/* ###################################################################
**     Filename    : main.c
**     Project     : MarqDroneKL25Z
**     Processor   : MKL25Z128VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-09, 21:22, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "CS1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"

#include "PTD.h"
#include "SPI0.h"
#include "WAIT1.h"
#include "UTIL1.h"

#include "RNG1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"

#include "SPI1.h"

/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

#include <stdio.h>
#include <string.h>
#include "Drivers/FC.h"
#include "Drivers/External/MPU9250.h"
#include "Drivers/SPI.h"
#include "Schedule/Scheduler.h"
#include "Drivers/PWM.h"
#include "Drivers/LED_PWM.h"
#include "Drivers/External/cc2500.h"
#include "Application/RF.h"
#include "Drivers/ADC.h"
#include "PORT_PDD.h"
#include "MK22F51212.h"
#include <string.h>

#include "Application/ICL.h"
#include "Application/Saved_Settings.h"


#ifdef KL25Z

#include "TPM2.h"
#include "TPM1.h"
#include "TPM0.h"

#endif

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
uint8_t in_buffer[USB1_DATA_BUFF_SIZE];
uint8_t bufferZ[4]={0,0,0,0};

uint32_t i = 0;

char helloWorld[] = "TomSuxs";

volatile uint16_t value = 0;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	uint32_t testValue = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */


  Save_Settings();

  Init_FC_IO();
  GLED_STATES = LED_OFF;
  RLED_STATES = LED_FADE;
  Init_ADC();
  WAIT1_Waitms(100);
  USB1_Init();
  while(testValue<100) {
	WAIT1_Waitms(10);


	if(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))!=ERR_BUSOFF)
	{
		USB_RDY = 1;
		break;
	}
	testValue++;
   }
  Set_Pin(&BLUE_PIN,1);
  WAIT1_Waitms(10);
  Set_Pin(&BLUE_PIN,0);
  WAIT1_Waitms(10);
  Set_Pin(&BLUE_PIN,1);
  //Run_ICL_Test();
  Set_Pin(&BLUE_PIN,0);

  //while(1);

  InitRFData();
  Init_RAM_Settings();

      WAIT1_Waitms(1000);

      Save_Settings();


      //Set_Pin(&BLUE_PIN,0);

	  value = Read_MPU92500_Reg(WHO_AM_I_MPU9250);

      WAIT1_Waitms(10);

      Set_Pin(&BLUE_PIN,1);

  WAIT1_Waitms(100);


#ifndef SKIP_RF
  if(setup_cc2500() != PASS)
  {
	  while(1)
	  {
		  //Set_Pin(&RED_PIN,0);
		  Set_Pin(&BLUE_PIN,0);
	  }
  }
#endif

  if(Init_MPU())
  {

  }
  else
  {
	  while(1)
	  {
		  //Set_Pin(&RED_PIN,0);
		  Set_Pin(&BLUE_PIN,0);
		  MPU_Test_ID();
	  }
  }

  PORT_PDD_SetPinInterruptConfiguration(PORTC_BASE_PTR,8,PORT_PDD_INTERRUPT_ON_RISING);

  Start_Scheduler();

  while(1);

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
