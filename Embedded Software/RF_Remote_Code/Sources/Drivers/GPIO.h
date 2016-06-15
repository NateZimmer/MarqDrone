/*
 * GPIO.h
 *
 *  Created on: Nov 8, 2014
 *      Author: Nate
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <PE_Types.h>


typedef enum 
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE
}PORTS;

typedef enum
{
	GPIO_OUTPUT= 0,
	GPIO_INPUT = 1
}PIN_TYPES;

typedef struct
{
	PORTS PORT;
	uint32_t Pin;
	PIN_TYPES PIN_TYPE;
}GPIO_HANDLES;

void Define_GPIO(PORTS PORT, bool Output, uint32_t Pin_Number);
void Set_Output_GPIO(PORTS PORT, uint32_t Pin_On, uint32_t Pin_Number);
void Setup_Pin(GPIO_HANDLES * GPIO_HANDLE); //If u wish to use handle
void Set_Pin(GPIO_HANDLES * GPIO_HANDLE,uint32_t Set_High); //If u wish to use handle
void Toggle_Pin(GPIO_HANDLES * GPIO_HANDLE);
void GPIO_Enable_All_Ports();


#endif /* GPIO_H_ */
