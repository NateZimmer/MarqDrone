/*
 * LED_PWM.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Z
 */

#include "LED_PWM.h"

#include "Cpu.h"
#include "Events.h"
#include "TPM_PDD.h"
#include "PWM.h"
#include "External/cc2500.h"


uint16_t LED_CYCLE = 0;

LED_STATES GLED_STATES=LED_OFF;
LED_STATES RLED_STATES=LED_FADE;

const int led_dutys2[] = {
1005,
1005,
1005,
1005,
1004,
1004,
1004,
1004,
1004,
1003,
1003,
1002,
1001,
1000,
999	,
998	,
997	,
995	,
994	,
992	,
990	,
988	,
985	,
983	,
980	,
977	,
973	,
970	,
966	,
961	,
957	,
952	,
947	,
942	,
936	,
930	,
924	,
917	,
910	,
902	,
894	,
886	,
877	,
868	,
859	,
849	,
839	,
828	,
816	,
805	,
805	,
816	,
828	,
839	,
849	,
859	,
868	,
877	,
886	,
894	,
902	,
910	,
917	,
924	,
930	,
936	,
942	,
947	,
952	,
957	,
961	,
966	,
970	,
973	,
977	,
980	,
983	,
985	,
988	,
990	,
992	,
994	,
995	,
997	,
998	,
999	,
1000,
1001,
1002,
1003,
1003,
1004,
1004,
1004,
1004,
1004,
1005,
1005,
1005,
1005,
};

void GLED_Sequence()
{
	uint16_t Value = 0;
	if(GLED_STATES==LED_FADE)
	{
		Value = led_dutys2[LED_CYCLE]; //change TA0.1 duty cycle
		Set_PWM_Reg(CH0,Value);
	}
	else if(GLED_STATES==LED_ON)
	{
		Set_PWM_Reg(CH0,0);
	}
	else if(GLED_STATES==LED_OFF)
	{
		Set_PWM_Reg(CH0,1007);
	}
}

void RLED_Sequence()
{
	uint16_t Value = 0;
	if(RLED_STATES==LED_FADE)
	{
		Value = led_dutys2[LED_CYCLE]; //change TA0.1 duty cycle
		Set_PWM_Reg(CH1,Value);
	}
	else if(RLED_STATES==LED_ON)
	{
		Set_PWM_Reg(CH1,0);
	}
	else if(RLED_STATES==LED_OFF)
	{
		Set_PWM_Reg(CH1,1007);
	}
}

void Handle_Fade()
{
	LED_CYCLE++;
	if(LED_CYCLE>99)
		LED_CYCLE=0;
}

////////////////////////////////////////////
//Handle_LEDs and put this in a scheduler,
//speed at which it is called determines the
//animation speed
////////////////////////////////////////////

void Handle_LEDs()
{
	RLED_Sequence();
	GLED_Sequence();
	Handle_Fade();

}

////////////////////////////////////////////

void handleRFKeepAlive()
{
	if(RF_Keep_Alive==false)
	{

	}
	if(RF_Keep_Alive==true)
	{

		RF_Keep_Alive = false;
	}
}

