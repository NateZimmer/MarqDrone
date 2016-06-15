/*
 * IMU_Data.h
 *
 *  Created on: Dec 26, 2015
 *      Author: Nathan
 */

#ifndef SOURCES_APP_IMU_DATA_H_
#define SOURCES_APP_IMU_DATA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

extern float * IMU_Data[12];
extern bool packet_recieved;

extern float ax,ay,az,gx,gy,gz,mx,my,mz,yaw,roll,pitch;

#define SYNC_BYTE1 ('O')
#define SYNC_BYTE2 ('K')

void Init_IMU_Data();
void ParseInputData(uint8_t * Packet);
uint8_t TestParseInput();
bool TestPacketEngine();
bool Packet_State(uint8_t Recieved_Byte);

extern uint16_t Packet_Counter;
extern uint8_t External_Flight_State;

enum
{
	FLIGHT_OFF=0,
	FLIGHT_REMOTE_CONNECTED=1,
	FLIGHT_ARMED=2,
	dummy=0xFFFFFFF,
};

extern int16_t Pitch_PR;
extern int16_t Pitch_IR;
extern int16_t Pitch_DR;
extern int16_t Roll_PR;
extern int16_t Roll_IR;
extern int16_t Roll_DR;
extern int16_t Yaw_PR;
extern int16_t Yaw_IR;
extern int16_t Yaw_DR;

extern uint16_t MotorSpeeds[4];


#endif /* SOURCES_APP_IMU_DATA_H_ */
