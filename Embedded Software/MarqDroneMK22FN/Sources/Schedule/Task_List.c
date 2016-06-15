/*
 * Task_List.c
 *
 *  Created on: Aug 30, 2014
 *      Author: Nate
 */

#include "Task_List.h"
#include "../Drivers/External/MPU9250.h"
#include "../Drivers/LED_PWM.h"
#include <stdio.h>
#include "../Application/Commands.h"
#include "../Drivers/External/cc2500.h"
#include "../Drivers/External/cc.h"
#include "../Application/RF.h"
uint8_t newBuff[40];

#define MS_10_TASK		(0x1<<0)
#define MS_20_TASK		(0x1<<1)
#define MS_40_TASK		(0x1<<2)
#define MS_80_TASK		(0x1<<3)
#define MS_160_TASK		(0x1<<4)
#define MS_320_TASK		(0x1<<5)
#define MS_640_TASK		(0x1<<6)
#define MS_1280_TASK	(0x1<<7)

uint8_t NewBuff[5]={4,0,0,0,0};

void Run_Default_Task()
{
	Handle_Incoming_Packets();
}

void Run_5MS_Task()
{

}

void Run_10MS_Task()
{

	//if(Fast_Data_Enable)
	//{
	//	Get_Data();
	//}
}

void Run_20MS_Task()
{
	Handle_LED_Fade();
}

void Run_40MS_Task()
{

}

void Run_80MS_Task()
{
	volatile uint8_t ReadStatusValue = 0;
	  ReadStatusValue = cc_read_status(TI_CCxxx0_MARCSTATE);

	  ReadStatusValue++;
}


void Run_160MS_Task()
{
	handleRadioCore();
}

void Run_320MS_Task()
{

}

void Run_640MS_Task()
{
	//cc2500_tx(NewBuff, 5);

}

void Run_1280MS_Task()
{
	 handleRFKeepAlive();
}
