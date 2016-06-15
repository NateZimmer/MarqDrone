/*
 * Flight.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Z
 */

#include "Flight.h"
#include "../Drivers/External/MPU9250.h"
#include "math.h"

int8_t remoteThrottle = 0;
float remotePitch = 0;
float remoteRoll = 0;
float remoteYaw = 0;

float cntrlRoll=0;
float cntrlPitch=0;
float cntrlYaw=0;
float cntrlThrottle=0;

float targetRoll=0;
float targetYaw=0;
float targetPitch=0;

///////////////////////////////////////
//
//		QUAD FRAME REFERENCE
//
//       x 0       x 1
//        \       /
//         \  _  /
//          xxxxx
//          xxxxx
//         /     \
//        /       \
//       x 3       x 2
//
///////////////////////////////////////

const int32_t MOTOR_SPEED_MIN = 0; // We do not want to shutoff the motors due to startup time
const int32_t MOTOR_SPEED_MAX = 999; // Motors inherently have a max speed we cannot exceed.


FLIGHT_STATES FLIGHT_STATE = FLIGHT_OFF;

float motor_speeds[numOfMotors] = {0,0,0,0};

uint32_t manual_motor_speeds[numOfMotors] = {0,0,0,0};

void applyThrottle()
{
	motor_speeds[0] =10*(int16_t)remoteThrottle;
	motor_speeds[1] =10*(int16_t)remoteThrottle;
	motor_speeds[2] =10*(int16_t)remoteThrottle;
	motor_speeds[3] =10*(int16_t)remoteThrottle;
}

void applyPitch()
{
	motor_speeds[0] +=cntrlPitch;
	motor_speeds[1] +=cntrlPitch;
	motor_speeds[2] -=cntrlPitch;
	motor_speeds[3] -=cntrlPitch;
}

void applyRoll()
{
	motor_speeds[1] -=cntrlRoll;
	motor_speeds[2] -=cntrlRoll;
	motor_speeds[0] +=cntrlRoll;
	motor_speeds[3] +=cntrlRoll;
}

void applyYaw()
{
	motor_speeds[1] -=cntrlYaw;
	motor_speeds[3] -=cntrlYaw;
	motor_speeds[0] +=cntrlYaw;
	motor_speeds[2] +=cntrlYaw;
}


void SetMotorSpeeds()
{
	Set_PPM_Reg(CH0,(int16_t)motor_speeds[0]);
	Set_PPM_Reg(CH1,(int16_t)motor_speeds[1]);
	Set_PPM_Reg(CH2,(int16_t)motor_speeds[2]);
	Set_PPM_Reg(CH3,(int16_t)motor_speeds[3]);
}

void motorsOff()
{
	uint16_t i = 0;
	for(i=0;i<numOfMotors;i++)
	{
		motor_speeds[i]=0;
		remotePitch = 0;
		remoteYaw = 0;
		remoteThrottle = 0;
		remoteRoll = 0;
	}
	SetMotorSpeeds();
}

#define TIME_CONSTANT 0.005
#define I_THR 200.01

const uint8_t ACRO_MODE = 0;



float Get_PID_Result(float Input, float Target, PID_STRUCT * PID)
{
	float Error =0;
	float returnValue = 0;

	if(ACRO_MODE)
	{
		Error = Target;
	}
	else
	{
		Error = Get_Angle(Target-Input);
	}


	// Calculate PID Errors
	float P = (PID->KP) * Error; // Proportional Error
	//float I = (PID->KI) * (PID->Previous_Error); // Integral Error
	PID->Previous_Error += (PID->KI) * Error / 10;
	float D = (PID->KD) * (Error - PID->Previous_Value); // Derivative Error

	// Take into account speed at which function is called
	D*=10;

	PID->Previous_Error = (motor_speeds[0]<300.0) ? 0 : PID->Previous_Error; // Do not accumulate error if motors not spinning, helps for takeoff hopefully?
	PID->Previous_Error = ((PID->KI)==0.0) ? 0 : PID->Previous_Error;

	// Store Previous Error
	if(fabsf(PID->Previous_Error)>I_THR) // If our I is greater than our threshold.
	{
		PID->Previous_Error = (PID->Previous_Error>0) ? I_THR : -I_THR;
	}

	PID->Previous_Value = Error;
	returnValue = (P + PID->Previous_Error + D);
	return returnValue;

}

PID_STRUCT Roll_PID = {8.0,1.0,20,0,0};
PID_STRUCT Pitch_PID = {8.0,1.0,20,0,0};
PID_STRUCT Yaw_PID  = {8,1,20,0,0};

void Get_Control_Values()
{
	cntrlRoll = Get_PID_Result(roll,(float)remoteRoll,&Roll_PID);
	cntrlPitch = Get_PID_Result(pitch,(float)remotePitch,&Pitch_PID);
	cntrlYaw = Get_PID_Result(yaw,(float)remoteYaw,&Yaw_PID);
}

/*
 * Ensures our target motor speeds are within the physical limits of the system.
 * We also want to ensure no motors completely shut-off due to varying startup time
 */
void applyLimits()
{
	uint16_t i = 0;
	for(i=0;i<numOfMotors;i++)
	{
		if(motor_speeds[i]>((float)MOTOR_SPEED_MAX))
		{
			motor_speeds[i] = (float)MOTOR_SPEED_MAX;
		}

		if(motor_speeds[i]<((float)MOTOR_SPEED_MIN))
		{
			motor_speeds[i] = (float)MOTOR_SPEED_MIN;
		}
	}
}


/*
 * Applies all the calculated kinetics per remote inputs and control outputs.
 * Upon final value calculations, does a sanity check to ensure values are within limits
 */

void updateMotorSpeeds()
{
	Get_Control_Values();
	applyThrottle();
	applyPitch();
	applyRoll();
	applyYaw();
	applyLimits();
	SetMotorSpeeds();
}

/*
 * uint8_t PID_Testing_Limit_Shutoff()
 * A function that shuts off motors if beyond a certain roll/pitch/yaw value
 *
 */

uint8_t PID_Testing_Limit_Shutoff()
{
	uint8_t Return_Value =0;
}


/*
 * Updates the motors with the manual motor speed values.
 * These values are set via the GUI / USB AT Commands
 */

void updateManualMotorSpeeds()
{
	Set_PPM_Reg(CH0,(int16_t)manual_motor_speeds[0]);
	Set_PPM_Reg(CH1,(int16_t)manual_motor_speeds[1]);
	Set_PPM_Reg(CH2,(int16_t)manual_motor_speeds[2]);
	Set_PPM_Reg(CH3,(int16_t)manual_motor_speeds[3]);
}


/*
 * Flight state system. Motors should always be off unless in the correct state.
 */

void updateQuadControl()
{
	switch(FLIGHT_STATE)
	{
		case FLIGHT_OFF:
			motorsOff();
			break;

		case FLIGHT_REMOTE_CONNECTED:
			motorsOff();
			break;

		case FLIGHT_ARMED:
			updateMotorSpeeds();
			break;

		case MOTOR_MANUAL_MODE:
			updateManualMotorSpeeds();
			break;

		default:
			motorsOff();
			break;
	}
}


