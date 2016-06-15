/*
 * IMU_Data.c
 *
 *  Created on: Dec 26, 2015
 *      Author: Nathan
 */

#include "IMU_Data.h"
#include "Math.h"
#include "RNG1.h"
#include "../External/cc2500.h"

float ax,ay,az,gx,gy,gz,mx,my,mz,yaw,roll,pitch;

int16_t Pitch_PR = 0;
int16_t Pitch_IR = 0;
int16_t Pitch_DR = 0;
int16_t Roll_PR = 0;
int16_t Roll_IR = 0;
int16_t Roll_DR = 0;
int16_t Yaw_PR = 0;
int16_t Yaw_IR = 0;
int16_t Yaw_DR = 0;

uint16_t MotorSpeeds[4]={0,0,0,0};

#define IMU_VALUE_AMOUNT 12

float * IMU_Data[IMU_VALUE_AMOUNT] = {
		&ax, //0
		&ay, //1
		&az, //2
		&gx, //3
		&gy, //4
		&gz, //5
		&mx, //6
		&my, //7
		&mz, //8
		&yaw, //9
		&roll, //10
		&pitch //11
};

bool packet_recieved = false;

void Init_IMU_Data()
{
	for(int i =0;i++;i<sizeof(IMU_Data))
	{
		*IMU_Data[i]=0;
	}
}

void ParseInputData(uint8_t * Packet)
{
	uint32_t Index = Packet[0];
	uint8_t * ptr;
	if(Index<(sizeof(IMU_Data)-1))
	{
		ptr = (uint8_t *)(IMU_Data[Index]);
		ptr[0]= Packet[1];
		ptr[1]= Packet[2];
		ptr[2]= Packet[3];
		ptr[3]= Packet[4];
	}
}

uint8_t TestParseInput()
{
	uint8_t * ptr;
	uint8_t returnValue = 0;
	float difference=0;
	float testValue=3.1241;
	ptr = (uint8_t *)&testValue;
	uint8_t testPacket[5]= {3,ptr[0],ptr[1],ptr[2],ptr[3]};
	ParseInputData(testPacket);

	difference = fabsf(testValue-gx);
	if(difference<0.01)
	{
		returnValue = 1;
	}
	return returnValue;
}



typedef enum
{
	NO_PACKET=0, // Packet cleared
	P_SYNC1=1, // Recieved SYNC 1
	P_SYNC2=2, // Recieved SYNC 2
	P_INDEX=3, // Recieved FLOAT
}RF_PACKET_STATES;

RF_PACKET_STATES RF_PACKET_STATE =NO_PACKET ;

uint16_t Packet_Counter = 0;
uint8_t Packet_Info[4]={0,0,0,0};


uint8_t External_Flight_State = 0;


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
	BATTERY_VOLTAGE=10,
	MOTOR_SPEED_01=11,
	MOTOR_SPEED_23=12,
};


uint8_t Parse_RF_Packet(uint16_t Command, uint8_t * Packet_Data)
{
	uint8_t * ptr;
	float IMU_Value = 0.0;
	int16_t yarg = 0;
	if(Command<IMU_VALUE_AMOUNT)
	{
		ptr = (uint8_t *)(&IMU_Value);
		ptr[0] = Packet_Data[0];
		ptr[1] = Packet_Data[1];
		ptr[2] = Packet_Data[2];
		ptr[3] = Packet_Data[3];

		if(fabsf(IMU_Value<5000))
		{
			*IMU_Data[Command] = IMU_Value;
			Packet_Counter++;
		}

	}
	else if(Command == 12)
	{
		External_Flight_State = Packet_Data[0];
		Packet_Counter++;
	}
	else
	{
		yarg = ((Packet_Data[0]<<8) + Packet_Data[1]);
		Packet_Counter++;
		switch(Command - 12)
		{
			case PITCH_P:
				Pitch_PR = yarg;
				break;

			case PITCH_I:
				Pitch_IR = yarg;
				break;

			case PITCH_D:
				Pitch_DR = yarg;
				break;

			case ROLL_P:
				Roll_PR = yarg;
				break;

			case ROLL_I:
				Roll_IR = yarg;
				break;

			case ROLL_D:
				Roll_DR = yarg;
				break;

			case YAW_P:
				Yaw_PR = yarg;
				break;

			case YAW_I:
				Yaw_IR = yarg;
				break;

			case YAW_D:
				Yaw_DR = yarg;
				break;

			case MOTOR_SPEED_01:
				MotorSpeeds[0] = ((Packet_Data[0]<<8) + Packet_Data[1]);
				MotorSpeeds[1] = ((Packet_Data[2]<<8) + Packet_Data[3]);
				break;

			case MOTOR_SPEED_23:
				MotorSpeeds[2] = ((Packet_Data[0]<<8) + Packet_Data[1]);
				MotorSpeeds[3] = ((Packet_Data[2]<<8) + Packet_Data[3]);
				break;

			default:
				break;
		}
	}
}


bool Packet_State(uint8_t Recieved_Byte)
{
	static uint8_t Float_Index = 0;
	static uint8_t Index = 0;
	static float IMU_Value = 0.0;
	uint8_t * ptr;
	switch(RF_PACKET_STATE)
	{
		case NO_PACKET:
			if(Recieved_Byte==SYNC_BYTE1)
			{
				RF_PACKET_STATE = P_SYNC1;
			}
		break;

		case P_SYNC1:
			if(Recieved_Byte==SYNC_BYTE2)
			{
				RF_PACKET_STATE = P_SYNC2;
			}
			else
			{
				RF_PACKET_STATE = NO_PACKET;
			}
		break;

		case P_SYNC2:
			if(Recieved_Byte<100)
			{
				Index = Recieved_Byte;
				RF_PACKET_STATE = P_INDEX;
				Float_Index = 0;
			}
			else
			{
				RF_PACKET_STATE = NO_PACKET;
			}
		break;

		case P_INDEX:

			//ptr = (uint8_t *)(&IMU_Value);
			ptr = Packet_Info;
			ptr[Float_Index] = Recieved_Byte;
			Float_Index++;
			if(Float_Index>3)
			{
				Parse_RF_Packet(Index, Packet_Info);
				RF_PACKET_STATE = NO_PACKET;
				RF_Keep_Alive = true;
				Float_Index = 0;
			}

		break;
	}
}

bool TestPacketEngine()
{
	float testValue=3.1241;
	float difference =0.0;
	uint8_t returnValue = 0;
	uint8_t buffer_byte = 0;
	uint8_t * ptr= (uint8_t *)&testValue;
	uint8_t TestPacket[12] = {0x00,0x00,0x32,0x55,'O','K',0x6,ptr[0],ptr[1],ptr[2],ptr[3],0x55};
	for(int i = 0; i<12;i++)
	{
		RNG1_Put(TestPacket[i]);
	}
	while(RNG1_NofElements())
	{
		RNG1_Get(&buffer_byte);
		Packet_State(buffer_byte);
	}
	difference = fabsf(testValue-mx);
	if(difference<0.01)
	{
		returnValue = 1;
	}
	return returnValue;
}






