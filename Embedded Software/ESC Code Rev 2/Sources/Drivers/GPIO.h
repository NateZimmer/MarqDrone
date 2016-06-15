/*
 * GPIO.h
 *
 *  Created on: Oct 22, 2014
 *      Author: 5016zimmern
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

//Generics

void Define_GPIO(PORTS PORT, bool Output, uint32_t Pin_Number);
void Set_Output_GPIO(PORTS PORT, uint32_t Pin_On, uint32_t Pin_Number);
void Setup_Pin(GPIO_HANDLES * GPIO_HANDLE); //If u wish to use handle
void Set_Pin(GPIO_HANDLES * GPIO_HANDLE,uint32_t Set_High); //If u wish to use handle
void Toggle_Pin(GPIO_HANDLES * GPIO_HANDLE);

//ESC Board 

void GPIO_Enable_All_Ports();
void Enable_LED();
void LED_On();
void LED_Off();
void LED_Toggle();
void Enable_LED_PWM_GPIO();
void Enable_OC_Reset_GPIO();
void Clear_Over_Current();
void Enable_Over_Current_Check();


//Freedom Board Only: 

void Setup_Freedom_Board_LED();
void Freedom_Board_LED_Toggle();
void Setup_Freedom_Red_LED_PWM();
void Set_Freedom_Red_LED_PWM_Value(uint32_t value);

extern uint16_t PWM_SPEED; //10000





#endif /* GPIO_H_ */
