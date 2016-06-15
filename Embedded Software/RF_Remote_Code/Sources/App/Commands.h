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
		GET_MM_CAL		=12,
		GET_MID_CAL		=13,
		GET_R			=14,
		SAVE_S			=15,
		FLIGHT_MODE		=16,
		MOTOR_SPEEDS	=17,
		GET_PACKET_RATE	=18,
		GET_R_MODE		=19,
		GET_D_MODE		=20,
		GET_CPU			=21,
		EN_PID_GAIN		=22,
		SET_PID_GAIN	=23,
		GET_PID_GAIN	=24,
		GET_MTR_SPEED	=25,
}GUI_COMMANDS;

enum Meta_Commands
{
	FLIGHT_STATE_COMMAND=0,
	PITCH_P=1,
	PITCH_I=2,
	PITCH_D=3,
	ROLL_P=4,
	ROLL_I=5,
	ROLL_D=6,
	YAW_P=7,
	YAW_I=8,
	YAW_D=9,
	BATTERY_VOLTAGE=10
};

extern const char * CMD_Invalid_Str;
extern uint8_t TRANSMIT_PID_GAINS;

int16_t Pitch_P;
int16_t Pitch_I;
int16_t Pitch_D;
int16_t Roll_P;
int16_t Roll_I;
int16_t Roll_D;
int16_t Yaw_P;
int16_t Yaw_I;
int16_t Yaw_D;


void Write_CDC_String(char * Input_String);
void Handle_Command(char * Input_String);
 
