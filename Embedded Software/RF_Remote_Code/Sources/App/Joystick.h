/*
 * Joystick.h
 *
 *  Created on: Jan 3, 2016
 *      Author: Z
 */

#ifndef SOURCES_APP_JOYSTICK_H_
#define SOURCES_APP_JOYSTICK_H_

#include "../Drivers/ADC.h"

#define THROTTLE_RANGE 100
#define RIGHT_RANGE 50 // Right joystick ranges

int16_t GET_R_THROTTLE();
int16_t GET_R_ROLL();
int16_t GET_R_PITCH();
int16_t GET_R_YAW();

extern bool POT_Min_Max_Cal;
extern bool POT_Mid_Cal;

extern int16_t Roll_Offset;
extern int16_t Pitch_Offset;


void HandleADC();
void Handle_ADC_Cals();
void Init_Joystick_Values(uint8_t Reset_Mid);
void Handle_Button_Presses();


#endif /* SOURCES_APP_JOYSTICK_H_ */
