/*
 * Led.c
 *
 * Created: 2/4/2021 12:29:48 AM
 *  Author: hp
 */ 
#include "Led.h"
#include "DIO_Interface.h"
#include "Elements.h"
#include "Timers.h"
#include "Port_h.h"
#define LED_PERIOD  (1000)


void LED_Init()
{
	Pin_Init(LED_PIN,OUTPUT);
	Set_Pin(LED_PIN,LOW);
}

void LED_Update()
{
	static uint16 Led_Counter=0;
	t_ELEMENT_STATE Led_flag;
	Led_Counter+=OS_TICK;
	if (Led_Counter!=LED_PERIOD)
	{
		return;
	}
	Led_Counter=0;
	Led_flag=Get_Element_State();
	switch(Led_flag)
	{
		case HEATING_STATE:
		Toggle_Pin(LED_PIN);
		break;
		
		case COOLING_STATE:
		Set_Pin(LED_PIN,HIGH);
		break;
	}
}