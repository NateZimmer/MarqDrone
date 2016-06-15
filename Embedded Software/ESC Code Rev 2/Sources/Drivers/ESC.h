/*
 * ESC.h
 *
 *  Created on: Nov 3, 2014
 *      Author: 5016zimmern
 */

#ifndef ESC_H_
#define ESC_H_


#define REV2

#include <stdint.h>
#include "GPIO.h"
#include "MKL25Z4.h"

#define TPM_Cn_MODE  (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK)

#define ESC_PORT_D_IO (PHASE_A_HIGH_GPIO|PHASE_A_LOW_GPIO|PHASE_B_LOW_GPIO|PHASE_C_LOW_GPIO)
#define ESC_PORT_C_IO (PHASE_B_HIGH_GPIO|PHASE_C_HIGH_GPIO)

// HIGH must be HIGH to turn on (see schematic)
// LOW must be LOW to turn on (see schematic)


#define LS_OFF PHASE_A_LOW_OFF; PHASE_B_LOW_OFF; PHASE_C_LOW_OFF

//Final Defines 

//Control all phases digitially

//#define PHASE_A_LS_PWM TPM0_C0V
//#define PHASE_B_LS_PWM TPM0_C1V
//#define PHASE_C_LS_PWM TPM0_C2V

typedef enum
{
	COMMUTATION_1=0,
	COMMUTATION_2=1,
	COMMUTATION_3=2,
	COMMUTATION_4=3,
	COMMUTATION_5=4,
	COMMUTATION_6=5,
	COMMUTATION_OFF=6,
	COMMUTATION_1_OFF = 7,
	COMMUTATION_2_OFF = 8,
	COMMUTATION_3_OFF = 9,
	COMMUTATION_4_OFF = 10,
	COMMUTATION_5_OFF = 11,
	COMMUTATION_6_OFF = 12
}COMMUTATION_CYCLES;


typedef enum
{
	ALIGNMEANT_PHASE=0,
	INITIAL_COMMUATIONS=1,
	STALLING_MOTOR=2,
	AQUIRED_ZERO_CROSSING=3,
	CROSSING_START=4,
	SENSORLESS_MODE=5,
	MOTOR_OFF=6
}STARTING_SEQUENCES;

typedef struct
{
	union
	{
		struct
		{
			uint16_t Z1;
			uint16_t Z2;
			uint16_t Z3;
			uint16_t Z4;
			uint16_t Z5;
			uint16_t Z6;
			uint16_t Null;
		};
		uint16_t Index[7];
	};
}ZERO_CROSSINGS;

extern STARTING_SEQUENCES STARTING_SEQUENCE;
extern COMMUTATION_CYCLES COMMUTATION_CYCLE;
extern ZERO_CROSSINGS Zero_Crossing;

extern GPIO_HANDLES MC_PUMP;
extern bool Motor_Started;

extern GPIO_HANDLES Phase_A_L; 
extern GPIO_HANDLES A_OUT_ENABLE;
extern GPIO_HANDLES Phase_B_L;
extern GPIO_HANDLES B_OUT_ENABLE;
extern GPIO_HANDLES Phase_C_L;
extern GPIO_HANDLES C_OUT_ENABLE;
extern GPIO_HANDLES LED;


void Commutate_Phase(COMMUTATION_CYCLES COMMUTATION_CYCLE);
void Commutation_Extended(COMMUTATION_CYCLES COMMUTATION_CYCLE);
void ESC_Init_GPIO();
void Init_IN_PWM_GPIO();
void ESC_NO_PWM();
void Set_Outputs(uint16_t Output_A, uint16_t Output_B, uint16_t Output_C);
void SetPhase(uint16_t PhaseA, uint16_t PhaseB, uint16_t PhaseC);

#endif /* ESC_H_ */
