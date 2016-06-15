/* ###################################################################
**     Filename    : main.c
**     Project     : RF_Remote_Code
**     Processor   : MKL25Z64VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-26, 10:21, # CodeGen: 0
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
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CS1.h"
#include "TPM1.h"
#include "PTD.h"
#include "ADC0.h"
#include "SPI0.h"
#include "WAIT1.h"
#include "TPM2.h"
#include "RNG1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "PTC.h"
#include "ADC_PDD.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Drivers/Remote.h"
#include "Drivers/Timer.h"
#include "App/Scheduler.h"
#include "External/cc2500.h"
#include "App/IMU_Data.h"
#include "Drivers/USB_Echo.h"
#include "Drivers/ADC.h"
#include "App/Saved_Settings.h"

uint8_t spi_initialized = 0;
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
//PTD_Init();
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  Setup_Remote_IO();
  WAIT1_Waitms(100);
  uint32_t testValue = 0;
  testValue =isSettings_Saved();



  if(testValue==0)
  {
	  //Set_Pin(&BLUE_LED,0);
  }
  else
  {
	  //Set_Pin(&BLUE_LED,1);
  }

  while(testValue<100) {
	WAIT1_Waitms(10);
	if(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))!=ERR_BUSOFF)
	{
		break;
	}
	testValue++;
   }
  USB_INIT = true;
  debug_console("USB INIT\r\n");
  Init_IMU_Data();
  Init_RAM_Settings();
  if(!TestParseInput())
  {
	  while(1);
  }

  if(!TestPacketEngine())
  {
	  while(1);
  }

  if(setup_cc2500())
  {
	  Set_Pin(&RED_LED,0);
	  while(1); // If init fails, halt startup.
  }
  debug_console("Radio core online!\r\n");

  spi_initialized = 1;



//  ADC_PDD_StartCalibration(ADC0_DEVICE);/


  Start_Scheduler();

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
