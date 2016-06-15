/*
 * GPIO.c
 *
 *  Created on: Oct 22, 2014
 *      Author: 5016zimmern
 */

#include "GPIO.h"
#include "MKL25Z4.h"

#define OUTPUT_EN (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK)

//ESC Feature Pins 
#define LED (0x1<<4) //PORT C 
#define OC_RESET (0x1<<7) // PROT D

//Freedom Defines 

#define FREEDOM_RED_LED (0x1<<18)

// Driver Defines 

#define TPM_Cn_MODE  (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK)
#define TPM_MODULE    1000
#define TPM_INIT_VAL    25


uint16_t PWM_SPEED = 20000; 

void GPIO_Enable_All_Ports()
{
	 SIM_SCGC5 |=  SIM_SCGC5_PORTA_MASK |SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
}

void Define_GPIO(PORTS PORT, bool Output, uint32_t Pin_Number)
{
	GPIO_Enable_All_Ports();
	
	switch(PORT)
	{
	case PORTA:
		PORT_PCR_REG(PORTA_BASE_PTR,Pin_Number) |= OUTPUT_EN;
		if(Output)
		{
			 GPIOA_PDDR |= (1<<Pin_Number);
		}
		else
		{
			GPIOA_PDDR &=~ (1<<Pin_Number);
		}
		break;
	case PORTB:
		PORT_PCR_REG(PORTB_BASE_PTR,Pin_Number) |= OUTPUT_EN;
		if(Output)
		{
			 GPIOB_PDDR |= (1<<Pin_Number);
		}
		else
		{
			GPIOB_PDDR &=~ (1<<Pin_Number);
		}
		break;
	case PORTC:
		PORT_PCR_REG(PORTC_BASE_PTR,Pin_Number) |= OUTPUT_EN;
		if(Output)
		{
			 GPIOC_PDDR |= (1<<Pin_Number);
		}
		else
		{
			GPIOC_PDDR &=~ (1<<Pin_Number);
		}
		break;
	case PORTD:
		PORT_PCR_REG(PORTD_BASE_PTR,Pin_Number) |= OUTPUT_EN;
		if(Output)
		{
			 GPIOD_PDDR |= (1<<Pin_Number);
		}
		else
		{
			GPIOD_PDDR &=~ (1<<Pin_Number);
		}
		break;
	case PORTE:
		PORT_PCR_REG(PORTE_BASE_PTR,Pin_Number) |= OUTPUT_EN;
		if(Output)
		{
			 GPIOE_PDDR |= (1<<Pin_Number);
		}
		else
		{
			GPIOE_PDDR &=~ (1<<Pin_Number);
		}
		break;
	default:
		break;	
	}
}

void Setup_Pin(GPIO_HANDLES * GPIO_HANDLE)
{
	bool IsOutput = FALSE;
	if(GPIO_HANDLE->PIN_TYPE ==GPIO_OUTPUT)
	{
		IsOutput = TRUE;
	}
	Define_GPIO(GPIO_HANDLE->PORT, IsOutput,GPIO_HANDLE->Pin);
}

void Set_Pin(GPIO_HANDLES * GPIO_HANDLE,uint32_t Set_High)
{
	Set_Output_GPIO(GPIO_HANDLE->PORT, Set_High, GPIO_HANDLE->Pin);
}


void Toggle_Pin(GPIO_HANDLES * GPIO_HANDLE)
{
	uint32_t Pin_Number = GPIO_HANDLE->Pin;
	switch(GPIO_HANDLE->PORT)
	{
	case PORTA:
		GPIOA_PTOR |= (1<<Pin_Number);
		break;
	case PORTB:
		GPIOB_PTOR |= (1<<Pin_Number);
		break;
	case PORTC:
		GPIOC_PTOR |= (1<<Pin_Number);
		break;
	case PORTD:
		GPIOD_PTOR |= (1<<Pin_Number);
		break;
	case PORTE:
		GPIOE_PTOR |= (1<<Pin_Number);
		break;
	default:
		break;	
	}
}

void Set_Output_GPIO(PORTS PORT, uint32_t Pin_On, uint32_t Pin_Number)
{
	switch(PORT)
	{
	case PORTA:
		if(Pin_On)
		{
			 GPIOA_PSOR = (1<<Pin_Number);
		}
		else
		{
			GPIOA_PCOR = (1<<Pin_Number);
		}
		break;
	case PORTB:
		if(Pin_On)
		{
			 GPIOB_PSOR = (1<<Pin_Number);
		}
		else
		{
			GPIOB_PCOR = (1<<Pin_Number);
		}
		break;
	case PORTC:
		if(Pin_On)
		{
			 GPIOC_PSOR = (1<<Pin_Number);
		}
		else
		{
			GPIOC_PCOR = (1<<Pin_Number);
		}
		break;
	case PORTD:
		if(Pin_On)
		{
			 GPIOD_PSOR = (1<<Pin_Number);
		}
		else
		{
			GPIOD_PCOR = (1<<Pin_Number);
		}
		break;
	case PORTE:
		if(Pin_On)
		{
			 GPIOE_PSOR = (1<<Pin_Number);
		}
		else
		{
			GPIOE_PCOR = (1<<Pin_Number);
		}
		break;
	default:
		break;	
	}
}



void Enable_LED()
{
	 PORTC_PCR4 |= OUTPUT_EN;
	 GPIOC_PDDR |= LED; 	 
}

void Enable_OC_Reset_GPIO()
{
	PORTD_PCR7 |= OUTPUT_EN;
	GPIOD_PDDR |= OC_RESET;
}

void Clear_Over_Current()
{
	GPIOD_PSOR = OC_RESET;
}

void Enable_Over_Current_Check()
{
	GPIOD_PCOR = OC_RESET;
}

void Enable_LED_PWM_GPIO()
{
	SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	PORTC_PCR4 |=(0|PORT_PCR_MUX(4)); /* TPM2_CH0 enable on PTB18 */
	TPM0_MOD  = PWM_SPEED;  // 48mhz/480=100khz
	TPM0_C3SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM0_C3V  = PWM_SPEED/2;  /* ~50% pulse width */
	
	TPM0_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);     /* Edge Aligned PWM running from BUSCLK / 1 */ // 48mhz /2 = 24mhz 
}


void LED_On()
{
	GPIOC_PSOR = LED; 
}

void LED_Off()
{
	GPIOC_PCOR = LED; 
}

void LED_Toggle()
{
	GPIOC_PTOR = LED;
}

void Setup_Freedom_Board_LED()
{
    PORTB_PCR18 |= OUTPUT_EN;
    GPIOB_PDDR |= FREEDOM_RED_LED;
    /*
	SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK);
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //

    PORTB_PCR18 = (0|PORT_PCR_MUX(3)); // TPM2_CH0 enable on PTB18 
    */
}

void Setup_Freedom_Red_LED_PWM()
{
	SIM_SCGC6|=( SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK); // Power to TPM modules 
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); // Need to look this one up 
	PORTB_PCR18 |=(0|PORT_PCR_MUX(3)); /* TPM2_CH0 enable on PTB18 */
	TPM2_MOD  = TPM_MODULE;  /* 0x0063 / 25MHz = 4uS PWM period */
	TPM2_C0SC = TPM_Cn_MODE;   /* No Interrupts; Low True pulses on Edge Aligned PWM */
	TPM2_C0V  = TPM_INIT_VAL;  /* 90% pulse width */
	TPM2_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);     /* Edge Aligned PWM running from BUSCLK / 1 */
}

void Set_Freedom_Red_LED_PWM_Value(uint32_t value)
{
	TPM2_C0V = value;
}

void Freedom_Board_LED_Toggle()
{
	GPIOB_PTOR = FREEDOM_RED_LED;
}
