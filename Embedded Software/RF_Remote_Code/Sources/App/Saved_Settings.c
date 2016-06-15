/*
 * Saved_Settings.c
 *
 *  Created on: Jan 3, 2016
 *      Author: Z
 */


#include "Saved_Settings.h"
#include "IFsh1.h"

__attribute__ ((aligned(0x400)))
const SETTINGS_TYPE My_Saved_Settings  = {
		0, // Profile Length
		0, // Profile Points
};



SETTINGS_TYPE_RAM My_Saved_Settings_RAM;

SETTINGS_TYPE_RAM * SS = (SETTINGS_TYPE_RAM *)(&My_Saved_Settings); // Normally I shouldn't need to create this pointer but KDS is being retarded when i'm attempting to read the flash.


uint32_t isSettings_Saved()
{
	volatile uint32_t returnValue = 0;
	returnValue = SS->I_AM_WRITTEN;
	return returnValue;
}

uint8_t Sector_Write(SETTINGS_TYPE * Settings_PTR)
{
	byte Error_Code = 0;
	Error_Code = IFsh1_EraseSector((IFsh1_TAddress)(&Settings_PTR->Settings_Byte_Data));
	Error_Code =IFsh1_SetBlockFlash(My_Saved_Settings_RAM.Settings_Byte_Data,(IFsh1_TAddress)(&Settings_PTR->Settings_Byte_Data),SECTOR_SIZE);
	return Error_Code;
}

uint8_t Save_Settings()
{
	uint8_t Error_Code = 0;
	Error_Code = Sector_Write(&My_Saved_Settings);
	return Error_Code;
}


void Init_RAM_Settings()
{
	if(isSettings_Saved())
	{
		for(int i = 0;i<SECTOR_SIZE;i++)
		{
			My_Saved_Settings_RAM.Settings_Byte_Data[i] = SS->Settings_Byte_Data[i];
		}
	}
	My_Saved_Settings_RAM.I_AM_WRITTEN=1;
}


