/*
 * Flight.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Z
 */

#ifndef SOURCES_APPLICATION_FLIGHT_H_
#define SOURCES_APPLICATION_FLIGHT_H_

#include "../Drivers/PWM.h"
#include <stdint.h>


#define numOfMotors	4

//Kinetics

extern int8_t remoteThrottle;
extern float remotePitch;
extern float remoteRoll;
extern float remoteYaw;

// Motor Speeds

typedef enum
{
	FLIGHT_OFF=0,
	FLIGHT_REMOTE_CONNECTED=1,
	FLIGHT_ARMED=2,
	MOTOR_MANUAL_MODE=5,
	dummy=0xFFFFFFF,
}FLIGHT_STATES;

typedef struct
{
	float KP;
	float KI;
	float KD;
	float Previous_Value;
	float Previous_Error;
}PID_STRUCT;

extern PID_STRUCT Roll_PID;
extern PID_STRUCT Pitch_PID;
extern PID_STRUCT Yaw_PID;

extern float motor_speeds[4];
extern uint32_t manual_motor_speeds[4];


extern FLIGHT_STATES FLIGHT_STATE;

void updateQuadControl();

#endif /* SOURCES_APPLICATION_FLIGHT_H_ */
