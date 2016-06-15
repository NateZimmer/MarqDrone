/*
 * MPU9250.h
 *
 *  Created on: Nov 15, 2015
 *      Author: Z
 */

#ifndef SOURCES_DRIVERS_EXTERNAL_MPU9250_H_
#define SOURCES_DRIVERS_EXTERNAL_MPU9250_H_

#include "../FC.h"
#include "MPU_REG.h"
#include <stdbool.h>

#define MPU9250_ADDRESS 0x68 // Device address when ADO = 0

uint8_t Read_MPU92500_Reg(uint8_t Reg);
void readBytes(uint16_t Test, uint8_t Reg, uint8_t Length, uint8_t * buffer);
void Test_MPU();
uint8_t Init_MPU();
void IMU_Filter();
void tryGetIMUData();
float Get_Angle(float Input_Angle);


extern float ax, ay, az, gx, gy, gz, mx, my, mz, roll, yaw, pitch;
extern float Initial_Yaw;
extern float Aux_Yaw;

bool MPU_Test_ID();


extern float * IMU_Data[12];
//float * IMU_Data[12] = {
//		&ax, //0
//		&ay, //1
//		&az, //2
//		&gx, //3
//		&gy, //4
//		&gz, //5
//		&mx, //6
//		&my, //7
//		&mz, //8
//		&yaw, //9
//		&roll, //10
//		&pitch //11
//};

enum IMU_DATA_ENUM
{
	axE= 0,
	ayE=1,
	azE=2,
	gxE=3,
	gyE=4,
	gzE=5,
	mxE=6,
	myE=7,
	mzE=8,
	yawE=9,
	rollE=10,
	pitchE=11,
};


extern uint32_t debug_enable;

typedef enum
{
	M_RAW_VALUES=0,
	M_CALIBRATING=1,
	M_COMPENSATED=2
}M_CALIBRATION_STATES;

extern M_CALIBRATION_STATES M_Calibration_State;


#endif /* SOURCES_DRIVERS_EXTERNAL_MPU9250_H_ */
