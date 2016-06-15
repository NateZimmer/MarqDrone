/*
 * ESC.c
 *
 *  Created on: Nov 3, 2014
 *      Author: 5016zimmern
 */

#include "ESC.h"


//ESC Gate Pins

#define OUTPUT_EN (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK)

//Start of functions 

//Steps: 1  2  3  4  5  6
//HIGH:           A  A
//OFF :        A        A
//LOW :  A  A  

//Steps: 1  2  3  4  5  6
//HIGH:     B  B  
//OFF :  B        B
//LOW :              B  B

//Steps: 1  2  3  4  5  6
//HIGH:  C              C
//OFF :     C        C
//LOW :        C  C  

#define MAX_SPEED 1000

COMMUTATION_CYCLES COMMUTATION_CYCLE = COMMUTATION_1;

// Extern Pins 
GPIO_HANDLES MC_PUMP = {PORTB,19,GPIO_OUTPUT}; // REV2 

GPIO_HANDLES Extern_1_L = {PORTB,16,GPIO_OUTPUT};  
GPIO_HANDLES Extern_1_H = {PORTB,17,GPIO_OUTPUT};
//GPIO_HANDLES Extern_2_L = {PORTB,19,GPIO_OUTPUT};
GPIO_HANDLES Extern_2_H = {PORTB,18,GPIO_OUTPUT};
GPIO_HANDLES Extern_3_L = {PORTB,0,GPIO_OUTPUT};
GPIO_HANDLES Extern_3_H = {PORTC,3,GPIO_OUTPUT};
GPIO_HANDLES LED = {PORTC,4,GPIO_OUTPUT};

//Primary Drive Pins 
GPIO_HANDLES Phase_A_L = {PORTD,0,GPIO_OUTPUT};  
GPIO_HANDLES Phase_A_H = {PORTD,3,GPIO_OUTPUT};  
GPIO_HANDLES Phase_B_L = {PORTD,1,GPIO_OUTPUT};  
GPIO_HANDLES Phase_B_H = {PORTC,8,GPIO_OUTPUT};  
GPIO_HANDLES Phase_C_L = {PORTD,2,GPIO_OUTPUT};  
GPIO_HANDLES Phase_C_H = {PORTC,9,GPIO_OUTPUT}; 


//GPIO_HANDLES Phase_A_L = {PORTD,0,GPIO_OUTPUT}; 
//GPIO_HANDLES Phase_B_L = {PORTD,1,GPIO_OUTPUT}; 
//GPIO_HANDLES Phase_C_L = {PORTD,2,GPIO_OUTPUT}; 


STARTING_SEQUENCES STARTING_SEQUENCE = ALIGNMEANT_PHASE;

#define LS_Starting_Value 0
#define TPM_MODULE    1000
#define TPM_INIT_VAL    25

bool Motor_Started = FALSE; 

void Init_LS_PWM_GPIO()
{
	//SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    //SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	
	SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	TPM0_MOD  = PWM_SPEED;  // 48mhz/480=100khz
	TPM0_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);     /* Edge Aligned PWM running from BUSCLK / 1 */ // 48mhz /2 = 24mhz 

	
	PORTD_PCR0 |=(0|PORT_PCR_MUX(4)); //Phase A LS / D0 / TMP0 C 0
	PORTD_PCR1 |=(0|PORT_PCR_MUX(4)); //Phase B LS / D1 / TMP0 C 1
	PORTD_PCR2 |=(0|PORT_PCR_MUX(4)); //Phase C LS / D2 / TMP0 C 2
	
	TPM0_C0SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C1SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C2SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	
	TPM0_C0V  = LS_Starting_Value; // Start Off
	TPM0_C1V  = LS_Starting_Value; // Start Off
	TPM0_C2V  = LS_Starting_Value; // Start Off
	
}


void Commutate_Phase(COMMUTATION_CYCLES COMMUTATION_CYCLE)
{
	switch(COMMUTATION_CYCLE)
	{
	case COMMUTATION_1:
		PHASE_A_LOW;
		PHASE_B_OFF;
		PHASE_C_HIGH;
		break;
	case COMMUTATION_2:
		PHASE_A_LOW;
		PHASE_B_HIGH;
		PHASE_C_OFF;
		break;
	case COMMUTATION_3:
		PHASE_A_OFF;
		PHASE_B_HIGH;
		PHASE_C_LOW;
		break;
	case COMMUTATION_4:
		PHASE_A_HIGH;
		PHASE_B_OFF;
		PHASE_C_LOW;
		break;
	case COMMUTATION_5:
		PHASE_A_HIGH;
		PHASE_B_LOW;
		PHASE_C_OFF;
		break;
	case COMMUTATION_6:
		PHASE_A_OFF;
		PHASE_B_LOW;
		PHASE_C_HIGH;
		break;
	case COMMUTATION_OFF:
		PHASE_A_OFF;
		PHASE_B_OFF;
		PHASE_C_OFF;
		break;
	default:
		PHASE_A_OFF;
		PHASE_B_OFF;
		PHASE_C_OFF;
		break;
	}
}


void ESC_Init_GPIO()
{
	Commutate_Phase(COMMUTATION_OFF); // Ensure GPIO are in safe position before enabled 
	GPIO_Enable_All_Ports(); //Give power to ports
	
	//Set pin modes to GPIO
	
	//PORTD_PCR0 |= OUTPUT_EN; //1
	//PORTD_PCR1 |= OUTPUT_EN; //2
	//PORTD_PCR2 |= OUTPUT_EN; //3
	PORTD_PCR3 |= OUTPUT_EN; //4
	
	PORTC_PCR8 |= OUTPUT_EN; //5
	PORTC_PCR9 |= OUTPUT_EN; //6
	
	GPIOD_PDDR |= ESC_PORT_D_IO; //Enable port D pins as output
	GPIOC_PDDR |= ESC_PORT_C_IO; //Enable port C pins as output
	
	//Setup_Pin(&Extern_1_L);
	//Setup_Pin(&Extern_2_H);
	//Setup_Pin(&Extern_2_L);
	//Setup_Pin(&Extern_2_H);
	Setup_Pin(&Extern_1_H);
	
	Setup_Pin(&Extern_3_H);
	Set_Pin(&Extern_3_H,1);
	//Setup_Pin(&LED);
	
	Init_LS_PWM_GPIO();
	Setup_Pin(&MC_PUMP);
	Enable_OC_Reset_GPIO();
	Clear_Over_Current();
}

void ESC_NO_PWM()
{
	Setup_Pin(&Phase_A_L);
	Setup_Pin(&Phase_A_H);
	Setup_Pin(&Phase_B_L);
	Setup_Pin(&Phase_B_H);
	Setup_Pin(&Phase_C_L);
	Setup_Pin(&Phase_C_H);
}



