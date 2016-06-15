/*
 * Task_List.c
 *
 *  Created on: Aug 30, 2014
 *      Author: Nate
 */

#include "Task_List.h"
#include "../Drivers/Timer.h"
#include "../Drivers/USB_Echo.h"
#include "../Drivers/GPIO.h"
#include "../Drivers/Remote.h"
#include "../External/cc2500.h"
#include "../Drivers/LED_PWM.h"
#include "../External/cc.h"
#include "../App/IMU_Data.h"
#include "../App/RF_Control.h"
#include "Joystick.h"
#include "CDC1.h"
#include "RNG1.h"
#include "Drivers/ADC.h"
#include "USB1.h"
#include <stdio.h>

#include "MKL25Z4.h"

#define MS_10_TASK		(0x1<<0)
#define MS_20_TASK		(0x1<<1)
#define MS_40_TASK		(0x1<<2)
#define MS_80_TASK		(0x1<<3)
#define MS_160_TASK		(0x1<<4)
#define MS_320_TASK		(0x1<<5)
#define MS_640_TASK		(0x1<<6)
#define MS_1280_TASK	(0x1<<7)

uint8_t NewBuff[6]={1,2,3,4,5,6};

#define TEMP_BUFF_SIZE 60
uint8_t rBuff[TEMP_BUFF_SIZE] = {0,0,0,0,0,0,0,0,0,0};

volatile uint32_t packet_error = 0;

void Fill_Ring_Buffer(uint8_t size,uint8_t * Buffer)
{
	for(int i = 0; i < size; i++)
	{
		RNG1_Put(Buffer[i]);
	}
}


#define CC2500_BUFFER_OVERFLOW (0x1<<7)

void Run_Default_Task()
{
  volatile uint8_t ReadStatusValue = 0;
  volatile uint8_t ReadStatusValue1 =0;
  volatile uint8_t wtf = 0;
	//Handle_USB_Read();

	static uint8_t prevBuf = 0;
	uint8_t buffer_byte = 0;

	if(packet_recieved) // ISR has set the PR flag which means the GDO sensed a packet has been recieved
	{
		if(OK_TO_TRANSMIT)
		{
			ReadStatusValue1 = cc_read_status( TI_CCxxx0_RXBYTES );
			ReadStatusValue = cc_read_status( TI_CCxxx0_RXBYTES );

			if(ReadStatusValue1==0)
			{
				wtf++; // This would indicate a CRC failure assuming auto flush worked
			}
			else if(ReadStatusValue1 & CC2500_BUFFER_OVERFLOW)
			{
				Quick_Reset_Core();
				wtf++; // WTF
				if(wtf>100)
				{
					wtf=0; // Seriously WTF
				}
				//Toggle_Pin(&BLUE_LED);
			}
			else if(ReadStatusValue1<TEMP_BUFF_SIZE)
			{
				receive_packet_fixed_length( rBuff, ReadStatusValue1,false);
				Fill_Ring_Buffer(ReadStatusValue1,rBuff);

			}
			else
			{
				receive_packet_fixed_length( rBuff, TEMP_BUFF_SIZE,false);
				Fill_Ring_Buffer(TEMP_BUFF_SIZE,rBuff);
			}
			while(RNG1_NofElements())
			{
				RNG1_Get(&buffer_byte);
				Packet_State(buffer_byte);
			}
			 ReadStatusValue1 = cc_read_status( TI_CCxxx0_RXBYTES );
			 packet_recieved = false;
			 //debug_console(sendBuff);
		}
	}
	//Toggle_Pin(&BLUE_LED); //IDLE TASK LED
	// Chip reccomends a interrupt driven solution, repeatidly polling as above is non ideal. Will try avoiding this route.
}



void Run_5MS_Task()
{

	if((GPIOC_PDIR & ((0x1<<8))) == 0)
	{
		if(Global_Flight_Mode != NO_CONNECTION)
		{
			debug_console("MSG,Flight Off Pressed\r\n");
			Global_Flight_Mode = RF_LINK_CONNECTED;
		}
	}
	Handle_Button_Presses();





}

void Run_10MS_Task()
{
	//cc2500_tx(NewBuff, 6);
	HandleADC();
	HandleRF_Outgoing_Link();
}

void Run_20MS_Task()
{
	Handle_LEDs();
	Handle_ADC_Cals();
}

void Run_40MS_Task()
{
	//handleRadioCore();

}

void Run_80MS_Task()
{
	
}

void Run_160MS_Task()
{
	Handle_RF_Status();
}

void Run_320MS_Task()
{

}

void Run_640MS_Task()
{
	Toggle_Pin(&POWER_LED);
	Handle_LED_States();
	handleRFKeepAlive();
}

void Run_1280MS_Task()
{
	handleRadioCore();
	Handle_Packet_Rate();
}
