/*
 * RF.h
 *
 *  Created on: Dec 23, 2015
 *      Author: Z
 */

#ifndef SOURCES_APPLICATION_RF_H_
#define SOURCES_APPLICATION_RF_H_

#include <stdint.h>
#include <stdbool.h>
#include "Flight.h"

extern bool RF_Keep_Alive;

void handleRFKeepAlive();
void handleRadioCore();
void TX_IMU_Data();

#define SYNC_BYTE1 ('O')
#define SYNC_BYTE2 ('K')

typedef enum
{
	SLEEP=0,
	IDLE=1,
	XOFF=2,
	VCOON_MC=3,
	REGON_MC=4,
	MANCAL=5,
	VCOON=6,
	REGON=7,
	STARTCAL=8,
	BWBOOST=9,
	FS_LOCK=10,
	IFADCON=11,
	ENDCAL=12,
	RX=13,
	RX_END=14,
	RX_RST=15,
	TXRX_SWITCH=16,
	RXFIFIO_OVERFLOW=17,
	FSTXON=18,
	TX=19,
	TX_END=20,
	RXTX_SWITCH=21,
	TXFIFIO_UNDERFLOW=22
}CC2500_STATES;

typedef enum
{
	NO_PACKET=0, // Packet cleared
	P_SYNC1=1, // Recieved SYNC 1
	P_SYNC2=2, // Recieved SYNC 2
	P_INDEX=3, // Recieved FLOAT
}RF_PACKET_STATES;

extern bool packet_recieved;

typedef enum
{
	REQUEST_FLIGHT_STATE_CHANGE = 0,
	SEND_MANUAL_MOTOR_DATA =1,
	SEND_YAW_ROLL_PITCH_THROTTLE_DATA=2,
	NULL_CMD=3,
	SEND_PID_GAINS=4,
}OUTGOING_COMMANDS;

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

#define IMU_VALUES 		12
#define META_COMMANDS	10
#define RF_WORDS		(IMU_VALUES+1)

typedef struct
{
	float * IMU_DATAS[IMU_VALUES];
}RF_TRANSMIT_DATA_TYPE;

extern RF_TRANSMIT_DATA_TYPE RF_TRANSMIT_DATA;

void Handle_Incoming_Packets();
void InitRFData();


#endif /* SOURCES_APPLICATION_RF_H_ */
