/*
 * Saved_Settings.h
 *
 *  Created on: Apr 6, 2016
 *      Author: Z
 */

#ifndef SOURCES_APPLICATION_SAVED_SETTINGS_H_
#define SOURCES_APPLICATION_SAVED_SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>
#include "IFsh1.h"

#define SECTOR_SIZE 0x800

typedef const struct
{
	union
	{
		const struct
		{
			const uint32_t I_AM_WRITTEN;
			const bool Mag_Cal_Complete;
			const float mag_max_x_F;
			const float mag_max_y_F;
			const float mag_max_z_F;
			const float mag_min_x_F;
			const float mag_min_y_F;
			const float mag_min_z_F;

		};
		const uint32_t Settings_Word_Data[512];
		const uint8_t Settings_Byte_Data[0x800];
	};
}SETTINGS_TYPE;


typedef struct
{
	union
	{
		struct
		{
			uint32_t I_AM_WRITTEN;
			bool Mag_Cal_Complete;
			float mag_max_x_F;
			float mag_max_y_F;
			float mag_max_z_F;
			float mag_min_x_F;
			float mag_min_y_F;
			float mag_min_z_F;

		};
		uint32_t Settings_Word_Data[512];
		uint8_t Settings_Byte_Data[0x800];
	};
}SETTINGS_TYPE_RAM;

extern const SETTINGS_TYPE My_Saved_Settings;
extern SETTINGS_TYPE_RAM My_Saved_Settings_RAM;

uint32_t isSettings_Saved();
uint8_t Save_Settings();
void Init_RAM_Settings();



#endif /* SOURCES_APP_SAVED_SETTINGS_H_ */


