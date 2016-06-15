/*
 * Commands.h
 *
 * Created: 7/13/2015 1:22:49 PM
 *  Author: Nate
 */ 

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
		NULL_COMMAND	=0,
		GET_ACC			=1,
		GET_MAG			=2,
		GET_GYRO		=3,
		GET_ATT			=4,
		WHO_AM_I		=5,
		AT				=6,
		RESET			=7,
		SET_M_CAL		=8,
		GET_M_CAL 		=9,
		GET_K			=10,
		SET_MOTOR		=11,
		GET_DATA		=12,
		EN_FDATA		=13,
		IMU_CAL			=14,
}GUI_COMMANDS;

extern const char * CMD_Invalid_Str;
extern uint8_t Fast_Data_Enable;

void Write_CDC_String(char * Input_String);
void Handle_Command(char * Input_String);
void Get_Data();
