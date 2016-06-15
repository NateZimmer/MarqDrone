/*
 * USB.c
 *
 *  Created on: Nov 15, 2015
 *      Author: Z
 */

#include "USB.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CS1.h"
#include "stdio.h"
#include "Commands.h"
#include "stdbool.h"


#define CMD_STRING_SIZE 50 // Defines the max characters in a single cmd line
uint8_t CMD_String_Buffer[CMD_STRING_SIZE];
uint8_t Previous_CMD[CMD_STRING_SIZE];

typedef enum
{
	NONE=0,
	ONEB=1,
	FONE=2,
}ARROW_CHECKS;

bool Command_Recieved = false;
static uint16_t CMD_Index = 0;

uint8_t CheckArrow(uint8_t Recieved_Data)
{
	static ARROW_CHECKS Arrow_Status =NONE;
	uint8_t returnVal = 0;
	switch(Arrow_Status)
	{
	case NONE:
		if(Recieved_Data==0x1b)
		{
			Arrow_Status=ONEB;
		}
		break;
	case ONEB:
		if(Recieved_Data==0x5b)
			Arrow_Status=FONE;
		else
			Arrow_Status =NONE;
		break;
	case FONE:
		if(Recieved_Data==0x41)
		{
			memcpy(CMD_String_Buffer,Previous_CMD,CMD_STRING_SIZE);
			CDC1_SendString("\n");
			CDC1_SendString(CMD_String_Buffer);
			CMD_Index = strlen(CMD_String_Buffer);
		}
			returnVal = 1;
		Arrow_Status =NONE;
		break;
	}
	return returnVal;
}

void Handle_USB_Read(uint8_t Recieved_Data)
{

	CMD_String_Buffer[CMD_Index] = Recieved_Data;
	Command_Recieved = false;
	bool Buffer_Overflow = false;
	CDC1_SendChar(Recieved_Data);
	do
	{
		if(CMD_String_Buffer[CMD_Index]==0x7f) // Handle Delete Key
		{
			if(CMD_Index>0)
			{
				CMD_String_Buffer[CMD_Index]=0;
				CMD_Index--;
			}
			break;
		}

		if(CheckArrow(Recieved_Data))
			break;

		if(CMD_String_Buffer[CMD_Index]=='\r') // if received enter key
		{
			Command_Recieved = true;
			break;
		}
		if(CMD_Index>sizeof(CMD_String_Buffer)-1) // If buffer overflowed
		{
			Buffer_Overflow = true;
			break;
		}
		CMD_Index++;
	} while (0);

	if(Buffer_Overflow)
	{
		CMD_Index=0;
		CDC1_SendString((char *)CMD_Invalid_Str);
		memset(CMD_String_Buffer,0,CMD_STRING_SIZE);
	}

	if(Command_Recieved)
	{
		CDC1_SendString("\n");
		Handle_Command(CMD_String_Buffer);
		memcpy(Previous_CMD,CMD_String_Buffer,CMD_STRING_SIZE); // Store previous command
		memset(CMD_String_Buffer,0,CMD_STRING_SIZE); // Erase command
		CMD_Index=0;
	}
}

void Handle_USB()
{
	uint32_t i = 0;
	uint8_t bufferChar =0;
    if (CDC1_GetCharsInRxBuf()!=0)
    {
		i = 0;
		while(CDC1_GetChar(&bufferChar)==ERR_OK)
		{
			i++;
			Handle_USB_Read(bufferChar);
		}
    }
}

/*
 static void CDC_Run(void) {
  int i, cnt = 0;
  uint32_t val = 0;
  unsigned char buf[16];

    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      //LED1_Neg(); LED2_Off();
      //WAIT1_Waitms(10);
    }
    //LED1_Off(); LED2_Neg();
    if (CDC1_GetCharsInRxBuf()!=0) {
      i = 0;
      while(   i<sizeof(in_buffer)-1
            && CDC1_GetChar(&in_buffer[i])==ERR_OK
           )
      {
        i++;
      }
      in_buffer[i] = '\0';
      (void)CDC1_SendString((unsigned char*)"echo: ");
      (void)CDC1_SendString(in_buffer);
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), val);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      (void)CDC1_SendString(buf);
      val++;
    } else {
      WAIT1_Waitms(10);
      cnt++;
      if ((cnt%1024)==0) {
        (void)CDC1_SendString((unsigned char*)"Type some text and it will echo.\r\n");
        CDC1_SendBlock((unsigned char*)"hello?\r\n", sizeof("hello?\r\n")-1);
      }
    }

    WAIT1_Waitms(10);
    Set_Pin(&BLUE_PIN,0);
    Read_MPU92500_Reg(WHO_AM_I_MPU9250);
    readBytes(0,WHO_AM_I_MPU9250-2, 4, bufferZ);
    Set_Pin(&BLUE_PIN,1);

    if(debug_enable)
    {
		while(CDC1_GetCharsInRxBuf()==0);
		while(CDC1_GetChar(&in_buffer[i])==ERR_OK)
		{
			if(i>sizeof(in_buffer)-1)
			{
				break;
			}
			i++;
		}
    }


}
*/

