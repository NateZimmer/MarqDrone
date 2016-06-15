/*
 * RF.c
 *
 *  Created on: Dec 23, 2015
 *      Author: Z
 */


#include "RF.h"
#include "../Drivers/LED_PWM.h"
#include "../Drivers/External/cc2500.h"
#include "../Drivers/External/cc.h"
#include "../Drivers/External/MPU9250.h"
#include "WAIT1.h"
#include "stdbool.h"
#include "RNG1.h"
#include "Flight.h"
#include "../Drivers/ADC.h"

bool RF_Keep_Alive = false;

bool packet_recieved = false;
RF_PACKET_STATES RF_PACKET_STATE =NO_PACKET ;


void handleRFKeepAlive()
{
	if(RF_Keep_Alive==false)
	{
		FLIGHT_STATE = FLIGHT_OFF;
		RLED_STATES = LED_FADE;
		GLED_STATES= LED_OFF;
	}
	if(RF_Keep_Alive==true)
	{
		RF_Keep_Alive = false;
		GLED_STATES = LED_FADE;
		RLED_STATES = LED_OFF;

		if(FLIGHT_STATE==FLIGHT_OFF)
		{
			FLIGHT_STATE =FLIGHT_REMOTE_CONNECTED;
		}

		if(FLIGHT_STATE == FLIGHT_ARMED )
		{
			GLED_STATES = LED_FADE;
			RLED_STATES = LED_FADE;
		}
	}
}


void handleRadioCore()
{
	 CC2500_STATES CC2500_State=0;
	 CC2500_State = cc_read_status(TI_CCxxx0_MARCSTATE);

	 if(1)
	 {
		 switch(CC2500_State)
		  {
			case TXFIFIO_UNDERFLOW:
				cc_strobe(TI_CCxxx0_SIDLE);
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
				WAIT1_WaitCycles(1000);
			  break;
			case RXFIFIO_OVERFLOW:
				cc_strobe(TI_CCxxx0_SIDLE);
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
				WAIT1_WaitCycles(1000);
				cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
				WAIT1_WaitCycles(1000);
				break;

			default:
				break;
		  }
	 }
	 if(0)
	 {
			cc_strobe(TI_CCxxx0_SIDLE);
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SFTX);      // Flush RXFIFO
			WAIT1_WaitCycles(100);
			cc_strobe(TI_CCxxx0_SRX);           // Initialize CCxxxx in RX mode.
			WAIT1_WaitCycles(100);
	 }
}

uint8_t tBuff[7]={'O','K',0,0,0,0,0};


void Format_Outing_Meta_Data(uint8_t * TBuffer,uint16_t Command)
{
	uint8_t OutgoingValue = 0;
	int16_t Transmit_Value = 0;
	switch(Command)
	{
		case FLIGHT_STATE_COMMAND:
			OutgoingValue = (uint8_t)FLIGHT_STATE ;
			TBuffer[3]=OutgoingValue;
			TBuffer[4]=OutgoingValue;
			TBuffer[5]=OutgoingValue;
			TBuffer[6]=OutgoingValue;
			break;

		case PITCH_P:
			Transmit_Value = (int16_t)(100*Pitch_PID.KP);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case PITCH_I:
			Transmit_Value = (int16_t)(100*Pitch_PID.KI);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case PITCH_D:
			Transmit_Value = (int16_t)(100*Pitch_PID.KD);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case ROLL_P:
			Transmit_Value = (int16_t)(100*Roll_PID.KP);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case ROLL_I:
			Transmit_Value = (int16_t)(100*Roll_PID.KI);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case ROLL_D:
			Transmit_Value = (int16_t)(100*Roll_PID.KD);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case YAW_P:
			Transmit_Value = (int16_t)(100*Yaw_PID.KP);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case YAW_I:
			Transmit_Value = (int16_t)(100*Yaw_PID.KI);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case YAW_D:
			Transmit_Value = (int16_t)(100*Yaw_PID.KD);
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;

		case BATTERY_VOLTAGE:
			Transmit_Value = Get_ADC_Value();
			TBuffer[3]=(Transmit_Value)>>8;
			TBuffer[4]=Transmit_Value & 0xFF;
			TBuffer[5]=(Transmit_Value)>>8;
			TBuffer[6]=Transmit_Value & 0xFF;
			break;


	}
}



void formatFloat(uint8_t * myPacket, uint8_t index)
{
	uint8_t * t_ptr;
	float testValue = 0.0;
	testValue = *IMU_Data[index];
	t_ptr = (uint8_t *)(&testValue);
	myPacket[2]=index;
	myPacket[3]=t_ptr[0];
	myPacket[4]=t_ptr[1];
	myPacket[5]=t_ptr[2];
	myPacket[6]=t_ptr[3];

}

void formatFloatF(uint8_t * myPacket, uint8_t index, float * myFloat)
{
	uint8_t * t_ptr;
	float testValue = *myFloat;
	t_ptr = (uint8_t *)(&testValue);
	myPacket[2]=index;
	myPacket[3]=t_ptr[0];
	myPacket[4]=t_ptr[1];
	myPacket[5]=t_ptr[2];
	myPacket[6]=t_ptr[3];
}



#define TRANSMIT_MOTOR_SPEEDS 1 // Choose between mag and motor speed transmits

void formatMotorSpeed(uint8_t * myPacket, uint8_t index)
{
	uint16_t Motor_Speed_Int = 0;
	uint16_t Motor_Speed_Int2 = 0;
	if(index==mxE) // Use mag spot, replace with motor speeds for speed of transmit
	{
		index = IMU_VALUES + MOTOR_SPEED_01;
		Motor_Speed_Int = (uint16_t)motor_speeds[0];
		Motor_Speed_Int2 = (uint16_t)motor_speeds[1];
	}
	else if(index ==myE)
	{
		index = IMU_VALUES + MOTOR_SPEED_23;
		Motor_Speed_Int = (uint16_t)motor_speeds[2];
		Motor_Speed_Int2 = (uint16_t)motor_speeds[3];
	}
	myPacket[2]=index;
	myPacket[3]= (Motor_Speed_Int & 0xFF00)>>8;
	myPacket[4]= (Motor_Speed_Int & 0xFF);
	myPacket[5]= (Motor_Speed_Int2 & 0xFF00)>>8;
	myPacket[6]= (Motor_Speed_Int2 & 0xFF);

}



void TX_IMU_Data()
{
	static int i = 0;
	static int meta_counter = 0;
	uint8_t * t_ptr;
	uint32_t metaDataValue = 0;
	float Transmit_Value = 0;

	tBuff[0] = SYNC_BYTE1;
	tBuff[1] = SYNC_BYTE2;

	if(i<12) // IF IMU Data
	{
		if(((i==mxE)||(i==myE))&&(TRANSMIT_MOTOR_SPEEDS))
		{
			formatMotorSpeed(tBuff,i);
		}
		else if(i==yawE)
		{
			//Transmit_Value = -1.0*yaw + Initial_Yaw;
			//Transmit_Value = Get_Angle(Transmit_Value);
			Transmit_Value = yaw;
			formatFloatF(tBuff, i, &Transmit_Value);
		}
		else
		{
			formatFloat(tBuff,i);
		}


	}
	else // Else less critical meta data
	{
		tBuff[2]=i+meta_counter;
		Format_Outing_Meta_Data(tBuff,meta_counter);
		meta_counter = (meta_counter + 1)%META_COMMANDS; // Cycle through meta data
	}

	if((GDO0_PxIN & GDO0_PIN)==0)
	{
		cc2500_tx(tBuff, 7);
		i = (i+1)%RF_WORDS;
	}
}

uint8_t Packet_Info[4]={0,0,0,0};

void Handle_Manual_Motor_State(uint8_t * Packets)
{
	manual_motor_speeds[0]=Packets[0]*10;
	manual_motor_speeds[1]=Packets[1]*10;
	manual_motor_speeds[2]=Packets[2]*10;
	manual_motor_speeds[3]=Packets[3]*10;
}



typedef enum
{
	NO_CONNECTION=0,
	REMOTE_MOTOR_MANUAL_MODE=1,
	REMOTE_ARM_DRONE=2,
	REMOTE_DRONE_ARMED=3,
	RF_LINK_CONNECTED=4,
	MOTOR_SHUT_OFF=5,
}REMOTE_MODES;



/*
 * Changes flight mode of drone. Changes from armed stage to motor manual stage to motor shutoff...ect
 */

void Handle_Flight_State_Change(char * Packet_Data)
{
	if(Packet_Data[0]==REMOTE_ARM_DRONE)
	{
		FLIGHT_STATE = FLIGHT_ARMED;
		Initial_Yaw = Aux_Yaw; // Set yaw target to present yaw observed when drone is armed.
		yaw = 0; // Jump yaw to 0;
	}
	else if(Packet_Data[0]==REMOTE_MOTOR_MANUAL_MODE)
	{
		FLIGHT_STATE = MOTOR_MANUAL_MODE;
	}
	else if(Packet_Data[0]==MOTOR_SHUT_OFF)
	{
		FLIGHT_STATE = FLIGHT_REMOTE_CONNECTED;
	}
	else if(Packet_Data[0]==RF_LINK_CONNECTED)
	{
		FLIGHT_STATE = FLIGHT_REMOTE_CONNECTED;
	}
}

void Handle_Flight_YRPT_Control_Data(char * Packet_Data)
{
	remoteThrottle = Packet_Data[0];
	remoteRoll = ((float)(-1*(int8_t)Packet_Data[1]))/10.0; // divide by 10 for more percision
	remotePitch = ((float)(-1*(int8_t)Packet_Data[2]))/10.0;
	remoteYaw = ((float)((int8_t)Packet_Data[3]))/10.0;
}


/*
 * Handle_PID_Gain_Data(char * Packet_Data)
 * Updates the Gains of the onboard control PID Settings
 *
 */

// 'O' 'K' 'index' 'command'

uint8_t Handle_PID_Gain_Data(uint8_t * Packet_Data)
{
	uint8_t Command = Packet_Data[0];
	PID_STRUCT * Target_PID;
	int16_t  Value=0;
	uint8_t Return_Value = 1;
	float Update_Value = 0;

	Value = (Packet_Data[1]<<8) + Packet_Data[2]; // Truncate packet values by 100 for fixed point precision
	Update_Value = Value / 100.0;


	switch(Command)
	{
		case PITCH_P:
			Pitch_PID.KP = (float)Update_Value;
			break;
		case PITCH_I:
			Pitch_PID.KI = (float)Update_Value;
			break;
		case PITCH_D:
			Pitch_PID.KD = (float)Update_Value;
			break;

		case ROLL_P:
			Roll_PID.KP = (float)Update_Value;
			break;
		case ROLL_I:
			Roll_PID.KI = (float)Update_Value;
			break;
		case ROLL_D:
			Roll_PID.KD = (float)Update_Value;
			break;

		case YAW_P:
			Yaw_PID.KP = (float)Update_Value;
			break;
		case YAW_I:
			Yaw_PID.KI = (float)Update_Value;
			break;
		case YAW_D:
			Yaw_PID.KD = (float)Update_Value;
			break;

		default:
			break;
	}

	return Return_Value;
}



uint8_t Parse_RF_Packet(OUTGOING_COMMANDS COMMNAD_RECIEVED, uint8_t * Packet_Data)
{
	switch(COMMNAD_RECIEVED)
	{
	case REQUEST_FLIGHT_STATE_CHANGE:
		Handle_Flight_State_Change(Packet_Data);
		break;
	case SEND_MANUAL_MOTOR_DATA:
		Handle_Manual_Motor_State(Packet_Data);
		break;
	case SEND_YAW_ROLL_PITCH_THROTTLE_DATA:
		Handle_Flight_YRPT_Control_Data(Packet_Data);
		break;
	case SEND_PID_GAINS:
		 Handle_PID_Gain_Data(Packet_Data);
		break;
	default:
		break;

	}
}

bool Packet_State(uint8_t Recieved_Byte)
{
	static uint8_t Float_Index = 0;
	static OUTGOING_COMMANDS Index = NULL_CMD;
	static float IMU_Value = 0.0;
	uint8_t * ptr;
	switch(RF_PACKET_STATE)
	{
		case NO_PACKET:
			if(Recieved_Byte==SYNC_BYTE1)
			{
				RF_PACKET_STATE = P_SYNC1;
			}
		break;

		case P_SYNC1:
			if(Recieved_Byte==SYNC_BYTE2)
			{
				RF_PACKET_STATE = P_SYNC2;
			}
			else
			{
				RF_PACKET_STATE = NO_PACKET;
			}
		break;

		case P_SYNC2:
			if(Recieved_Byte<10)
			{
				Index = Recieved_Byte;
				RF_PACKET_STATE = P_INDEX;
				Float_Index = 0;
			}
			else
			{
				RF_PACKET_STATE = NO_PACKET;
			}
		break;

		case P_INDEX:
			ptr = Packet_Info;
			ptr[Float_Index] = Recieved_Byte;
			Float_Index++;
			if(Float_Index>3)
			{
				Parse_RF_Packet(Index, Packet_Info);
				RF_PACKET_STATE = NO_PACKET;
				RF_Keep_Alive = true;
				Float_Index = 0;
				TX_IMU_Data(); // Send back a TX every time we get a valid packet. This helps avoid collisions
			}

		break;
	}
}

void Fill_Ring_Buffer(uint8_t size,uint8_t * Buffer)
{
	for(int i = 0; i < size; i++)
	{
		RNG1_Put(Buffer[i]);
	}
}

#define TEMP_BUFF_SIZE 60
uint8_t rBuff[TEMP_BUFF_SIZE];
#define CC2500_BUFFER_OVERFLOW (0x1<<7)

void Handle_Incoming_Packets()
{
  volatile uint8_t ReadStatusValue = 0;
  volatile uint8_t ReadStatusValue1 =0;
  volatile uint8_t wtf = 0;
	//Handle_USB_Read();

	static uint8_t prevBuf = 0;
	uint8_t buffer_byte = 0;

	if(packet_recieved) // ISR has set the PR flag which means the GDO sensed a packet has been recieved
	{
		if((GDO0_PIN & GDO0_PxIN)==0) // Aka no new packets
		{
			ReadStatusValue1 = cc_read_status( TI_CCxxx0_RXBYTES );
			ReadStatusValue = cc_read_status( TI_CCxxx0_RXBYTES );

			if(ReadStatusValue1==0)
			{
				wtf++; // This would indicate a CRC failure assuming auto flush worked
			}
			else if(ReadStatusValue1 & CC2500_BUFFER_OVERFLOW)
			{
				wtf++;
				if(wtf>20)
				{
					wtf=0;

				}
				Quick_Reset_Core();
				//Toggle_Pin(&BLUE_LED);
			}
			else if(ReadStatusValue1<TEMP_BUFF_SIZE)
			{
				receive_packet_fixed_length( rBuff, ReadStatusValue1,false);
				Fill_Ring_Buffer(ReadStatusValue1,rBuff);

			}
			else
			{
				receive_packet_fixed_length( rBuff, TEMP_BUFF_SIZE,false);
				Fill_Ring_Buffer(TEMP_BUFF_SIZE,rBuff);
			}
			while(RNG1_NofElements())
			{
				RNG1_Get(&buffer_byte);
				Packet_State(buffer_byte); // IMPORTANT, this is the packet parser
			}
			 ReadStatusValue1 = cc_read_status( TI_CCxxx0_RXBYTES );
			 packet_recieved = false;
			 //debug_console(sendBuff);
		}
	}
	//Toggle_Pin(&BLUE_LED); //IDLE TASK LED
	// Chip reccomends a interrupt driven solution, repeatidly polling as above is non ideal. Will try avoiding this route.
}



float * IMU_Data[12] = {
		&ax, //0
		&ay, //1
		&az, //2
		&gx, //3
		&gy, //4
		&gz, //5
		&mx, //6
		&my, //7
		&mz, //8
		&yaw, //9
		&roll, //10
		&pitch //11
};

RF_TRANSMIT_DATA_TYPE RF_TRANSMIT_DATA;

void InitRFData()
{
	RF_TRANSMIT_DATA.IMU_DATAS[0] = &ax;
	RF_TRANSMIT_DATA.IMU_DATAS[1] = &ay;
	RF_TRANSMIT_DATA.IMU_DATAS[2] = &az;
	RF_TRANSMIT_DATA.IMU_DATAS[3] = &gx;
	RF_TRANSMIT_DATA.IMU_DATAS[4] = &gy;
	RF_TRANSMIT_DATA.IMU_DATAS[5] = &gz;
	RF_TRANSMIT_DATA.IMU_DATAS[6] = &mx;
	RF_TRANSMIT_DATA.IMU_DATAS[7] = &my;
	RF_TRANSMIT_DATA.IMU_DATAS[8] = &mz;
	RF_TRANSMIT_DATA.IMU_DATAS[9] = &yaw;
	RF_TRANSMIT_DATA.IMU_DATAS[10] =&roll;
	RF_TRANSMIT_DATA.IMU_DATAS[11] =&pitch;
}




