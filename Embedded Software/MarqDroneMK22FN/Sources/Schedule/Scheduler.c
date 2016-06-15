/*
 * Scheduler.c
 *
 *  Created on: Aug 30, 2014
 *      Author: Nate
 */

#include "Scheduler.h"
#include "../Application/USB.h"
#include "Task_List.h"
#include "Cpu.h"
#include "Events.h"
#include "../Drivers/TPM0.h"
#include "../Application/USB.h"
#include "../Drivers/FC.h"
#include "../Application/RF.h"
#include "../Drivers/External/MPU9250.h"

#ifdef MK22FN
#include "Init_Config.h"
#include "PDD_Includes.h"
#endif



#define MS_10_TASK		(0x1<<0)
#define MS_20_TASK		(0x1<<1)
#define MS_40_TASK		(0x1<<2)
#define MS_80_TASK		(0x1<<3)
#define MS_160_TASK		(0x1<<4)
#define MS_320_TASK		(0x1<<5)
#define MS_640_TASK		(0x1<<6)
#define MS_1280_TASK	(0x1<<7)

void run_scheduler(uint8_t current_tick)
{
	if(current_tick & MS_10_TASK)
	{
		Run_10MS_Task();
	}
	else if(current_tick & MS_20_TASK)
	{
		Run_20MS_Task();
	}
	else if(current_tick & MS_40_TASK)
	{
		Run_40MS_Task();
	}
	else if(current_tick & MS_80_TASK)
	{
		Run_80MS_Task();
	}
	else if(current_tick & MS_160_TASK)
	{
		Run_160MS_Task();
	}
	else if(current_tick & MS_320_TASK)
	{
		Run_320MS_Task();
	}
	else if(current_tick & MS_640_TASK)
	{
		Run_640MS_Task();
	}
	else if(current_tick & MS_1280_TASK)
	{
		Run_1280MS_Task();
	}
}

void Check_Scheduler()
{
	static uint8_t previous_ticks=0;

	if(previous_ticks != Get_System_Tick())
	{
		run_scheduler(previous_ticks);
		Run_5MS_Task();
		previous_ticks++;

	}

	Run_Default_Task();
	Handle_USB();
	//Set_Pin(&RED_PIN,0);
	//IMU_Filter();
	//Set_Pin(&RED_PIN,1);
}

void Start_Scheduler()
{
	while(1)
	{
		Check_Scheduler();
	}
}





