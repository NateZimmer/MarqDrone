/*
 * Saved_Settings.h
 *
 *  Created on: Jan 3, 2016
 *      Author: Z
 */

#ifndef SOURCES_APP_SAVED_SETTINGS_H_
#define SOURCES_APP_SAVED_SETTINGS_H_

#include "../Drivers/ADC.h"
#include "IMU_Data.h"

#define SECTOR_SIZE 0x400

typedef const struct
{
	union
	{
		const struct
		{
			const uint32_t I_AM_WRITTEN;
			const bool MidPointCalDone;
			const bool MinMaxCalDone;
			const POT_STRUCTS POT_STRUCT[ADCH_CHANNEL_TOTAL];
		};
		const uint32_t Settings_Word_Data[256];
		const uint8_t Settings_Byte_Data[0x400];
	};
}SETTINGS_TYPE;

typedef struct
{
	union
	{
		struct
		{
			uint32_t I_AM_WRITTEN;
			bool MidPointCalDone;
			bool MinMaxCalDone;
			POT_STRUCTS POT_STRUCT[ADCH_CHANNEL_TOTAL];
		};
		uint32_t Settings_Word_Data[256];
		uint8_t Settings_Byte_Data[0x400];
	};
}SETTINGS_TYPE_RAM;

extern const SETTINGS_TYPE My_Saved_Settings;
extern SETTINGS_TYPE_RAM My_Saved_Settings_RAM;

uint32_t isSettings_Saved();
uint8_t Save_Settings();
void Init_RAM_Settings();



#endif /* SOURCES_APP_SAVED_SETTINGS_H_ */
