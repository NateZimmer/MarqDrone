/*
 * RF_Control.c
 *
 *  Created on: Jan 8, 2016
 *      Author: Z
 */


#include "RF_Control.h"
#include "Joystick.h"
#include "../Drivers/LED_PWM.h"
#include "stdlib.h"
#include "Commands.h"
#include "USB1.h"
#include "../Drivers/USB_Echo.h"

/*
typedef enum
{
	FLIGHT_OFF=0,
	MOTOR_MANUAL_MODE=1,
	ARM_DRONE=2,
	SET_MOTOR_SPEED
}FLIGHT_MODES;
*/

typedef enum
{
	REQUEST_FLIGHT_STATE_CHANGE = 0,
	SEND_MANUAL_MOTOR_DATA =1,
	SEND_YAW_ROLL_PITCH_THROTTLE_DATA=2,
	NULL_CMD=3,
	SEND_PID_GAINS=4,
}OUTGOING_COMMANDS;

#define RF_PACKET_LENGTH 7
#define BYTES_BETWEEN_STATUS 10


FLIGHT_MODES Global_Flight_Mode = NO_CONNECTION;

uint16_t Manual_Motor_Speeds[NUMBER_OF_MOTORS]= {0,0,0,0};

uint8_t RF_Data_BUFF[RF_PACKET_LENGTH]={SYNC_BYTE1,SYNC_BYTE2,0,0,0,0,0};

void Set_Flight_Mode(FLIGHT_MODES FLIGHT_MODE)
{
	Global_Flight_Mode = FLIGHT_MODE;
}

void Set_Motor_Speed(uint16_t M1, uint16_t M2, uint16_t M3, uint16_t M4)
{
	Manual_Motor_Speeds[0] = M1;
	Manual_Motor_Speeds[1] = M2;
	Manual_Motor_Speeds[2] = M3;
	Manual_Motor_Speeds[3] = M4;
}

void Format_Manual_Motor_Packet(char * InputString)
{
	InputString[0] = SYNC_BYTE1;
	InputString[1] = SYNC_BYTE2;
	InputString[2] = SEND_MANUAL_MOTOR_DATA;
	InputString[3] = Manual_Motor_Speeds[0]/10;
	InputString[4] = Manual_Motor_Speeds[1]/10;
	InputString[5] = Manual_Motor_Speeds[2]/10;
	InputString[6] = Manual_Motor_Speeds[3]/10;
}

void Format_Flight_State_Packet(char * InputString)
{
	InputString[0] = SYNC_BYTE1;
	InputString[1] = SYNC_BYTE2;
	InputString[2] = REQUEST_FLIGHT_STATE_CHANGE;
	InputString[3] = Global_Flight_Mode;
	InputString[4] = Global_Flight_Mode;
	InputString[5] = Global_Flight_Mode;
	InputString[6] = Global_Flight_Mode;
}

void Format_YPRT_Packet(char * InputString)
{
	InputString[0] = SYNC_BYTE1;
	InputString[1] = SYNC_BYTE2;
	InputString[2] = SEND_YAW_ROLL_PITCH_THROTTLE_DATA;
	InputString[3] = (int8_t)GET_R_THROTTLE();
	InputString[4] = (int8_t)GET_R_ROLL();
	InputString[5] = (int8_t)GET_R_PITCH();
	InputString[6] = (int8_t)GET_R_YAW();
}


/*
 * Format_PID_Gains(char * InputString)
 */

void Format_PID_Gains(char * InputString)
{
	static uint8_t i = 0;

	int16_t Set_Value = 0;
	InputString[0] = SYNC_BYTE1;
	InputString[1] = SYNC_BYTE2;
	InputString[2] = SEND_PID_GAINS;
	InputString[3] = i;

	switch(i)
	{
		case PITCH_P:
			Set_Value = Pitch_P;
			break;

		case PITCH_I:
			Set_Value = Pitch_I;
			break;

		case PITCH_D:
			Set_Value = Pitch_D;
			break;

		case ROLL_P:
			Set_Value = Roll_P;
			break;

		case ROLL_I:
			Set_Value = Roll_I;
			break;

		case ROLL_D:
			Set_Value = Roll_D;
			break;

		case YAW_P:
			Set_Value = Yaw_P;
			break;

		case YAW_I:
			Set_Value = Yaw_I;
			break;

		case YAW_D:
			Set_Value = Yaw_D;
			break;

		default:
			break;
	}
	InputString[4] = Set_Value>>8;
	InputString[5] = Set_Value & 0xFF;
	i = (i%9) +1;
}




/*
 * void HandleRF_Outgoing_Link()
 * Should be called repetivily at the rate at which desired outgoing transmission frequency
 */

void HandleRF_Outgoing_Link()
{
	static uint8_t i = 0;

	if((i==9) && TRANSMIT_PID_GAINS)
	{
		Format_PID_Gains(RF_Data_BUFF);
		cc2500_tx(RF_Data_BUFF, RF_PACKET_LENGTH);
	}
	else if((i==0) || (Global_Flight_Mode==NO_CONNECTION) || (Global_Flight_Mode==RF_LINK_CONNECTED)|| (Global_Flight_Mode == ARM_DRONE))
	{
		Format_Flight_State_Packet(RF_Data_BUFF);
		cc2500_tx(RF_Data_BUFF, RF_PACKET_LENGTH);
	}
	else
	{
		switch(Global_Flight_Mode)
		{
			case MOTOR_MANUAL_MODE:
				Format_Manual_Motor_Packet(RF_Data_BUFF);
				cc2500_tx(RF_Data_BUFF, RF_PACKET_LENGTH);
				break;
			case DRONE_ARMED:
					Format_YPRT_Packet(RF_Data_BUFF);
					cc2500_tx(RF_Data_BUFF, RF_PACKET_LENGTH);
				break;
			default:
				break;
		}
	}
	i = (i+1) % BYTES_BETWEEN_STATUS;

}

#define ARMING_TOLLERANCE 	5
#define ARM_THROTTLE		0
#define ARM_ROLL			(RIGHT_RANGE)
#define ARM_PITCH			(-RIGHT_RANGE)

bool Check_For_Arming_Sequence()
{
	bool returnValue = false;
	int16_t CheckValue = 0;
	int16_t Compare_Value = 0;
	do
	{
		CheckValue = GET_R_THROTTLE();
		Compare_Value = abs(CheckValue - ARM_THROTTLE);
		if(Compare_Value > ARMING_TOLLERANCE)
			break;






		CheckValue = GET_R_PITCH(); // Slightly complicated checking ARMING because of throttling potential. Aka can't exceed max of x value due to offset
		Compare_Value = ARM_PITCH - Pitch_Offset;
		Compare_Value = ABS_Limiter16(Compare_Value,ARM_PITCH);

		if(abs(CheckValue - Compare_Value)>ARMING_TOLLERANCE)
		{
			break;
		}


		CheckValue = GET_R_ROLL(); // Now we check roll for ARM_ROLL

		Compare_Value = ARM_ROLL - Roll_Offset;
		Compare_Value = ABS_Limiter16(Compare_Value,ARM_ROLL);

		if(abs(CheckValue - Compare_Value)>ARMING_TOLLERANCE)
		{
			break;
		}


		returnValue = true; // If this point is reached, arming sequence has been performed



	}while(0);

	return returnValue;
}


void Handle_RF_Status()
{
	FLIGHT_MODES Current_Flight_State = Global_Flight_Mode;
	bool Arming_Aquired = false;




	if(RF_Keep_Alive ==false) // First and foremost, ensure we have connection, note this may be bad if our transmitter has more range than our reciever
	{
		Set_Flight_Mode(NO_CONNECTION);
		debug_console("MSG,RF Keep alive failed\r\n");
	}
	else if(POT_Min_Max_Cal || POT_Mid_Cal) // Do nothing while calibrating
	{

	}
	else
	{
		switch(Current_Flight_State)
		{
			case NO_CONNECTION:
				if(RF_Keep_Alive == true) // We have recieved RF Packets recently
				{
					Set_Flight_Mode(RF_LINK_CONNECTED);
				}
				break;
			case RF_LINK_CONNECTED:
				Arming_Aquired = Check_For_Arming_Sequence();
				if(Arming_Aquired)
				{
					Set_Flight_Mode(ARM_DRONE); // Tell drone to go into flight mode
				}
				break;
			case MOTOR_MANUAL_MODE:
				break; // Do nothing for Motor Manual mode, keep state
			case ARM_DRONE:
				if(External_Flight_State == FLIGHT_ARMED)
				{
					Set_Flight_Mode(DRONE_ARMED); // Tell drone to go into flight mode
				}
				break;
			case DRONE_ARMED:
				if(External_Flight_State != FLIGHT_ARMED )
				{
					Set_Flight_Mode(RF_LINK_CONNECTED); // Tell drone to go into flight mode
					debug_console("MSG,Drone Flight mode Error\r\n");
				}
				break;

			default:
				break; // do nothing
		}
	}
}

void Handle_LED_States()
{
	FLIGHT_MODES Current_Flight_State = Global_Flight_Mode;

	switch(Current_Flight_State)
	{
		case NO_CONNECTION:
			RLED_STATES = LED_FADE;
			GLED_STATES= LED_OFF;
			break;

		case RF_LINK_CONNECTED:
			GLED_STATES = LED_FADE;
			RLED_STATES = LED_OFF;
			break;

		case DRONE_ARMED:
			GLED_STATES = LED_FADE;
			RLED_STATES = LED_FADE;
			break;

		default:
			RLED_STATES = LED_FADE;
			GLED_STATES= LED_OFF;
			break;
	}
}

uint16_t Packet_Rate = 0;

#define TASK_TIME 0.28 //uint: seconds , this should be set to the time of the task it is in

void Handle_Packet_Rate()
{
	Packet_Rate = ((Packet_Counter*100)*0.78)/100;
	Packet_Counter = 0;
}

uint16_t Get_Packet_Rate()
{
	return Packet_Rate;
}


