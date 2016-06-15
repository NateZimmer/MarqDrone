/*
 * Commands.c
 *
 * Created: 7/13/2015 1:09:48 PM
 *  Author: Nate
 */ 

#include "Commands.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CS1.h"
#include "IMU_Data.h"
#include "Drivers/ADC.h"
#include "App/Joystick.h"
#include <stdio.h>
#include "Saved_Settings.h"
#include "RF_Control.h"
#include "../Drivers/Timer.h"
#include "../Drivers/USB_Echo.h"

const char * CMD_Invalid_Str = "Invalid Command!\r\n";
const char * CMD_Valid_Str = "OK!\r\n";

uint8_t TRANSMIT_PID_GAINS = 0;

int16_t Pitch_P = 0;
int16_t Pitch_I = 0;
int16_t Pitch_D = 0;
int16_t Roll_P = 0;
int16_t Roll_I = 0;
int16_t Roll_D = 0;
int16_t Yaw_P = 0;
int16_t Yaw_I = 0;
int16_t Yaw_D = 0;

#define CMD_STRING_SIZE 50 // Defines the max characters in a single cmd line
uint8_t PrintBuffer[CMD_STRING_SIZE];

const char * GUI_Command_Set[] = {
	"GET_ACC", 		//1
	"GET_MAG", 		//2
	"GET_GYRO", 	//3
	"GET_ATT", 		//4
	"WHO_AM_I", 	//5
	"AT", 			//6
	"RESET", 		//7
	"SET_M_CAL",	//8
	"GET_M_CAL",	//9
	"GET_K",		//10
	"SET_MOTOR",	//11
	"R_CAL_MM",		//12
	"R_CAL_MID",	//13
	"GET_R", 		//14
	"SAVE",			//15
	"MODE",			//16
	"MOTOR_SPEED",	//17
	"PACKET_RATE",	//18
	"GET_R_MODE", 	//19
	"GET_D_MODE",	//20
	"GET_CPU",		//21
	"EN_PID_GAIN",	//22,
	"SET_PID_GAIN",	//23,
	"GET_PID_GAIN",	//24
	"GET_MTR",		//25
};

#define NUMBER_OF_COMMANDS (sizeof(GUI_Command_Set)/sizeof(GUI_Command_Set[0]))

////////////////////////////////////////////////////
// Returns Input String with command removed 
// Returns the GUI_Command if any
////////////////////////////////////////////////////

char * Get_GUI_Command(char * Input_String, GUI_COMMANDS * GUI_Command)
{
	uint16_t i = 0;
	char * returnVal;
	*GUI_Command = NULL_COMMAND;
	for(i=0;i<NUMBER_OF_COMMANDS;i++) // Check versus all commands
	{
		returnVal =strstr((const char *)Input_String,GUI_Command_Set[i]); // Compare strings 
		if(returnVal==Input_String) // Returns null if strings are not equal
		{
			returnVal+=strlen(GUI_Command_Set[i]);
			if((returnVal[0]=='\r')||(returnVal[0]==','))
			{
				*GUI_Command = (GUI_COMMANDS)(1+i);
				break;
			}
			

		}
	}
	return returnVal;
}

void Write_CDC_String(char * Input_String)
{
	CDC1_SendString(Input_String);
}

char * Get_Hex_Value(char * Input_String,uint32_t  * Hex_Value)
{
	char * returnVal;
	char * tempPtr;
	tempPtr=Input_String;
	if(tempPtr[0]==',')
	{
		tempPtr++;
	}
	*Hex_Value = (uint32_t)strtoul((const char *)tempPtr,&returnVal,16);
	return returnVal;
}

char * Get_Hex_Value_Signed(char * Input_String,int32_t  * Hex_Value)
{
	char * returnVal;
	char * tempPtr;
	tempPtr=Input_String;
	if(tempPtr[0]==',')
	{
		tempPtr++;
	}
	*Hex_Value = (int32_t)strtol((const char *)tempPtr,&returnVal,16);
	return returnVal;
}


void Get_Remote_Kinematics_Value()
{
	sprintf(PrintBuffer,"Remote,%4d,%4d,%4d,%4d\r\n",GET_R_THROTTLE(),GET_R_YAW(),GET_R_ROLL(),GET_R_PITCH());
	Write_CDC_String(PrintBuffer);
}

void Get_Remote_Mode()
{
	sprintf(PrintBuffer,"RSTATE,%d\r\n",Global_Flight_Mode);
	Write_CDC_String(PrintBuffer);
}

void Get_Drone_Mode()
{
	sprintf(PrintBuffer,"DSTATE,%d\r\n",External_Flight_State);
	Write_CDC_String(PrintBuffer);
}

void Get_Incoming_RF_Packet_Rate()
{
	sprintf(PrintBuffer,"PR,%d\r\n",Get_Packet_Rate());
	Write_CDC_String(PrintBuffer);
}

void Print_CPU()
{
	sprintf(PrintBuffer,"CPU,%d\r\n",CPU_USAGE);
	Write_CDC_String(PrintBuffer);
}


void Set_Min_Max_Cal(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	POT_Min_Max_Cal = Value ? true:false;
	if(POT_Min_Max_Cal)
	{
		Init_Joystick_Values(0);
	}
}


void Get_Motor_Speeds()
{
	sprintf(PrintBuffer,"MTR,%d,%d,%d,%d\r\n",MotorSpeeds[0],MotorSpeeds[1],MotorSpeeds[2],MotorSpeeds[3]);
	Write_CDC_String(PrintBuffer);
}

void Set_Mid_Cal(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	POT_Mid_Cal = Value ? true:false;
	if(POT_Mid_Cal)
	{
		Init_Joystick_Values(1);
	}
}

void Enable_PID_Gain(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);

	if(Value)
	{
		TRANSMIT_PID_GAINS = 1;
	}
	else
	{
		TRANSMIT_PID_GAINS = 0;
	}
}

void Get_PID_Gain(char * Input_String)
{
	uint32_t Value = 0;
	int16_t Set_Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);

	switch(Value)
	{
		case PITCH_P:
			Set_Value = Pitch_PR;
			break;

		case PITCH_I:
			Set_Value = Pitch_IR;
			break;

		case PITCH_D:
			Set_Value = Pitch_DR;
			break;

		case ROLL_P:
			Set_Value = Roll_PR;
			break;

		case ROLL_I:
			Set_Value = Roll_IR;
			break;

		case ROLL_D:
			Set_Value = Roll_DR;
			break;

		case YAW_P:
			Set_Value = Yaw_PR;
			break;

		case YAW_I:
			Set_Value = Yaw_IR;
			break;

		case YAW_D:
			Set_Value = Yaw_DR;
			break;

		default:
			break;
	}
	sprintf(PrintBuffer,"PID,%d,%d\r\n",Value,Set_Value);
	Write_CDC_String(PrintBuffer);
}


void Set_PID_Gains(char * Input_String)
{
	int32_t Value = 0;
	int32_t Command = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Command);
	Local_String_Ptr =Get_Hex_Value_Signed(Local_String_Ptr,&Value);

	switch(Command)
	{
		case PITCH_P:
			Pitch_P = (int16_t)Value;
			break;

		case PITCH_I:
			Pitch_I = (int16_t)Value;
			break;

		case PITCH_D:
			Pitch_D = (int16_t)Value;
			break;

		case ROLL_P:
			Roll_P = (int16_t)Value;
			break;

		case ROLL_I:
			Roll_I = (int16_t)Value;
			break;

		case ROLL_D:
			Roll_D = (int16_t)Value;
			break;

		case YAW_P:
			Yaw_P = (int16_t)Value;
			break;

		case YAW_I:
			Yaw_I = (int16_t)Value;
			break;

		case YAW_D:
			Yaw_D = (int16_t)Value;
			break;

		default:
			break;
	}

}


void Who_Am_I_Message()
{
	Write_CDC_String("MarqRemote\r\n");
	USB_RDY = true;
}

//	extern float ax, ay, az, gx, gy, gz, mx, my, mz;
void Get_Acc()
{
	sprintf(PrintBuffer,"ACC,%3.3f,%3.3f,%3.3f\r\n",ax,ay,az);
	Write_CDC_String(PrintBuffer);
}

void Get_Gyro()
{
	sprintf(PrintBuffer,"GYRO,%3.3f,%3.3f,%3.3f\r\n",gx,gy,gz);
	Write_CDC_String(PrintBuffer);
}

void Get_Mag()
{
	sprintf(PrintBuffer,"MAG,%3.3f,%3.3f,%3.3f\r\n",mx,my,mz);
	Write_CDC_String(PrintBuffer);
}

void Get_Kinematics() // Return of sensor fusion
{
	sprintf(PrintBuffer,"Y_P_R,%3.3f,%3.3f,%3.3f\r\n",yaw,pitch,roll);
	Write_CDC_String(PrintBuffer);
}

void Set_Settings()
{
	Save_Settings();
}

void Set_Flight_Mode_Command(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	Set_Flight_Mode((FLIGHT_MODES)Value);
}


void Set_Motor_Speed_Command(char * Input_String)
{
	uint32_t Value[4] = {0,0,0,0};
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value[0]);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value[1]);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value[2]);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value[3]);
	Set_Motor_Speed((uint16_t)Value[0],(uint16_t)Value[1],(uint16_t)Value[2],(uint16_t)Value[3]);
}

void Run_GUI_Command(char * Input_String, GUI_COMMANDS * GUI_Command)
{
	if((*GUI_Command)!=NULL_COMMAND)
	{
		if((*GUI_Command)==WHO_AM_I)
		{
			Who_Am_I_Message();
		}
		else if((*GUI_Command)==SET_PID_GAIN)
		{
			Set_PID_Gains(Input_String);

		}
		else if((*GUI_Command)==GET_MTR_SPEED)
		{
			Get_Motor_Speeds();
		}
		else if((*GUI_Command)==GET_PID_GAIN)
		{
			Get_PID_Gain(Input_String);
		}
		else if((*GUI_Command)==EN_PID_GAIN)
		{
			Enable_PID_Gain(Input_String);
		}
		else if((*GUI_Command)==FLIGHT_MODE)
		{
			Set_Flight_Mode_Command(Input_String);
		}
		else if((*GUI_Command)==GET_R_MODE)
		{
			Get_Remote_Mode();
		}
		else if((*GUI_Command)==GET_D_MODE)
		{
			Get_Drone_Mode();
		}
		else if((*GUI_Command)==MOTOR_SPEEDS)
		{
			Set_Motor_Speed_Command(Input_String);
		}
		else if((*GUI_Command)==GET_ACC)
		{
			Get_Acc();
		}
		else if((*GUI_Command)==GET_CPU)
		{
			Print_CPU();
		}
		else if((*GUI_Command)==SAVE_S)
		{
			Set_Settings();
		}
		else if((*GUI_Command)==GET_GYRO)
		{
			Get_Gyro();
		}
		else if((*GUI_Command)==GET_MAG)
		{
			Get_Mag();
		}
		else if((*GUI_Command)==GET_K)
		{
			Get_Kinematics();
		}
		else if((*GUI_Command)==GET_MM_CAL)
		{
			Set_Min_Max_Cal(Input_String);
		}
		else if((*GUI_Command)==GET_MID_CAL)
		{
			Set_Mid_Cal(Input_String);
		}
		else if((*GUI_Command)==GET_R)
		{
			Get_Remote_Kinematics_Value();
		}
		else if((*GUI_Command)==GET_PACKET_RATE)
		{
			Get_Incoming_RF_Packet_Rate();
		}

		//if((*GUI_Command)==SET_DI_PU)
		//{
		//	Set_Digital_Pullups(Input_String);
		//}

		Write_CDC_String((char *)CMD_Valid_Str);
	}
	else
	{
		Write_CDC_String((char *)CMD_Invalid_Str);
	}

}

void Handle_Command(char * Input_String)
{
	GUI_COMMANDS GUI_Command = NULL_COMMAND;
	char * BufferPtr;
	BufferPtr =Get_GUI_Command(Input_String,&GUI_Command);
	Run_GUI_Command(BufferPtr,&GUI_Command);
}

/*
 void Set_Status_Led(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	if(Value)
	{
		Set_Led_On(true);
	}
	else
	{
		Set_Led_On(false);
	}
}

void Set_Time_CMD(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	DS3231_setSecond(Value);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value);
	DS3231_setMinute(Value);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value);
	DS3231_setHour(Value);
}

void Get_Time_CMD()
{
	uint8_t Second = 0;
	uint8_t Minute = 0;
	uint8_t Hour = 0;
	
	DS3231_getSecond(&Second);
	DS3231_getMinute(&Minute);
	DS3231_getHour(&Hour);
	
	sprintf(CMD_String_Buffer,"%02d:%02d:%02d\r\n",Hour,Minute,Second);
	Write_CDC_String(CMD_String_Buffer);
}

void Set_Analog_Mux(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	Set_Shift_Reg((uint16_t)Value, ANALOG_SHIFT_REG);
}

void Set_Digital_Pullups(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	Set_Shift_Reg((uint16_t)Value,DIGITAL_SHIFT_REG);
}

void Get_Voltage_CMD()
{
	float Bat_Voltage = 0; 
	Bat_Voltage = (float)3.3*ADC->ADC_CDR[14]; //Core voltage/ref
	Bat_Voltage = (float)11*Bat_Voltage; // Resistor ratio 
	Bat_Voltage = Bat_Voltage/(4095);
	sprintf(CMD_String_Buffer,"%3.3f\r\n",Bat_Voltage);
	Write_CDC_String(CMD_String_Buffer);
}

void Get_Current_CMD()
{
	float Current = 0; 
	Current = (float)0.38*ADC->ADC_CDR[12]; //Core voltage/ref
	sprintf(CMD_String_Buffer,"%4.2f\r\n",Current);
	Write_CDC_String(CMD_String_Buffer);
}

void Get_Temp_CMD()
{
	float Temperature = 0;
	DS3231_getTemperature(&Temperature);
	sprintf(CMD_String_Buffer,"%3.1fC\r\n",Temperature);
	Write_CDC_String(CMD_String_Buffer);
}

uint8_t Analog_Lookup[] = {3,2,1,0,7,6,5,4};

void Get_ADC_CMD(char * Input_String)
{
	uint32_t Value = 0;
	float Voltage = 0;
	uint32_t Counts = 0;
	uint32_t Analog_Settings = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	if(Value>7)
	{
		Value = 0;
	}
	Counts=ADC_Data[Analog_Lookup[Value]];
	Voltage = 2.509*Counts;
	Voltage = Voltage/65535;
	Analog_Settings = (Analog_Shift_Value & (0x3<<(2*Value)))>>(2*Value);
	if(Analog_Settings==ANALOG_5V_SETTING)
	{
		Voltage *=2;
		sprintf(CMD_String_Buffer,"%3.3fV\r\n",Voltage);
	}
	else if(Analog_Settings==ANALOG_10V_SETTING)
	{
		Voltage *=4;
		sprintf(CMD_String_Buffer,"%3.3fV\r\n",Voltage);
	}
	else if(Analog_Settings==ANALOG_CURRENT_SETTING)
	{
		Voltage *=2;
		Voltage /=0.2495;
		sprintf(CMD_String_Buffer,"%3.3fmA\r\n",Voltage);
	}
	
	Write_CDC_String(CMD_String_Buffer);
}

void Set_LSD_CMD(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	LSD_Value =Value;
}

void Who_Am_I_Message()
{
	Write_CDC_String("Skale Controller\r\n");
}

void Handle_Digital_CMD()
{
	uint8_t Digital_Data = Get_Digital_Inputs();
	sprintf(CMD_String_Buffer,"%d\r\n",Digital_Data);
	Write_CDC_String(CMD_String_Buffer);
}

void Set_Serial_Mode(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	uint32_t IO_Handle = 0; 
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	
	
	if(Value==1)
	{
		IO_Handle = RS485_EN1;
	}
	else if(Value==2)
	{
		IO_Handle = RS485_EN2;
	}
	else if(Value==3)
	{
		IO_Handle = RS485_3_D;
	}
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Value);
	
	if(Value)
	{
		gpio_set_pin_high(IO_Handle);
	}
	else
	{
		gpio_set_pin_low(IO_Handle);
	}
}





void Send_String_CMD(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	Local_String_Ptr++;
	if(Value == 1)
	{
		COM_Write_String(COM1,Local_String_Ptr);
		COM_Write_String(COM1,"\r\n");
	}
	else if(Value == 2)
	{
		COM_Write_String(COM2,Local_String_Ptr);
		COM_Write_String(COM2,"\r\n");
	}
	else if(Value == 3)
	{
		COM_Write_String(COM3,Local_String_Ptr);
		COM_Write_String(COM3,"\r\n");
	}
}
//extern uint8_t COM1_Buffer[30];
//extern uint8_t COM2_Buffer[30];

void Get_Serial_CMD(char * Input_String)
{
	uint32_t Value = 0;
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	if(Value == 1)
	{
		Write_CDC_String(COM1_Buffer);
		Write_CDC_String("\r\n");
		memset(COM1_Buffer,0,sizeof(COM1_Buffer));
		COM1_Index = 0;
	}
	else if(Value == 2)
	{
		Write_CDC_String(COM2_Buffer);
		Write_CDC_String("\r\n");
		memset(COM2_Buffer,0,sizeof(COM2_Buffer));
		COM2_Index = 0;
	}
	else if(Value == 3)
	{
		Write_CDC_String(COM3_Buffer);
		Write_CDC_String("\r\n");
		memset(COM3_Buffer,0,sizeof(COM3_Buffer));
		COM3_Index = 0;
	}
}

void Handle_AOUT_CMD(char * Input_String)
{
	uint32_t Value = 0;
	uint32_t Mode = 0; 
	char * Local_String_Ptr;
	Local_String_Ptr =Get_Hex_Value(Input_String,&Value);
	Local_String_Ptr =Get_Hex_Value(Local_String_Ptr,&Mode);
	AOUT_Current_Mode = Mode;
	AOUT_Current_Value = Value;
};

 */
