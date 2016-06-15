/*
 * RF_Control.h
 *
 *  Created on: Jan 8, 2016
 *      Author: Z
 */

#ifndef SOURCES_APP_RF_CONTROL_H_
#define SOURCES_APP_RF_CONTROL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "IMU_Data.h"
#include "../External/cc2500.h"
#include "../External/cc.h"

typedef enum
{
	NO_CONNECTION=0,
	MOTOR_MANUAL_MODE=1,
	ARM_DRONE=2,
	DRONE_ARMED=3,
	RF_LINK_CONNECTED=4,
}FLIGHT_MODES;

extern FLIGHT_MODES Global_Flight_Mode;

void Set_Flight_Mode(FLIGHT_MODES FLIGHT_MODE);
void Set_Motor_Speed(uint16_t M1, uint16_t M2, uint16_t M3, uint16_t M4);
void Set_Target_Kinetics(int16_t Throttle,int16_t Yaw,int16_t Roll,int16_t Pitch);
void HandleRF_Outgoing_Link();
void Handle_RF_Status();
void Handle_LED_States();
void Handle_Packet_Rate();

uint16_t Get_Packet_Rate();

#define NUMBER_OF_MOTORS 4 // QUAD

#endif /* SOURCES_APP_RF_CONTROL_H_ */
