/*
 * Timer_App.h
 *
 *  Created on: Jan 4, 2015
 *      Author: 5016zimmern
 */

#ifndef TIMER_APP_H_
#define TIMER_APP_H_

#include <stdio.h>
#include <PE_Types.h>
#include "MKL25Z4.h"
#include "../Drivers/ESC.h"

void Handle_Commutation();
void Increment_Commutation();
void Handle_High_Side_Commutaitons();

void Handle_Starting(); //Multi Sensors

volatile extern COMMUTATION_CYCLES PRIMARY_COMMUTATION;
extern bool ZeroFound;
extern uint16_t Pre_ZC_Timer_Value; 
extern uint16_t Zero_Crossing_Time; 
extern bool Sensorless_Drive_On;
extern uint16_t Compare;
volatile extern uint32_t FailurePoint;
//extern uint16_t ZeroCrosses[7];
extern uint16_t Speed;


#endif /* TIMER_APP_H_ */
