/*
 * Remote.c
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */


#include "GPIO.h"
#include "Remote.h"

GPIO_HANDLES POWER_LED = {PORTB,1,GPIO_OUTPUT};
GPIO_HANDLES GREEN_LED = {PORTB,2,GPIO_OUTPUT};
GPIO_HANDLES RED_LED = {PORTB,3,GPIO_OUTPUT};
GPIO_HANDLES BLUE_LED = {PORTB,16,GPIO_OUTPUT};
GPIO_HANDLES CC_CS_PIN = {PORTD, 0, GPIO_OUTPUT};

void Setup_Remote_IO()
{
	GPIO_Enable_All_Ports(); // Clk to ports

	Setup_Pin(&POWER_LED); //Define GPIOs as outputs
	//Setup_Pin(&GREEN_LED);
	//Setup_Pin(&RED_LED);
	Setup_Pin(&BLUE_LED);

	Setup_Pin(&CC_CS_PIN);

	Set_Pin(&POWER_LED,1); // Turn on power LED
	//Set_Pin(&GREEN_LED,1); // Turn off LED
	//Set_Pin(&RED_LED,1); // Turn off LED
	Set_Pin(&BLUE_LED,1); // Turn off LED

	Set_Pin(&CC_CS_PIN, 1);

}

/*
 *  Wrapper to turn on an LED.
 *  Provides abstraction since the Power LED is turned on by setting the GPIO pin high,
 *  while the RGB LEDs are turned on by setting their corresponding GPIO pins low.
 */
void Turn_On_LED(GPIO_HANDLES * GPIO_HANDLE, uint32_t on) {

	// Check if the handle passed is the handle of the power LED
	if (GPIO_HANDLE == &POWER_LED) {
		Set_Pin(GPIO_HANDLE, on);
	} else {
		Set_Pin(GPIO_HANDLE, ~(on));
	}
}
