/*
 * USB_Echo.c
 *
 *  Created on: Oct 26, 2015
 *      Author: Z
 */

#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "../../Generated_Code/usb_class.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "USB_Echo.h"
#include "../App/Commands.h"

#define USB_DEBUG	0

bool USB_INIT = false;
bool USB_RDY;


#define CMD_STRING_SIZE 30

uint8_t CMD_String_Buffer[CMD_STRING_SIZE];
uint16_t CMD_Index = 0;
bool Buffer_Overflow=0;
bool Command_Recieved = 0;


void Handle_USB_Read()
{
	static char myChar = 0;
	uint8_t Recieved_Data = 0;
	  if (USB1_GetCharsInRxBuf()!=0)
	    {
	      while(CDC1_GetChar(&Recieved_Data)==ERR_OK)
	      {


	    	USB1_SendChar(Recieved_Data);
	    	CMD_String_Buffer[CMD_Index] = Recieved_Data;

	    	do
	    	{

	    		if(CMD_Index>(CMD_STRING_SIZE-1)) // If buffer overflowed
	    		{
	    			Buffer_Overflow = true;
	    			break;
	    		}

				if(Recieved_Data=='\r') // if received enter key
				{
					Command_Recieved = true;
					break;
				}
	    		CMD_Index++;

	    	}while(0);

	    	if(Buffer_Overflow)
	    	{
	    		CMD_Index=0;
	    		CDC1_SendString((char *)CMD_Invalid_Str);
	    		memset(CMD_String_Buffer,0,CMD_STRING_SIZE);
	    	}

	    	if(Command_Recieved)
	    	{
	    		Command_Recieved = false;
	    		CDC1_SendString("\n");
	    		Handle_Command(CMD_String_Buffer);
	    		memset(CMD_String_Buffer,0,CMD_STRING_SIZE); // Erase command
	    		CMD_Index=0;
	    	}
	      }
	    }
}


uint32_t msg_counter = 0;
uint8_t localBuffer[10];
void debug_console(char * textBuffer)
{
	if(USB_DEBUG && USB_INIT)
	{
		sprintf(localBuffer,"%d ,",msg_counter);
		USB1_SendString(localBuffer);
		USB1_SendString(textBuffer);
		msg_counter++;
	}
	if(USB_RDY)
	{
		USB1_SendString(textBuffer);
	}
}
