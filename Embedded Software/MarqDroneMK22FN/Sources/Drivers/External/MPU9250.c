/*
 * MPU9250.c
 *
 *  Created on: Nov 15, 2015
 *      Author: Z
 */

//Referenced from https://github.com/kriswiner/MPU-9250/blob/master/MPU9250BasicAHRS_t3.ino

#include "MPU9250.h"
#include <math.h>
#include <stdio.h>
#include "../SPI.h"
#include "../../Generated_Code/WAIT1.h"
#include "../../Generated_Code/CDC1.h"
#include "../FC.h"
#include "../TPM0.h"
#include "../../Application/Saved_Settings.h"
#include "WAIT1.h"

uint32_t debug_enable =1;

#define SKIP_ACC_BIAS

/*
 * Read 1 Register on the MPU92500
 */

uint8_t Read_MPU92500_Reg(uint8_t Reg)
{
	uint8_t returnValue = 0;
	Set_Pin(&MPU9250_CS,0);
	spi_send_recv(0x80|Reg); // Send Reg Address
	WAIT1_WaitCycles(100);
	returnValue = spi_send_recv(0); // Send Address
	Set_Pin(&MPU9250_CS,1);
	return returnValue;
}

/*
 * Read multiple registers on the MPU9250
 */

void Read_MPU92500_Regs(uint8_t Reg, uint8_t Length, uint8_t * Buffer)
{
	Set_Pin(&MPU9250_CS,0);
	spi_send_recv(0x80|Reg); // Send Address
	WAIT1_WaitCycles(100);
	for(int i=0;i<Length;i++)
	{
		Buffer[i] = spi_send_recv(0); // Send Address
		WAIT1_WaitCycles(100);
	}
	Set_Pin(&MPU9250_CS,1);
}

/*
 * Write to reg on MPU9250
 */

void Write_MPU9250_Write(uint8_t reg, uint8_t data)
{
	Set_Pin(&MPU9250_CS,0);
	spi_send_recv(0x7f & reg); // Send Address
	WAIT1_WaitCycles(100);
	spi_send_recv(data); // Send Address
	Set_Pin(&MPU9250_CS,1);
}

/*
 * Write to mag on MPU9250. Over spi this is messy because the MPU translates this to I2C and then back to SPI.
 */

void Write_MPU9250_Mag_Reg(uint8_t reg, uint8_t data)
{
	uint8_t writeComplete = 0;
	uint8_t MPU_Status_Read=0;
	Write_MPU9250_Write(I2C_SLV4_REG, reg ); // Send I2C reg
	Write_MPU9250_Write(I2C_SLV4_ADDR, AK8963_ADDRESS ); // Send I2C Address
	Write_MPU9250_Write(I2C_SLV4_DO, data ); // Send I2C data
	Write_MPU9250_Write(I2C_SLV4_CTRL, I2C_SLV4_EN); // Initiate

	while(!writeComplete)
	{
		WAIT1_WaitCycles(100);
		MPU_Status_Read = Read_MPU92500_Reg(I2C_MST_STATUS);
		if((MPU_Status_Read & I2C_SLV4_DONE)==I2C_SLV4_DONE)
		{
			writeComplete = 1;
		}
	}
}


/*
 * Read from mag on MPU9250.
 */

uint8_t Read_MPU9250_Mag_Reg(uint8_t reg)
{
	uint8_t writeComplete = 0;
	uint8_t MPU_Status_Read=0;
	uint16_t Fail_Counter = 0;
	Write_MPU9250_Write(I2C_SLV4_REG, reg ); // Send I2C reg
	Write_MPU9250_Write(I2C_SLV4_ADDR, AK8963_ADDRESS | 0x80 ); // Send I2C Address w/ read bit
	Write_MPU9250_Write(I2C_SLV4_CTRL, I2C_SLV4_EN); // Initiate

	while(!writeComplete)
	{
		WAIT1_WaitCycles(10000);
		MPU_Status_Read = Read_MPU92500_Reg(I2C_MST_STATUS);
		Fail_Counter++;
		if((MPU_Status_Read & I2C_SLV4_DONE)==I2C_SLV4_DONE)
		{
			writeComplete = 1;
		}
		if(Fail_Counter>1000)
		{
			break;
		}
	}
	MPU_Status_Read =Read_MPU92500_Reg(I2C_SLV4_DI);
	return MPU_Status_Read;
}

/*
 * Ensure MPU reads correct reg
 */

bool MPU_Test_ID()
{
	uint8_t returnValue = 0;
	returnValue = Read_MPU92500_Reg(WHO_AM_I_MPU9250);
	if(returnValue==0x71)
	{
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}
}

/*
 * Compatability layer with arduino code
 */

void writeByte(uint16_t Device, uint8_t Reg, uint8_t Data)
{
	if(Device==MPU9250_ADDRESS)
	{
		Write_MPU9250_Write(Reg, Data);
	}
	if(Device==AK8963_ADDRESS)
	{
		Write_MPU9250_Mag_Reg(Reg,Data);
	}
}

void readBytes(uint16_t Device, uint8_t Reg, uint8_t Length, uint8_t * buffer)
{
	if(Device==MPU9250_ADDRESS)
	{
		Read_MPU92500_Regs(Reg,Length,buffer);
	}
	else if(Device==AK8963_ADDRESS)
	{
		for(int i=0;i<Length;i++) //Should eventually be replaced with a sequential read
		{
			buffer[i] =Read_MPU9250_Mag_Reg(Reg+i);
		}
	}

}

void delay(uint32_t delays)
{
	WAIT1_Waitms(delays);
}

uint8_t readByte(uint16_t Device, uint8_t Reg)
{
	uint8_t returnValue = 0;
	if(Device==MPU9250_ADDRESS)
	{
		returnValue = Read_MPU92500_Reg(Reg);
	}
	if(Device==AK8963_ADDRESS)
	{
		returnValue = Read_MPU9250_Mag_Reg(Reg);
	}
	return returnValue;
}

/*
 * Start of ardunio code
 */


#define PI 3.14159265358979323846f
float SelfTest[6]; // holds results of gyro and accelerometer self test

enum Ascales {
  AFS_2G = 0,
  AFS_4G = 1,
  AFS_8G = 2,
  AFS_16G =3
};

enum Gscales {
  GFS_250DPS = 0,
  GFS_500DPS = 1,
  GFS_1000DPS = 2,
  GFS_2000DPS = 3
};
#define MPU_DPS_SHIFT 3

enum Mscales {
  MFS_14BITS = 0, // 0.6 mG per LSB
  MFS_16BITS      // 0.15 mG per LSB
};

// Specify sensor full scale
//uint8_t Gscale = GFS_250DPS; // Modified NATE
//uint8_t Ascale = AFS_2G;

uint8_t Gscale = GFS_500DPS;
uint8_t Ascale = AFS_8G;

uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
uint8_t Mmode = 0x06;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read
float aRes, gRes, mRes;      // scale resolutions per LSB for the sensors

int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output
float magCalibration[3] = {0, 0, 0}, magbias[3] = {0, 0, 0};  // Factory mag calibration and mag bias
float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};      // Bias corrections for gyro and accelerometer
int16_t tempCount;      // temperature raw count output
float   temperature;    // Stores the real internal chip temperature in degrees Celsius
float   SelfTest[6];    // holds results of gyro and accelerometer self test

// global constants for 9 DoF fusion and AHRS (Attitude and Heading Reference System)
float GyroMeasError = PI * (40.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
float GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
float Initial_Yaw = 0.0;


//float beta = sqrt(3.0f / 4.0f) * GyroMeasError;   // compute beta
//float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value

#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f

uint32_t delt_t = 0; // used to control display output rate
uint32_t count = 0, sumCount = 0; // used to control display output rate
float pitch, yaw, roll;
float sum = 0.0f;        // integration interval for both filter schemes
uint32_t lastUpdate = 0, firstUpdate = 0; // used to calculate integration interval
uint32_t Now = 0;        // used to calculate integration interval

float ax, ay, az, gx, gy, gz, mx, my, mz; // variables to hold latest sensor data values
float eInt[3] = {0.0f, 0.0f, 0.0f};       // vector to hold integral error for Mahony method


void MPU9250SelfTest(float * destination) // Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
{
   uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
   uint8_t selfTest[6];
   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
   float factoryTrim[6];
   uint8_t FS = 0;

  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
  writeByte(MPU9250_ADDRESS, CONFIG, 0x02);        // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 1<<FS);  // Set full scale range for the gyro to 250 dps
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 1<<FS); // Set full scale range for the accelerometer to 2 g

  for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer

  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
  aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

    readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);       // Read the six raw data registers sequentially into data array
  gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
  aAvg[ii] /= 200;
  gAvg[ii] /= 200;
  }

// Configure the accelerometer for self-test
   writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
   writeByte(MPU9250_ADDRESS, GYRO_CONFIG,  0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
   delay(25);  // Delay a while to let the device stabilize

  for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer

  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
  aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

    readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
  gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
  gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
  }

  for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average self-test readings
  aSTAvg[ii] /= 200;
  gSTAvg[ii] /= 200;
  }

 // Configure the gyro and accelerometer for normal operation
   writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
   writeByte(MPU9250_ADDRESS, GYRO_CONFIG,  0x00);
   delay(25);  // Delay a while to let the device stabilize

   // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
   selfTest[0] = readByte(MPU9250_ADDRESS, SELF_TEST_X_ACCEL); // X-axis accel self-test results
   selfTest[1] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
   selfTest[2] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
   selfTest[3] = readByte(MPU9250_ADDRESS, SELF_TEST_X_GYRO);  // X-axis gyro self-test results
   selfTest[4] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_GYRO);  // Y-axis gyro self-test results
   selfTest[5] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_GYRO);  // Z-axis gyro self-test results

  // Retrieve factory self-test value from self-test code reads
   factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
   factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
   factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
   factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
   factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
   factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation

 // Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
 // To get percent, must multiply by 100
   for (int i = 0; i < 3; i++) {
     destination[i]   = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i];   // Report percent differences
     destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3]; // Report percent differences
   }

}

void calibrateMPU9250(float * dest1, float * dest2)
{
  uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
  uint16_t ii, packet_count, fifo_count;
  int32_t gyro_bias[3]  = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

 // reset device
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
  delay(100);

 // get stable time source; Auto select clock source to be PLL gyroscope reference if ready
 // else use the internal oscillator, bits 2:0 = 001
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
  writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
  delay(200);

// Configure device for bias calculation
  writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
  writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
  delay(150);

  //Nate Code,
  //Ensure FIFO is empty

  readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
  fifo_count = ((uint16_t)data[0] << 8) | data[1];


  //End nate code




// Configure MPU6050 gyro and accelerometer for bias calculation
  writeByte(MPU9250_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

  uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
  uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g

    // Configure FIFO to capture accelerometer and gyro data for bias calculation
  //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO
  /////////NOTE NATE MODDED HERE/////////////////////////////////////////
  writeByte(MPU9250_ADDRESS, USER_CTRL,(I2C_MST_EN | I2C_IF_DIS | FIFO_EN_BIT)); // Enable FIFO, I2C Reset, I2C Master

  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in MPU-9150)
  delay(15); // accumulate 40 samples in 40 milliseconds = 480 bytes

// At end of sample accumulation, turn off FIFO sensor read
  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
  readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
  fifo_count = ((uint16_t)data[0] << 8) | data[1];
  packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

  for (ii = 0; ii < packet_count; ii++) {
    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
    readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
    accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
    accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
    accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;
    gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
    gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
    gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;

    accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
    accel_bias[1] += (int32_t) accel_temp[1];
    accel_bias[2] += (int32_t) accel_temp[2];
    gyro_bias[0]  += (int32_t) gyro_temp[0];
    gyro_bias[1]  += (int32_t) gyro_temp[1];
    gyro_bias[2]  += (int32_t) gyro_temp[2];

}
    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;

  if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
  else {accel_bias[2] += (int32_t) accelsensitivity;}

// Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
  data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
  data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
  data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
  data[3] = (-gyro_bias[1]/4)       & 0xFF;
  data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
  data[5] = (-gyro_bias[2]/4)       & 0xFF;

// Push gyro biases to hardware registers

#ifndef SKIP_GYRO_BIAS

  writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
  writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
  writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
  writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
  writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
  writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);

  #endif


// Output scaled gyro biases for display in the main program
  dest1[0] = (float) gyro_bias[0]/(float) gyrosensitivity;
  dest1[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
  dest1[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

// Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
// factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
// non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
// compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
// the accelerometer biases calculated above must be divided by 8.

  int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
  readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
  accel_bias_reg[0] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
  readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[1] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
  readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
  accel_bias_reg[2] = (int32_t) (((int16_t)data[0] << 8) | data[1]);

  uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
  uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

  for(ii = 0; ii < 3; ii++) {
    if((accel_bias_reg[ii] & mask)) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
  }

  // Construct total accelerometer bias, including calculated average accelerometer bias from above
  accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
  accel_bias_reg[1] -= (accel_bias[1]/8);
  accel_bias_reg[2] -= (accel_bias[2]/8);

  data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  data[1] = (accel_bias_reg[0])      & 0xFF;
  data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  data[3] = (accel_bias_reg[1])      & 0xFF;
  data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
  data[5] = (accel_bias_reg[2])      & 0xFF;
  data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

// Apparently this is not working for the acceleration biases in the MPU-9250
// Are we handling the temperature correction bit properly?
// Push accelerometer biases to hardware registers

#ifndef SKIP_ACC_BIAS

  writeByte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
  writeByte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
  writeByte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
  writeByte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
  writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
  writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);
#endif


// Output scaled accelerometer biases for display in the main program
   dest2[0] = (float)accel_bias[0]/(float)accelsensitivity;
   dest2[1] = (float)accel_bias[1]/(float)accelsensitivity;
   dest2[2] = (float)accel_bias[2]/(float)accelsensitivity;


}


void initMPU9250()
{
 // wake up device
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
  delay(100); // Wait for all registers to reset

 // get stable time source
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
  delay(200);

 // Configure Gyro and Thermometer
 // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively;
 // minimum delay time for this setting is 5.9 ms, which means sensor fusion update rates cannot
 // be higher than 1 / 0.0059 = 170 Hz
 // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
 // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
  writeByte(MPU9250_ADDRESS, CONFIG, GYRO_LPF_184HZ);

 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x01);  // Use a 500 Hz rate; a rate consistent with the filter update rate
                                    // determined inset in CONFIG above

 // Set gyroscope full scale range
 // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  uint8_t c = readByte(MPU9250_ADDRESS, GYRO_CONFIG);
//  writeRegister(GYRO_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
  //writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c & ~0x02); // Clear Fchoice bits [1:0]
  //writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
  //writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c | Gscale << 3); // Set full scale range for the gyro

  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, (GFS_500DPS<<MPU_DPS_SHIFT) ); // Set full scale range for the gyro


 // writeRegister(GYRO_CONFIG, c | 0x00); // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of GYRO_CONFIG

 // Set accelerometer full-scale range configuration
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG);
//  writeRegister(ACCEL_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
  //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
  //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c | Ascale << 3); // Set full scale range for the accelerometer
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, Ascale << 3);

 // Set accelerometer sample rate configuration
 // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
 // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2);
  //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c & ~0x0F); // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, GYRO_LPF_184HZ); // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz

 // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
 // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
  // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips
  // can join the I2C bus and all can be controlled by the Arduino as master
   ///NATE MOD HERE
  //writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
   writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
   delay(100);
}

void initAK8963(float * destination)
{
  // First extract the factory calibration for each magnetometer axis
  uint8_t rawData[3];  // x/y/z gyro calibration data stored here
  uint8_t d = 0;
 // writeByte(MPU9250_ADDRESS, USER_CTRL,(I2C_MST_RST)); // Enable FIFO, I2C Reset, I2C Master
  //delay(100);
  d  = readByte(MPU9250_ADDRESS,USER_CTRL);
  d++;
  writeByte(MPU9250_ADDRESS, USER_CTRL,(I2C_MST_RST)); // Enable FIFO, I2C Reset, I2C Master
  delay(100);
  writeByte(MPU9250_ADDRESS, USER_CTRL,(I2C_MST_EN)); // Enable FIFO, I2C Reset, I2C Master

  Write_MPU9250_Write(I2C_SLV0_REG, 0xB ); // Send I2C reg
  Write_MPU9250_Write(I2C_SLV0_ADDR, AK8963_ADDRESS ); // Send I2C Address
  Write_MPU9250_Write(I2C_SLV0_DO, 0x1 ); // Send I2C data
  Write_MPU9250_Write(I2C_SLV0_CTRL, 0x81); // Initiate
  delay(100);



  //writeByte(AK8963_ADDRESS, AK8963_CNTL2, 0x01); // Power down magnetometer
  delay(100);
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
  delay(100);
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
  delay(100);
  readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
  destination[0] =  (float)(rawData[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
  destination[1] =  (float)(rawData[1] - 128)/256. + 1.;
  destination[2] =  (float)(rawData[2] - 128)/256. + 1.;
  writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
  delay(100);
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR

  writeByte(MPU9250_ADDRESS,I2C_SLV0_REG, AK8963_ST1);
  writeByte(MPU9250_ADDRESS,I2C_SLV0_ADDR, AK8963_ADDRESS | 0x80);
  writeByte(MPU9250_ADDRESS,I2C_SLV0_CTRL, I2C_SLV4_EN | 8);

  delay(10);
  writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, (0x1<<6)); // Disable I2C master
}


void readAccelData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;
}


void readGyroData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  destination[0] = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  destination[1] = ((int16_t)rawData[2] << 8) | rawData[3] ;
  destination[2] = ((int16_t)rawData[4] << 8) | rawData[5] ;
}

void readMagData(int16_t * destination)
{
  uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
  if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
  readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
  uint8_t c = rawData[6]; // End data read by reading ST2 register
    if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
    destination[0] = ((int16_t)rawData[1] << 8) | rawData[0] ;  // Turn the MSB and LSB into a signed 16-bit value
    destination[1] = ((int16_t)rawData[3] << 8) | rawData[2] ;  // Data stored as little Endian
    destination[2] = ((int16_t)rawData[5] << 8) | rawData[4] ;
   }
  }
}

int16_t readTempData()
{
  uint8_t rawData[2];  // x/y/z gyro register data stored here
  readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array
  return ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a 16-bit value
}

char textBuffer[50];

int16_t AccData[3];
int16_t MagData[3];
int16_t GyroData[3];

uint8_t in_buffer[64];

float q[4] = {1.0f, 0.0f, 0.0f, 0.0f}; // vector to hold quaternion
float deltat = 0.0f;

float beta = sqrt(3.0f / 4.0f) * PI * (60.0 / 180.0);  // compute beta
float zeta = sqrt(3.0f / 4.0f) * ( PI * (1.0f / 180.0f));  // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value


// Implementation of Sebastian Madgwick's "...efficient orientation filter for... inertial/magnetic sensor arrays"
// (see http://www.x-io.co.uk/category/open-source/ for examples and more details)
// which fuses acceleration, rotation rate, and magnetic moments to produce a quaternion-based estimate of absolute
// device orientation -- which can be converted to yaw, pitch, and roll. Useful for stabilizing quadcopters, etc.
// The performance of the orientation filter is at least as good as conventional Kalman-based filtering algorithms
// but is much less computationally intensive---it can be performed on a 3.3 V Pro Mini operating at 8 MHz!

//===================================================================================================================
//====== Set of useful function to access acceleration. gyroscope, magnetometer, and temperature data
//===================================================================================================================




void getMres() {
  switch (Mscale)
  {
 	// Possible magnetometer scales (and their register bit settings) are:
	// 14 bit resolution (0) and 16 bit resolution (1)
    case MFS_14BITS:
          mRes = 10.*4912./8190.; // Proper scale to return milliGauss
          break;
    case MFS_16BITS:
          mRes = 10.*4912./32760.0; // Proper scale to return milliGauss
          break;
  }
}

void getGres() {
  switch (Gscale)
  {
 	// Possible gyro scales (and their register bit settings) are:
	// 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
    case GFS_250DPS:
          gRes = 250.0/32768.0;
          break;
    case GFS_500DPS:
          gRes = 500.0/32768.0;
          break;
    case GFS_1000DPS:
          gRes = 1000.0/32768.0;
          break;
    case GFS_2000DPS:
          gRes = 2000.0/32768.0;
          break;
  }
}

void getAres() {
  switch (Ascale)
  {
 	// Possible accelerometer scales (and their register bit settings) are:
	// 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
    case AFS_2G:
          aRes = 2.0/32768.0;
          break;
    case AFS_4G:
          aRes = 4.0/32768.0;
          break;
    case AFS_8G:
          aRes = 8.0/32768.0;
          break;
    case AFS_16G:
          aRes = 16.0/32768.0;
          break;
  }
}

#define Mag_Scale 500.00

//M_CALIBRATION_STATES M_Calibration_State = M_RAW_VALUES;
M_CALIBRATION_STATES M_Calibration_State = M_COMPENSATED;

void magScale(float * k,float * k_max, float * k_min)
{
	float mag=0;

	*k = 500*(*k - *k_min)/(*k_max - *k_min) - 250.0;

	//mag= (fabsf(*k_max)+fabsf(*k_min)) / 2.0; // calc mag of scale, note fabsf is the float abs
	//*k = Mag_Scale / (mag) * ( (*k)- ((*k_max) - mag)); // Adjust value of k to compensate for soft/hard iron offsets

}

/*
float mag_max_x = 0;
float mag_max_y = 0;
float mag_max_z = 0;
float mag_min_x = 0;
float mag_min_y = 0;
float mag_min_z = 0;
*/

// Hardcoded from observed calc data. Todo, replace with flash loaded values
/*
float mag_max_x = 677.7;
float mag_max_y = 1055.0;
float mag_max_z = -175.064;
float mag_min_x = -329.864;
float mag_min_y = 28.081;
float mag_min_z = -1262.0;
*/
float mag_max_x = 593.381;
float mag_max_y = 1172.367;
float mag_max_z = -454.979;
float mag_min_x = -370.551;
float mag_min_y = 199.02;
float mag_min_z = -1437.53;



void magCalibrate() // update based upon max values
{
	if(M_Calibration_State ==M_CALIBRATING)
	{
		if(mag_max_x< mx)
			mag_max_x = mx;
		if(mag_max_y< my)
			mag_max_y = my;
		if(mag_max_z< mz)
			mag_max_z = mz;

		if(mag_min_x>mx)
			mag_min_x = mx;
		if(mag_min_y>my)
			mag_min_y = my;
		if(mag_min_z>mz)
			mag_min_z = mz;
	}
}


/*
 * Save mag calibration settings to flash
 */

void Save_Mag_Calbration()
{
	My_Saved_Settings_RAM.mag_max_x_F = mag_max_x;
	My_Saved_Settings_RAM.mag_max_y_F = mag_max_y;
	My_Saved_Settings_RAM.mag_max_z_F = mag_max_z;

	My_Saved_Settings_RAM.mag_min_x_F = mag_min_x;
	My_Saved_Settings_RAM.mag_min_y_F = mag_min_y;
	My_Saved_Settings_RAM.mag_min_z_F = mag_min_z;

	My_Saved_Settings_RAM.Mag_Cal_Complete= TRUE;
	Save_Settings();

}





void handleMag()
{
	static uint32_t Previous_Mag_Cal_State = M_RAW_VALUES;
	if(M_Calibration_State ==M_CALIBRATING)
	{
		magCalibrate();
	}
	if((M_Calibration_State == M_CALIBRATING)||(M_Calibration_State ==M_COMPENSATED ) )
	{
		magScale(&mx,&mag_max_x,&mag_min_x);
		magScale(&my,&mag_max_y,&mag_min_y);
		magScale(&mz,&mag_max_z,&mag_min_z);
	}


	if((Previous_Mag_Cal_State == M_CALIBRATING) && (M_Calibration_State ==M_COMPENSATED)) // Catch when save occurs
	{
		Save_Mag_Calbration();
	}

	Previous_Mag_Cal_State = M_Calibration_State;

}


typedef enum {
	IDX_ACCEL_XOUT_H=0, //0
	IDX_ACCEL_XOUT_L=1, //1
	IDX_ACCEL_YOUT_H=2, //2
	IDX_ACCEL_YOUT_L=3, //3
	IDX_ACCEL_ZOUT_H=4, //4
	IDX_ACCEL_ZOUT_L=5, //5
	IDX_TEMP_OUT_H=6,
	IDX_TEMP_OUT_L=7,
	IDX_GYRO_XOUT_H=8,
	IDX_GYRO_XOUT_L=9,
	IDX_GYRO_YOUT_H=10,
	IDX_GYRO_YOUT_L=11,
	IDX_GYRO_ZOUT_H=12,
	IDX_GYRO_ZOUT_L=13,
	IDX_MAG_ST1=14,
	IDX_MAG_XOUT_L=15,
	IDX_MAG_XOUT_H=16,
	IDX_MAG_YOUT_L=17,
	IDX_MAG_YOUT_H=18,
	IDX_MAG_ZOUT_L=19,
	IDX_MAG_ZOUT_H=20,
	IDX_MAG_ST2=21,
	BUFFER_SIZE,
}IMU_REGS;

uint8_t IMU_Buffer[25];

float Ax_F = 0;
float Ay_F = 0;
float Az_F = 0;

float Gx_F = 0;
float Gy_F = 0;
float Gz_F = 0;

float Gxx = 0;
float Gyy = 0;
float Gzz = 0;

float Gxxx = 0;
float Gyyy = 0;
float Gzzz = 0;


float mmx = 0;
float mmy = 0;
float mmz = 0;
float Aux_Yaw;


#define A_GAIN (0.01)

bool GYRO_ONLY =  0;

void tryGetIMUData()
{
	uint8_t getStatus = 0;
	getStatus = readByte(MPU9250_ADDRESS, INT_STATUS);
	if(getStatus & 0x1)
	{
		Read_MPU92500_Regs(ACCEL_XOUT_H,22,IMU_Buffer);

		accelCount[0] = ((int16_t)IMU_Buffer[0] << 8) | IMU_Buffer[1] ;  // Turn the MSB and LSB into a signed 16-bit value
		accelCount[1] = ((int16_t)IMU_Buffer[2] << 8) | IMU_Buffer[3] ;
		accelCount[2] = ((int16_t)IMU_Buffer[4] << 8) | IMU_Buffer[5] ;
		getAres();
		//ax = (float)accelCount[0]*aRes; // - accelBias[0];  // get actual g value, this depends on scale being set
		//ay = (float)accelCount[1]*aRes; // - accelBias[1];
		//az = (float)accelCount[2]*aRes; // - accelBias[2];


		Ax_F = (float)accelCount[0]*aRes; // - accelBias[0];  // get actual g value, this depends on scale being set
		Ay_F = (float)accelCount[1]*aRes; // - accelBias[1];
		Az_F = (float)accelCount[2]*aRes; // - accelBias[2];

		ax = ax + 0.1*(Ax_F - ax);
		ay = ay + 0.1*(Ay_F - ay);
		az = az + 0.1*(Az_F - az);

		gyroCount[0] = ((int16_t)IMU_Buffer[IDX_GYRO_XOUT_H] << 8) | IMU_Buffer[IDX_GYRO_XOUT_L] ;  // Turn the MSB and LSB into a signed 16-bit value
		gyroCount[1] = ((int16_t)IMU_Buffer[IDX_GYRO_YOUT_H] << 8) | IMU_Buffer[IDX_GYRO_YOUT_L] ;
		gyroCount[2] = ((int16_t)IMU_Buffer[IDX_GYRO_ZOUT_H] << 8) | IMU_Buffer[IDX_GYRO_ZOUT_L] ;
		getGres();

		gx = (float)gyroCount[0]*gRes;  // get actual gyro value, this depends on scale being set
		gy = (float)gyroCount[1]*gRes;
		gz = (float)gyroCount[2]*gRes;

		magCount[0] = ((int16_t)IMU_Buffer[IDX_MAG_XOUT_H] << 8) | IMU_Buffer[IDX_MAG_XOUT_L] ;  // Turn the MSB and LSB into a signed 16-bit value
		magCount[1] = ((int16_t)IMU_Buffer[IDX_MAG_YOUT_H] << 8) | IMU_Buffer[IDX_MAG_YOUT_L] ;  // Data stored as little Endian
		magCount[2] = ((int16_t)IMU_Buffer[IDX_MAG_ZOUT_H] << 8) | IMU_Buffer[IDX_MAG_ZOUT_L] ;
		getMres();

		yaw  += 1.0 * gz * 0.002; // Uncomment this eventually

		if(IMU_Buffer[IDX_MAG_ST1] & DRDY)
		{
			mx = (float)magCount[0]*mRes*magCalibration[0] - magbias[0];  // get actual magnetometer value, this depends on scale being set
			my = (float)magCount[1]*mRes*magCalibration[1] - magbias[1];
			mz = (float)magCount[2]*mRes*magCalibration[2] - magbias[2];

			handleMag();

			mmx = mmx + 0.25*(mx - mmx);
			mmy = mmy + 0.25*(my - mmy);
			mmz = mmz + 0.25*(mz - mmz);

			//mx = -mmx;
			//my = -mmy;
			mx = -mmx;
			my = -mmy;
			mz = mmz;

			float psi_num = (mz)*sinf(roll*PI/180) - (my)*cosf(roll*PI/180);
			float psi_den = (mx)*cosf(pitch*PI/180) + (my)*sinf(pitch*PI/180)*sin(roll*PI/180)+(mz)*sinf(pitch*PI/180)*cos(roll*PI/180);
			//yaw = 0.9*yaw + 0.1*atan2f(psi_num,psi_den)*180/PI;

			float yaw_aux = 0;
			if(fabsf(atan2f(psi_num,psi_den)*180/PI)>90)
			{
				//yaw = 0.9*yaw + 0.1*(atan2f(-psi_num,-psi_den)*180/PI - 180.0);
				Aux_Yaw = atan2f(-psi_num,-psi_den)*180/PI - 180.0;
			}
			else
			{
				//yaw = 0.9*yaw + 0.1*atan2f(psi_num,psi_den)*180/PI;
				Aux_Yaw =atan2f(psi_num,psi_den)*180/PI;
			}
			yaw = 0.99*yaw + 0.01*Get_Angle(-1.0*Aux_Yaw +1.0*Initial_Yaw);

			mx = mmx;
			my = mmy;
			mz = mmz;

			//Toggle_Pin(&GREEN_PIN);
		}
		//Toggle_Pin(&RED_PIN);

#ifdef Nates_Filter

		Ax_F = Ax_F + (0.1)*(ax - Ax_F);
		Ay_F = Ay_F + (0.1)*(ay - Ay_F);
		Az_F = Az_F + (0.1)*(az - Az_F);

		Gxxx = Gxxx + 0.01*(gx);
		Gyyy = Gyyy + 0.01*(gy);
		Gzzz = Gzzz + 0.01*(gz);


		Gxxx *= 0.9;
		Gyyy *= 0.9;
		Gzzz *= 0.9;


		Gxx = gx;
		Gyy = gy;
		Gzz = gz;
		//Gxxx *=0.999;
		//Gyyy *=0.999;
		//Gzzz *=0.999;

		/*
		Gx_F = (0.98) * (Gx_F + gx - Gxx);
		Gy_F = (0.98) * (Gy_F + gy - Gyy);
		Gz_F = (0.98) * (Gz_F + gz - Gzz);
		Gxxx = Gxxx + 0.01*Gx_F;
		Gyyy = Gyyy + 0.01*Gy_F;
		Gzzz = Gzzz + 0.01*Gz_F;
		*/

		roll = -1.0 * Gyyy;
		pitch= -1.0 * Gxxx;
		roll+=180*atan2(Ax_F, sqrt(Ay_F*Ay_F+Az_F*Az_F))/PI;
		pitch+= 180*atan2(-1.0*Ay_F,Az_F)/PI;
		//roll+=180*atan2(Ax_F, sqrt(Ay_F*Ay_F+Az_F*Az_F))/PI;
		//pitch+= 180*atan2(-1.0*Ay_F,Az_F)/PI;

		//yaw = 	-1.0 * Gzzz;

#endif

		pitch+=-1.0 * gx * 0.002;
		roll +=-1.0 * gy * 0.002;

		//yaw= yaw*0.999; // add a forgetting factor on yaw;

		float AccCheck = fabsf(ax)+fabsf(ay)+fabsf(az);

		if(GYRO_ONLY==false)
		{
			if((AccCheck>0.7) && (AccCheck<1.5)) // If not garbage values
			{
				float pitch_A = 180*atan(-1.0*ay/az)/PI;
				pitch = 0.99*pitch + 0.01*pitch_A;

				float roll_A = 180*atan2(ax, sqrt(ay*ay+az*az))/PI;

				roll = 0.99*roll + 0.01*roll_A;

			}
		}


	}
	else
	{
		getStatus++;
	}

}


float Get_Angle(float Input_Angle)
{
	float myResult = 0;
	if(Input_Angle>180.0)
	{
		myResult = Input_Angle - 360;
	}
	else if(Input_Angle<(-180))
	{
		myResult = 360+ Input_Angle;
	}
	else
	{
		myResult = Input_Angle;
	}

	return myResult;
}


uint8_t Init_MPU()
{
	uint8_t d=0;
	uint8_t returnValue = 0;
	int i =0;
	do
	{
		if(MPU_Test_ID())
		{

		}
		else
		{
			break;
		}
		MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
		calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
		initMPU9250();

		d = readByte(MPU9250_ADDRESS,I2C_SLV0_CTRL);
		d = readByte(MPU9250_ADDRESS,I2C_SLV4_CTRL);
		initAK8963(magCalibration);

		d = readByte(AK8963_ADDRESS, WHO_AM_I_AK8963); // Read WHO_AM_I register for AK8963

		if(d==0x48)
		{
			//Success
		}
		else
		{
			break;
		}

		if(My_Saved_Settings.I_AM_WRITTEN==TRUE)
		{
			M_Calibration_State = M_COMPENSATED;
		}

		returnValue = 1;
	}while(0);

	return returnValue;
}




