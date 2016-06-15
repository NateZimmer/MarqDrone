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


//uint16_t ZeroCrosses[7]={0,0,0,0,0,0,0};


bool ZeroFound =FALSE;
bool Sensorless_Drive_On = FALSE; 
uint16_t Pre_ZC_Timer_Value = 100; 
uint16_t Zero_Crossing_Time = 0; 

void Increment_Commutation()
{
	FailurePoint = 1<<8;
	if(PRIMARY_COMMUTATION==COMMUTATION_6)
	{
		//ZeroCrosses[PRIMARY_COMMUTATION]=TPM1_MOD; // Store Zero Crossings 
		PRIMARY_COMMUTATION = COMMUTATION_1;
	}
	else if(PRIMARY_COMMUTATION !=COMMUTATION_OFF)
	{
		//ZeroCrosses[PRIMARY_COMMUTATION]=TPM1_MOD; // Store Zero Crossings 
		PRIMARY_COMMUTATION++;
	}
}

uint16_t counter = 0;

//TMP0 = PHASE A IN
//TMP1 = PHASE B IN
//TMP2 = PHASE C IN

volatile uint32_t FailurePoint = 0;

void Handle_High_Side_Commutaitons()
{
	FailurePoint = 0;
	TPM0_SC &=~(0x1<<3);
	TPM1_CNT = 1;
	
	ZeroFound = FALSE;
	Zero_Crossing_Time = 0; 
	TPM2_CNT = 1; //Restart Counter 
	TPM0_MOD = 0;
	FailurePoint = 1<<0;
	switch(PRIMARY_COMMUTATION)
	{
	case COMMUTATION_1: // HS A ON, LS B ON, PHASE C BEMF:Falling	
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,0); // PHASE BEMF
		FailurePoint = 1<<2;
		Set_Outputs(0,Duty_Cycle,0); // Phase B PWM 
		FailurePoint = 1<<3;
		CMP_Enable_Phase_C(FALSE);	
		FailurePoint = 1<<4;
		break;
	case COMMUTATION_2: // HS A ON, LS C ON, PHASE B BEMF:Rising
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,0); //PHASE BEMF
		Set_Pin(&C_OUT_ENABLE,1); //Enabled 
		FailurePoint = 1<<2;
		Set_Outputs(0,0,Duty_Cycle); // Phase C PWM 
		FailurePoint = 1<<3;
		CMP_Enable_Phase_B(TRUE);
		FailurePoint = 1<<4;
		break;
	case COMMUTATION_3:  // HS B ON, LS C ON, PHASE A BEMF:Falling
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,0); //Phase BEMF 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,1); //Enabled 
		FailurePoint = 1<<2;
		Set_Outputs(0,0,Duty_Cycle); // Phase C PWM 
		FailurePoint = 1<<3;
		CMP_Enable_Phase_A(FALSE);
		FailurePoint = 1<<4;
		break;
	case COMMUTATION_4: // HS B ON, LS A ON, PHASE C BEMF:Rising 
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled
		Set_Pin(&C_OUT_ENABLE,0); //Phase BEMF
		FailurePoint = 1<<2;
		Set_Outputs(Duty_Cycle,0,0); // Phase A PWM 
		FailurePoint = 1<<3;
		CMP_Enable_Phase_C(TRUE);	
		FailurePoint = 1<<4;
		break;
	case COMMUTATION_5: // HS C ON, LS A ON, PHASE B BEMF:Falling
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,1); //Enabled 
		Set_Pin(&B_OUT_ENABLE,0); //Phase BEMF
		Set_Pin(&C_OUT_ENABLE,1); //Enabled
		FailurePoint = 1<<2;
		Set_Outputs(Duty_Cycle,0,0); // Phase A PWM 
		FailurePoint = 1<<3;
		CMP_Enable_Phase_B(FALSE);
		FailurePoint = 1<<4;
		break;
	case COMMUTATION_6: // HS C ON, LS B ON, PHASE A BEMF:Rising
		FailurePoint = 1<<1;
		Set_Pin(&A_OUT_ENABLE,0); //Phase BEMF 
		Set_Pin(&B_OUT_ENABLE,1); //Enabled 
		Set_Pin(&C_OUT_ENABLE,1); //Enabled
		FailurePoint = 1<<2;
		Set_Outputs(0,Duty_Cycle,0); // Phase B PWM 	
		FailurePoint = 1<<3;
		CMP_Enable_Phase_A(TRUE);
		FailurePoint = 1<<4;
		break;
	default: // Shut everything off 
		//CMP_Enable_Phase_A(); // For test control // CMP will handle stall for starting 
		Set_Pin(&A_OUT_ENABLE,0); //Disabled
		Set_Pin(&B_OUT_ENABLE,0); //Disabled
		Set_Pin(&C_OUT_ENABLE,0); //Disabled
		Set_Outputs(0,0,0); // PWM OFF
		break;

	}
	FailurePoint = 1<<5;
	TPM0_CNT = 0;
	FailurePoint = 1<<6;
	TPM0_MOD = PWM_SPEED;
	TPM0_SC |=(0x1<<3);
	FailurePoint = 1<<7;
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
	
	Target_Filter = 200000/(1+TPM1_MOD/2);
	
	if(Target_Filter<40)
		Target_Filter = 40;
	if(Target_Filter>200)
		Target_Filter = 200;
	CMP0_FPR &=~(0xFF);
	CMP0_FPR |= Target_Filter&0xFF;

}



static float filter2 = 0;
uint16_t Speed = 30;

void Handle_Starting()
{
	static uint16_t counter2 = 0;
	int ADC_Value = 0;
	FailurePoint = 1<<9;
	if(STARTING_SEQUENCE==ALIGNMEANT_PHASE)
	{
		TPM1_MOD = 1000;
		counter2 =0;
		//STARTING_SEQUENCE = INITIAL_COMMUATIONS;
		//ZeroFound = true;
		Handle_Commutation();
		TPM1_SC |=(0x1<<3);

		
	}
	else if(STARTING_SEQUENCE == INITIAL_COMMUATIONS)
	{
		TPM1_MOD = 2000;
		PWM_SPEED = 5000;
		Duty_Cycle = PWM_SPEED/30; 
		counter2++;
		Handle_Commutation();
		if(counter2>10)
		{
			STARTING_SEQUENCE = AQUIRED_ZERO_CROSSING;
		}
	}
	else if(STARTING_SEQUENCE ==AQUIRED_ZERO_CROSSING)
	{
		//TPM1_MOD = 0;
		TPM1_SC &=~(0x1<<3);
		TPM2_CNT = 1;
		//GPIOB_PSOR = (0x1<<17); // 2L Extern // Top Left
		//ADC_Value = ADC0_RA;
		FailurePoint = 1<<25;
		filter2 = filter2+(float)0.0005*(Speed - filter2); 
		ADC_Value = (int)filter2;
		FailurePoint = 1<<26;
		
		/*
		PWM_SPEED = TPM1_MOD/10;
		if(PWM_SPEED<5000)
		{
			PWM_SPEED = 5000;
		}
		*/
		
		/*
		if(TPM1_MOD>8000)
		{
			PWM_SPEED = 10000;
		}
		else
		{
			PWM_SPEED = 5000;
		}
		*/
		
		//HandleFilterUpdate();
		MIN_DUTY =PWM_SPEED/10+1;
		MAX_DUTY =PWM_SPEED*0.9-MIN_DUTY;
		//Duty_Cycle = MIN_DUTY+ADC_Value*MAX_DUTY/(0xFFFF);  
		Duty_Cycle = MIN_DUTY+ADC_Value*MAX_DUTY/100; 
		FailurePoint = 1<<27;
		Handle_Commutation();	
	}
	else if(STARTING_SEQUENCE==MOTOR_OFF)
	{
		PWM_SPEED=0;
	}
	FailurePoint = 1<<28;
	TPM1_CNT = 1;
	FailurePoint = 1<<29;
	//ADC0_SC1A |= 12;
	//ADC0_SC3 |= (0x1<<3);
}

