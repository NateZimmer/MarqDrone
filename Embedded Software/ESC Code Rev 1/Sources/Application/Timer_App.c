/*
 * Timer_App.c
 *
 *  Created on: Jan 4, 2015
 *      Author: 5016zimmern
 */

#include "Timer_App.h"
#include "../Drivers/GPIO.h"
#include "Compare.h"
#include "TPM_PDD.h"

typedef enum
{
	PHASE_A_HS_ON = 0,
	PHASE_B_HS_ON = 1,
	PHASE_C_HS_ON = 2,
	PHASE_HS_ALL_OFF = 3
}HS_COMMUTATIONS;

volatile COMMUTATION_CYCLES PRIMARY_COMMUTATION = COMMUTATION_6; 

HS_COMMUTATIONS HS_COMMUTATION = PHASE_C_HS_ON;
#define MAX_SPEED 1000

//GPIO Must be HIGH to turn on HS

#define LS_PWM_OFF_VALUE 0 

/*
#define MIN_DUTY PWM_SPEED/20
#define MAX_DUTY PWM_SPEED/2
*/

static uint16_t MAX_DUTY =  1000;
static uint16_t MIN_DUTY = 100;
static uint32_t Duty_Cycle = 100;


bool ZeroFound =FALSE;
bool Sensorless_Drive_On = FALSE; 
uint16_t Pre_ZC_Timer_Value = 100; 
uint16_t Zero_Crossing_Time = 0; 

void Increment_Commutation()
{
	if(PRIMARY_COMMUTATION==COMMUTATION_6)
	{
		PRIMARY_COMMUTATION = COMMUTATION_1;
	}
	else if(PRIMARY_COMMUTATION !=COMMUTATION_OFF)
	{
		PRIMARY_COMMUTATION++;
	}
}

uint16_t counter = 0;

#define A_OUT_ENABLE Phase_A_H
#define B_OUT_ENABLE Phase_B_H
#define C_OUT_ENABLE Phase_C_H

#define A_IN TPM0_C0V
#define B_IN TPM0_C1V
#define C_IN TPM0_C2V

//TMP0 = PHASE A IN
//TMP1 = PHASE B IN
//TMP2 = PHASE C IN

void Set_Outputs(uint16_t Output_A, uint16_t Output_B, uint16_t Output_C)
{
	while(A_IN != Output_A)
	{
		A_IN = Output_A; 
	}
	while(B_IN != Output_B)
	{
		B_IN = Output_B; 
	}
	while(C_IN != Output_C)
	{
		C_IN = Output_C;
	}

}

void Handle_High_Side_Commutaitons()
{
	ZeroFound = FALSE;
	Zero_Crossing_Time = 0; 
	TPM2_CNT = 1; //Restart Counter 
	TPM0_MOD = 0;
	switch(PRIMARY_COMMUTATION)
	{
	case COMMUTATION_1: // HS A ON, LS B ON, PHASE C BEMF:Falling	
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,0); // PHASE BEMF
		Set_Outputs(0,Duty_Cycle,0); // Phase B PWM 
		CMP_Enable_Phase_C();	
		break;
	case COMMUTATION_2: // HS A ON, LS C ON, PHASE B BEMF:Rising
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,0); //PHASE BEMF
		Set_Pin(&C_OUT_ENABLE,1); //Enabled 
		Set_Outputs(0,0,Duty_Cycle); // Phase C PWM 
		CMP_Enable_Phase_B();
		break;
	case COMMUTATION_3:  // HS B ON, LS C ON, PHASE A BEMF:Falling
		Set_Pin(&A_OUT_ENABLE,0); //Phase BEMF 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,1); //Enabled 
		Set_Outputs(0,0,Duty_Cycle); // Phase C PWM 
		CMP_Enable_Phase_A();
		break;
	case COMMUTATION_4: // HS B ON, LS A ON, PHASE C BEMF:Rising 
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,0); //Phase BEMF
		Set_Outputs(Duty_Cycle,0,0); // Phase A PWM 
		CMP_Enable_Phase_C();	
		break;
	case COMMUTATION_5: // HS C ON, LS A ON, PHASE B BEMF:Falling
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,0); //Phase BEMF
		Set_Pin(&C_OUT_ENABLE,1); //Enabled
		Set_Outputs(Duty_Cycle,0,0); // Phase A PWM 
		CMP_Enable_Phase_B();
		break;
	case COMMUTATION_6: // HS C ON, LS B ON, PHASE A BEMF:Rising
		Set_Pin(&A_OUT_ENABLE,0); //Phase BEMF 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled 
		Set_Pin(&C_OUT_ENABLE,1); //Enabled
		Set_Outputs(0,Duty_Cycle,0); // Phase B PWM 	
		CMP_Enable_Phase_A();	
		break;
	default: // Shut everything off 
		//CMP_Enable_Phase_A(); // For test control // CMP will handle stall for starting 
		Set_Pin(&A_OUT_ENABLE,0); //Disabled
		Set_Pin(&B_OUT_ENABLE,0); //Disabled
		Set_Pin(&C_OUT_ENABLE,0); //Disabled
		Set_Outputs(0,0,0); // PWM OFF
		break;

	}
	TPM0_CNT = 0;
	TPM0_MOD = PWM_SPEED;
}

void Handle_Commutation()
{
	Increment_Commutation();
	Handle_High_Side_Commutaitons();
}

//Multi Phase Sensor System

uint16_t Compare = 0;





void HandleFilterUpdate()
{
	int32_t Target_Filter = 40;
	
	Target_Filter = 200000/(1+TPM1_MOD);
	
	if(Target_Filter<40)
		Target_Filter = 40;
	if(Target_Filter>200)
		Target_Filter = 200;
	CMP0_FPR &=~(0xFF);
	CMP0_FPR |= Target_Filter&0xFF;

}



static float filter2 = 0;

void Handle_Starting()
{
	static uint16_t counter2 = 0;
	static uint32_t Stall_Counter = 0; 
	static uint16_t Zero_Sequence_Counter = 0;
	static uint16_t Starting_Counts = 0;
	int ADC_Value = 0;
	
	
	if(STARTING_SEQUENCE==ALIGNMEANT_PHASE)
	{
		GPIOB_PSOR = (0x1<<17); // 2L Extern // Top Left
		TPM1_MOD = 20000;
		//STARTING_SEQUENCE = INITIAL_COMMUATIONS;
		STARTING_SEQUENCE = AQUIRED_ZERO_CROSSING;
		PRIMARY_COMMUTATION = COMMUTATION_6;
		Duty_Cycle = PWM_SPEED/20; 
		Handle_Commutation();
		PRIMARY_COMMUTATION = COMMUTATION_3;
		counter2 = 0; 
		Motor_Started = FALSE;
		TPM1_CONF &= ~(0x1<<17); // Stop trigger reload 
		
	}
	else if(STARTING_SEQUENCE == INITIAL_COMMUATIONS)
	{
		TPM1_MOD = 4000;
		Duty_Cycle = PWM_SPEED/10; 
		if(counter2>20)
		{
			STARTING_SEQUENCE = STALLING_MOTOR;
			PRIMARY_COMMUTATION = COMMUTATION_OFF;
			CMP_Enable_Phase_B();
			Compare=2;
		}
		Handle_Commutation();
		counter2++;
	}
	else if(STARTING_SEQUENCE ==AQUIRED_ZERO_CROSSING)
	{
		//TPM1_MOD = 0;
		TPM1_SC &=~(0x1<<3);
		TPM2_CNT = 1;
		GPIOB_PSOR = (0x1<<17); // 2L Extern // Top Left
		ADC_Value = ADC0_RA;
		filter2 = filter2+(float)0.01*(ADC_Value - filter2); 
		ADC_Value = (int)filter2;
		
		if(TPM1_MOD>8000)
		{
			PWM_SPEED = 10000;
		}
		else
		{
			PWM_SPEED = 5000;
		}
		HandleFilterUpdate();
		MIN_DUTY =PWM_SPEED/10+1;
		MAX_DUTY =PWM_SPEED*0.9-MIN_DUTY;
		Duty_Cycle = MIN_DUTY+ADC_Value*MAX_DUTY/(0xFFFF);  
		Handle_Commutation();	
	}

	
	TPM1_CNT = 1;
	
	//ADC0_SC1A |= 12;
	//ADC0_SC3 |= (0x1<<3);
}

