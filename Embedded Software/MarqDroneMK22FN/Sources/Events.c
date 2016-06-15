/* ###################################################################
**     Filename    : Events.c
**     Project     : MarqDroneKL25Z
**     Processor   : MKL25Z128VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-09, 21:22, # CodeGen: 0
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
#include "Init_Config.h"
#include "PDD_Includes.h"
#include "Drivers/FC.h"

#include "Drivers/External/cc2500.h"
#include "Drivers/External/cc.h"
#include "Application/RF.h"
#include "PTD.h"
#include "PORT_PDD.h"
#include "Drivers/External/MPU9250.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

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

void PTC_ISR(void)
{
	 uint32_t interrupts = PORT_PDD_GetInterruptFlags(PORTC_BASE_PTR);
	 if(interrupts == (0x1<<8))
	 {
		 tryGetIMUData();
		 Toggle_Pin(&A1);
	 }

#ifdef MK22FN
	 PORT_PDD_ClearInterruptFlags(PORTC_BASE_PTR,0xFFFF);
#endif

#ifdef KL25Z
	 PORT_PDD_ClearInterruptFlags(PTD_PORT_DEVICE, 0xFFFF);
#endif

}


void PTD_ISR(void)
{
	 uint32_t interrupts = PORT_PDD_GetInterruptFlags(PORTD_BASE_PTR);


	  // Check to see if this interrupt was caused by the GDO0 pin from the CC2500
//	  if ( PORT_PDD_GetPinInterruptFlag(PTD_PORT_DEVICE, GDO0_PIN) )
	 if (interrupts & GDO0_PIN && CC_2500_SETUP_DONE)
	  {
		 packet_recieved = true;
		/*
		 if( receive_packet(p_rx_buffer,&length) )
	      {
		     //Toggle_Pin(&BLUE_PIN);
		     RF_Keep_Alive = true;
	        // Successful packet receive, now send data to callback function
	        //if( rx_callback( p_rx_buffer, length ) )
	        //{
	          // If rx_callback returns nonzero, wakeup the processor
	          //__bic_SR_register_on_exit(LPM1_bits);
	        //}

	        // Clear the buffer

	    	  //writeStringTXD(TX_Buff, &uartTypes);
	    	  //writeChar(p_rx_buffer[1]);

	        memset( p_rx_buffer, 0x00, sizeof(p_rx_buffer) );
	      }
	      else
	      {
//	         A failed receive can occur due to bad CRC or (if address checking is
//	         enabled) an address mismatch
//
//	        uart_write("CRC NOK\r\n", 9);
	      }
	      */

	  }
#ifdef MK22FN
	 PORT_PDD_ClearInterruptFlags(PORTD_BASE_PTR,0xFFFF);
#endif

#ifdef KL25Z
	 PORT_PDD_ClearInterruptFlags(PTD_PORT_DEVICE, 0xFFFF);
#endif


	//PORT_PDD_ClearInterruptFlags(PTD_PORT_DEVICE,0xFFFF);


}


uint8_t UART_BUFFER[100];

#define START_LIDAR 0xFA
#define PACKET_LENGTH 22


typedef struct
{
	union
	{
		struct
		{
			uint8_t StartByte;
			uint8_t Index;
			uint8_t SpeedLow;
			uint8_t SpeedHigh;
			uint8_t Speed[16];
			uint8_t ChecksumL;
			uint8_t ChecksumH;
		};
		uint8_t LidarRaw[PACKET_LENGTH];
	};
}LIDAR_PACKETS;

LIDAR_PACKETS LIDAR_PACKET;


uint16_t LidarData[360];

uint32_t RPM = 0;

void ParseLidarPacket()
{
	uint16_t Distance = 0;
	uint16_t Index = 0;
	do
	{
		if(LIDAR_PACKET.Index < 0xA0)
			break;
		LIDAR_PACKET.Index -= 0xA0;


		if(LIDAR_PACKET.Index==5)
		{
			 Toggle_Pin(&BLUE_PIN);
		}

		for(int i = 0; i<4;i++)
		{
			Index = LIDAR_PACKET.Index*4 + i;
			if( (LIDAR_PACKET.Speed[i*4+1] & 0x80) ==0)
			{
				Distance = (LIDAR_PACKET.Speed[i*4+1] & 0xC)<<8; // Upper 6 bits
				Distance += LIDAR_PACKET.Speed[i*4]; // Lower 8 bits
				LidarData[Index] = Distance;
			}
			else
			{
				LidarData[Index] = 0;
			}
			//sprintf(UART_BUFFER,"%d,%d\r\n",Index,LidarData[Index]);
			//if(USB_RDY)
			//{
			//	Write_CDC_String(UART_BUFFER);
			//}
		}

	}while(0); // State machine break, todo add checksum check above



}

void PointStateMachine(uint8_t Data)
{
	static bool StartRecieved = FALSE;
	static uint8_t Packet_Index = 0;

	if(Data == START_LIDAR)
	{
		StartRecieved = TRUE;
	}

	if(StartRecieved)
	{
		LIDAR_PACKET.LidarRaw[Packet_Index] = Data;
		Packet_Index++;
		if(Packet_Index>(PACKET_LENGTH-1))
		{
			Packet_Index = 0;
			StartRecieved = false;
			ParseLidarPacket();
		}
	}

}

void UARTRX()
{
	static uint32_t index = 0;
	uint8_t Data = 0;
	uint8_t Data2 = 0;
	//Toggle_Pin(&BLUE_PIN);

	Data2 = UART_PDD_ReadStatus1Flags(UART0_DEVICE);
	Data=  UART_PDD_GetChar8(UART0_DEVICE);

	PointStateMachine(Data);

	if(index<100)
	{
		UART_BUFFER[index]=Data;
	}

	index++;

	UART_PDD_ClearInterruptFlags(UART0_DEVICE,Data2);

}










/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK22FN512LH12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void)
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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
