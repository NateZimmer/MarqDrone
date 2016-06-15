/*
 * Joystick.c
 *
 *  Created on: Jan 3, 2016
 *      Author: Z
 */

#include "Joystick.h"
#include "Saved_Settings.h"

bool POT_Min_Max_Cal = false;
bool POT_Mid_Cal = false;
bool POT_CAL_Done = false;

int16_t Roll_Offset = 0;
int16_t Pitch_Offset = 0;


void Init_Joystick_Values(uint8_t Reset_Mid)
{

	if(Reset_Mid)
	{
		for(int i =0;i<ADCH_CHANNEL_TOTAL;i++)
		{
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MID =0;
		}
	}
	else
	{
		for(int i =0;i<ADCH_CHANNEL_TOTAL;i++)
		{
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MAX =0x0;
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MIN =0xFFFF;
		}
	}

}


/*
 * Handle_Min_Max_Check()
 * When in cal mode, min and max values will be updated
 */

void Handle_Min_Max_Check()
{
	//Init_Joystick_Values(0); // Reset min/max
	if(POT_Min_Max_Cal)
	{
		for(int i =0;i<ADCH_CHANNEL_TOTAL;i++)
		{
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MAX = (My_Saved_Settings_RAM.POT_STRUCT[i].CH_MAX<My_Saved_Settings_RAM.POT_STRUCT[i].CH_VALUE) ? My_Saved_Settings_RAM.POT_STRUCT[i].CH_VALUE : My_Saved_Settings_RAM.POT_STRUCT[i].CH_MAX;
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MIN = (My_Saved_Settings_RAM.POT_STRUCT[i].CH_MIN>My_Saved_Settings_RAM.POT_STRUCT[i].CH_VALUE) ? My_Saved_Settings_RAM.POT_STRUCT[i].CH_VALUE : My_Saved_Settings_RAM.POT_STRUCT[i].CH_MIN;
		}
	}
}

/*
 * Handle_Mid_Check()
 * When in cal mode,
 */

void Handle_Mid_Check()
{
	//Init_Joystick_Values(1); // Reset mid
	if(POT_Mid_Cal)
	{
		for(int i =0;i<ADCH_CHANNEL_TOTAL;i++)
		{
			My_Saved_Settings_RAM.POT_STRUCT[i].CH_MID = My_Saved_Settings_RAM.POT_STRUCT[i].CH_VALUE;
		}
	}
}

void Handle_ADC_Cals()
{
	Handle_Min_Max_Check();
	Handle_Mid_Check();
	if((My_Saved_Settings_RAM.POT_STRUCT[0].CH_MID>0) && (My_Saved_Settings_RAM.POT_STRUCT[0].CH_MAX>0))
	{
		My_Saved_Settings_RAM.MidPointCalDone = true;
	}

}

int16_t GET_R_THROTTLE()
{
	int32_t returnValue = 0;

	if(My_Saved_Settings_RAM.MidPointCalDone)
	{
		returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[R_THROTTLE].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[R_THROTTLE].CH_MIN)*THROTTLE_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[R_THROTTLE].CH_MAX-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[R_THROTTLE].CH_MIN));
	}
	return returnValue;
}

int16_t GET_R_ROLL()
{
	int32_t returnValue = 0;
	uint8_t target = R_ROLL;

	if(My_Saved_Settings_RAM.MidPointCalDone)
	{
		if(My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE > My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MAX-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID));
		}
		else
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MIN));
		}

	}

	if((abs(Roll_Offset+returnValue))>RIGHT_RANGE) // If range exceeded
	{
		if(Roll_Offset+returnValue>0) // Apply Limit
		{
			returnValue = RIGHT_RANGE;
		}
		else
		{
			returnValue = -RIGHT_RANGE;
		}
	}
	else // Value is valid
	{
		returnValue +=Roll_Offset;
	}

	returnValue =returnValue * (-1); // Inverted because of hardware
	return returnValue;
}

int16_t GET_R_PITCH()
{
	int32_t returnValue = 0;
	uint8_t target = R_PITCH;

	if(My_Saved_Settings_RAM.MidPointCalDone)
	{
		if(My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE > My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MAX-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID));
		}
		else
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MIN));
		}

	}


	if((abs(Pitch_Offset+returnValue))>RIGHT_RANGE) // If range exceeded
	{
		if(Pitch_Offset+returnValue>0) // Apply Limit
		{
			returnValue = RIGHT_RANGE;
		}
		else
		{
			returnValue = -RIGHT_RANGE;
		}
	}
	else // Value is valid
	{
		returnValue +=Pitch_Offset;
	}

	returnValue =returnValue * (-1); // Inverted because of hardware
	return returnValue;
}

int16_t GET_R_YAW()
{
	int32_t returnValue = 0;
	uint8_t target = R_YAW;

	if(My_Saved_Settings_RAM.MidPointCalDone)
	{
		if(My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE > My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MAX-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID));
		}
		else
		{
			returnValue = (int16_t)((((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_VALUE - (int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID)*RIGHT_RANGE)/((int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MID-(int32_t)My_Saved_Settings_RAM.POT_STRUCT[target].CH_MIN));
		}

	}
	return returnValue;
}




#define BUTTON2 (0x1<<8) // Used for E shutoff
#define BUTTON3 (0x1<<7)
#define BUTTON4 (0x1<<10)
#define BUTTON5 (0x1<<6)
#define BUTTON6 (0x1<<9)

static bool B2_UP = FALSE;
static bool B3_UP = FALSE;
static bool B4_UP = FALSE;
static bool B5_UP = FALSE;
static bool B6_UP = FALSE;

#define BUTTON_3_PRESSED ((GPIOC_PDIR & (BUTTON3)) == 0)
#define BUTTON_4_PRESSED ((GPIOC_PDIR & (BUTTON4)) == 0)
#define BUTTON_5_PRESSED ((GPIOC_PDIR & (BUTTON5)) == 0)
#define BUTTON_6_PRESSED ((GPIOC_PDIR & (BUTTON6)) == 0)


void Handle_Button_Presses()
{
	if(BUTTON_3_PRESSED)
	{
		B3_UP = TRUE;
	}
	if(BUTTON_4_PRESSED)
	{
		B4_UP = TRUE;
	}
	if(BUTTON_5_PRESSED)
	{
		B5_UP = TRUE;
	}
	if(BUTTON_6_PRESSED)
	{
		B6_UP = TRUE;
	}

	if(B3_UP && (!BUTTON_3_PRESSED))
	{
		Pitch_Offset++;
		B3_UP = FALSE;
	}

	if(B4_UP && (!BUTTON_4_PRESSED))
	{
		Pitch_Offset--;
		B4_UP = FALSE;
	}

	if(B5_UP && (!BUTTON_5_PRESSED))
	{
		Roll_Offset++;
		B5_UP = FALSE;
	}

	if(B6_UP && (!BUTTON_6_PRESSED))
	{
		Roll_Offset--;
		B6_UP = FALSE;
	}

}






void Handle_Arming_Check()
{

}


void HandleADC()
{
	static uint8_t ADC_Channel_Selected = 0;
	My_Saved_Settings_RAM.POT_STRUCT[ADC_Channel_Selected].CH_VALUE = ADC0_RA;
	ADC_Channel_Selected = (ADC_Channel_Selected+1) % ADCH_CHANNEL_TOTAL;
	Set_ADC_Channel((POTS)ADC_Channel_Selected);
}

