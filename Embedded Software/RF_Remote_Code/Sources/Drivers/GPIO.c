/*
 * GPIO.c
 *
 *  Created on: Nov 8, 2014
 *      Author: Nate
 */

#include "GPIO.h"
#include "MKL25Z4.h"

#define FAN	(0x1<<29)
#define OUTPUT_EN (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK)

GPIO_HANDLES AUX_PIN = {PORTE,23,GPIO_OUTPUT};  
GPIO_HANDLES FAN_PIN = {PORTE,25,GPIO_OUTPUT};
GPIO_HANDLES GPIO_PIN = {PORTE,29,GPIO_OUTPUT}; //SW1 on schematic 
GPIO_HANDLES BUZZER_PIN = {PORTB,18,GPIO_OUTPUT};

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
		PORT_PCR_REG(PORTA_BASE_PTR,Pin_Number) = OUTPUT_EN;
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
		PORT_PCR_REG(PORTB_BASE_PTR,Pin_Number) = OUTPUT_EN;
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
		PORT_PCR_REG(PORTC_BASE_PTR,Pin_Number) = OUTPUT_EN;
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
		PORT_PCR_REG(PORTD_BASE_PTR,Pin_Number) = OUTPUT_EN;
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
		PORT_PCR_REG(PORTE_BASE_PTR,Pin_Number) = OUTPUT_EN;
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
	switch(GPIO_HANDLE->PORT)
	{
	case PORTA:
		GPIOA_PTOR = (1<<GPIO_HANDLE->Pin);
		break;
	case PORTB:
		GPIOB_PTOR = (1<<GPIO_HANDLE->Pin);
		break;
	case PORTC:
		GPIOC_PTOR = (1<<GPIO_HANDLE->Pin);
		break;
	case PORTD:
		GPIOD_PTOR = (1<<GPIO_HANDLE->Pin);
		break;
	case PORTE:
		GPIOE_PTOR = (1<<GPIO_HANDLE->Pin);
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

