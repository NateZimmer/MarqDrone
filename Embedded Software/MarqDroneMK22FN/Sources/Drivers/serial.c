/*
 * serial.c
 *
 *  Created on: May 19, 2016
 *      Author: Z
 */

#include <string.h>
#include <stdint.h>
#include "Init_Config.h"
#include "../../Generated_Code/UART0.h"
#include "MK22F51212.h"
#include "UART_PDD.h"

void uartPrintString(char * myString)
{
	uint16_t i = 0;
	for(i = 0; i<strlen(myString);i++)
	{
		while(UART_PDD_GetTxCompleteStatus(UART0_DEVICE)==0);
		UART_PDD_PutChar8(UART0_DEVICE,myString[i]);
	}
}
