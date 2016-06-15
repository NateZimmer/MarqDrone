/* ###################################################################
**     Filename    : Events.c
**     Project     : RF_Remote_Code
**     Processor   : MKL25Z64VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-26, 10:21, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
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
#include "PORT_PDD.h"
#include "Drivers/GPIO.h"
#include "Drivers/Remote.h"
#include "string.h"
#include "External/cc2500.h"
#include "External/cc.h"
#include "ADC_PDD.h"
#include "Drivers/USB_Echo.h"
#include "App/IMU_Data.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

extern uint8_t spi_initialized;

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
 * ====================================================================
 * 		Event		:	INT_PORTD
 */
/*!
 * 		@brief
 * 			This interrupt occurs on the falling edge of PTD.4
 */
void PTD_ISR(void) {
	 uint8_t length = CC2500_BUFFER_LENGTH;
	 static uint8_t p_rx_buffer[CC2500_BUFFER_LENGTH];
	 uint32_t interrupts = PORT_PDD_GetInterruptFlags(PTD_PORT_DEVICE);




	 // Careful reading spi data in here. Was getting garbage data.
	 if (interrupts & GDO0_PIN && spi_initialized)
	 {
		 //Toggle_Pin(&BLUE_LED);
		 packet_recieved = true;
	 }





	  // Check to see if this interrupt was caused by the GDO0 pin from the CC2500
//	  if ( PORT_PDD_GetPinInterruptFlag(PTD_PORT_DEVICE, GDO0_PIN) )

	 /*
	 if (interrupts & GDO0_PIN && spi_initialized)
	  {
		 //debug_console("Seeing RF ISR\r\n");
	      if( receive_packet_fixed_length( p_rx_buffer,6,false))
	      {
	        // Successful packet receive, now send data to callback function
	        //if( rx_callback( p_rx_buffer, length ) )
	        //{
	          // If rx_callback returns nonzero, wakeup the processor
	          //__bic_SR_register_on_exit(LPM1_bits);
	        //}

	        // Clear the buffer

	    	  //writeStringTXD(TX_Buff, &uartTypes);
	    	  //writeChar(p_rx_buffer[1]);
	    	  RF_Keep_Alive = true;
	    	  //Toggle_Pin(&BLUE_LED);
	    	  //Toggle_Pin(&RED_LED);
	        memset( p_rx_buffer, 0x00, sizeof(p_rx_buffer) );
	      }
	      else
	      {
//	         A failed receive can occur due to bad CRC or (if address checking is
//	         enabled) an address mismatch
//
//	        uart_write("CRC NOK\r\n", 9);
	      }

	  }
	 */

	  PORT_PDD_ClearInterruptFlags(PTD_PORT_DEVICE, 0xFFFF);

//	  GDO0_PxIFG &= ~GDO0_PIN;  // Clear interrupt flag

	  // Only needed if radio is configured to return to IDLE after transmission
	  // Check register MCSM1.TXOFF_MODE
	  // cc_strobe(TI_CCxxx0_SRX); // enter receive mode again
}


void ADC0_ISR(void) {
//	ADC_PDD_ReadDataResultReg(ADC0_DEVICE, RA);
//	ADC_PDD_StartCalibration(ADC0_DEVICE);

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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
