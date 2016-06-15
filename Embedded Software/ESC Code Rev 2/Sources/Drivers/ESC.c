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

//Primary Drive Pins 






#ifdef REV2

GPIO_HANDLES A_OUT_ENABLE = {PORTD,3,GPIO_OUTPUT};  
GPIO_HANDLES B_OUT_ENABLE = {PORTC,9,GPIO_OUTPUT};  
GPIO_HANDLES C_OUT_ENABLE = {PORTD,0,GPIO_OUTPUT}; 
#define A_IN TPM0_C2V
#define B_IN TPM0_C4V
#define C_IN TPM0_C1V
GPIO_HANDLES LED = {PORTD,7,GPIO_OUTPUT}; 

#endif

//Rev1

#ifdef REV1
GPIO_HANDLES A_OUT_ENABLE = {PORTD,3,GPIO_OUTPUT};  
GPIO_HANDLES B_OUT_ENABLE = {PORTC,8,GPIO_OUTPUT}; 
GPIO_HANDLES C_OUT_ENABLE = {PORTC,9,GPIO_OUTPUT}; 
#define A_IN TPM0_C0V
#define B_IN TPM0_C1V
#define C_IN TPM0_C2V
GPIO_HANDLES OC_RESET = {PORTD,7,GPIO_OUTPUT}; 
#endif

STARTING_SEQUENCES STARTING_SEQUENCE = ALIGNMEANT_PHASE;

#define LS_Starting_Value 0
#define TPM_MODULE    1000
#define TPM_INIT_VAL    25

bool Motor_Started = FALSE; 




void Init_IN_PWM_GPIO()
{
	//SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    //SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	
	SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	TPM0_MOD  = PWM_SPEED;  // 48mhz/480=100khz
	TPM0_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);     /* Edge Aligned PWM running from BUSCLK / 1 */ // 48mhz /2 = 24mhz 

	
#ifdef REV2
	PORTC_PCR8 |=(0|PORT_PCR_MUX(3)); // PTC8 IN PWM pin TMP4
	PORTD_PCR1 |=(0|PORT_PCR_MUX(4)); // IN PWM pin TPM1
	PORTD_PCR2 |=(0|PORT_PCR_MUX(4)); // IN PWM pin TPM2
	TPM0_C4SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C1SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C2SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C4V  = LS_Starting_Value; // Start Off
	TPM0_C1V  = LS_Starting_Value; // Start Off
	TPM0_C2V  = LS_Starting_Value; // Start Off
#endif
	
#ifdef REV1
	PORTD_PCR0 |=(0|PORT_PCR_MUX(4)); //Phase A LS / D0 / TMP0 C 0
	PORTD_PCR1 |=(0|PORT_PCR_MUX(4)); //Phase B LS / D1 / TMP0 C 1
	PORTD_PCR2 |=(0|PORT_PCR_MUX(4)); //Phase C LS / D2 / TMP0 C 2
	
	TPM0_C0SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C1SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C2SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C0V  = LS_Starting_Value; // Start Off
	TPM0_C1V  = LS_Starting_Value; // Start Off
	TPM0_C2V  = LS_Starting_Value; // Start Off
	
	Setup_Pin(&OC_RESET); // Turn on LED
	Set_Pin(&OC_RESET,1);
#endif
	
	//PORTE_PCR25 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | (0x1<<19) |PORT_PCR_MUX(1) ;
	
}


void Commutate_Phase(COMMUTATION_CYCLES COMMUTATION_CYCLE)
{
	switch(COMMUTATION_CYCLE)
	{
	case COMMUTATION_1:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_2:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_3:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_4:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_5:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_6:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	case COMMUTATION_OFF:
		Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	default:
		Set_Pin(&A_OUT_ENABLE,0); 
		Set_Pin(&B_OUT_ENABLE,0);
		Set_Pin(&C_OUT_ENABLE,0);
		break;
	}
}

/*
void SetPhase(uint16_t PhaseA, uint16_t Phase B, uint16_t PhaseC)
{
	PhaseA ? Set_Pin(&A_OUT_ENABLE,0) : Set_Pin(&A_OUT_ENABLE,1); 
	Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
	Set_Pin(&B_OUT_ENABLE,0);
	Set_Pin(&C_OUT_ENABLE,1);
}
*/

void delayS(uint32_t ms)
{
	volatile uint32_t i = 0; 
	for(i=0;i<(10*ms);i++){}
}



void SetPhase(uint16_t PhaseA, uint16_t PhaseB, uint16_t PhaseC)
{
	PhaseA ? Set_Pin(&A_OUT_ENABLE,1) : Set_Pin(&A_OUT_ENABLE,0); 
	PhaseB ? Set_Pin(&B_OUT_ENABLE,1) : Set_Pin(&B_OUT_ENABLE,0); 
	PhaseC ? Set_Pin(&C_OUT_ENABLE,1) : Set_Pin(&C_OUT_ENABLE,0); 
}


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


void ESC_Init_GPIO()
{
	Commutate_Phase(COMMUTATION_OFF); // Ensure GPIO are in safe position before enabled 
	GPIO_Enable_All_Ports(); //Give power to ports
	
	Setup_Pin(&A_OUT_ENABLE); // Setup Enable pins, these are not PWM-ed 
	Setup_Pin(&B_OUT_ENABLE); // IN pins will be PWM-ed 
	Setup_Pin(&C_OUT_ENABLE);
	
	Set_Pin(&A_OUT_ENABLE,0); // Set pins to High Z state
	Set_Pin(&B_OUT_ENABLE,0);
	Set_Pin(&C_OUT_ENABLE,0);
	
#ifdef REV2
	Setup_Pin(&LED);
	Set_Pin(&LED,0);
#endif
	
	PORTC_PCR6 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
	PORTC_PCR7 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
	PORTE_PCR30 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
	
	
	//Setup_Pin(&LED); // Turn on LED
	//Set_Pin(&LED,0);
	
	//Init_IN_PWM_GPIO(); // Init PWM Pins 
	
	SetPhase(1,0,0);
	Set_Outputs(1000,0,0);
	//while(1);
	delayS(1000);
	SetPhase(0,1,0);
	Set_Outputs(0,1000,0);
	//while(1);
	delayS(1000);
	SetPhase(0,0,1);
	Set_Outputs(0,0,1000);
	delayS(1000);
	//while(1);
	SetPhase(0,0,0);
	Set_Outputs(0,0,0);
	//Set_Pin(&LED,1);
	//while(1);

}


