/*
 * Elements.c
 *
 * Created: 2/4/2021 12:18:17 AM
 *  Author: hp
 */ 
#include "DIO_Interface.h"
#include "Elements.h"
#include "Temp.h"
#include "Temp_Setting.h"
#include "Timers.h"
#include "Port_h.h"
#include <stdlib.h>
#define ELEMENT_ACTION_PERIOD_MS                (1000)
#define WATER_HEATER_CHANGE_RATE                 (5)
#define MAX_TEMP_ERROR                           (15)

static t_ELEMENT_STATE Element_Flag=COOLING_STATE;

void Elements_Init()
{
	
	Pin_Init(HEATING_ELEMENT_PIN,OUTPUT);
	
	Pin_Init(COOLING_ELEMENT_PIN,OUTPUT);
	
	Set_Pin(HEATING_ELEMENT_PIN,LOW);
		
	Set_Pin(COOLING_ELEMENT_PIN,LOW);
	
	
}

void Element_Update()
{
	static uint16 Element_Counter=0;
	Element_Counter+=OS_TICK;
	uint8 User_req_Temp=0;
	uint8 Actual_Temp=0;
	static uint8 Result=0;
	if (Element_Counter!=ELEMENT_ACTION_PERIOD_MS)
	{
		return;
	}
	
	Element_Counter=0;
	Actual_Temp=Get_Temperature();
	
	User_req_Temp=Temp_Setting_Get_Temp();
	
	Result=abs(Actual_Temp-User_req_Temp);
	
	//Bug is here Fix it 
	if (Actual_Temp!=0)
	{
		//Take action
	if ((Result>=WATER_HEATER_CHANGE_RATE) && (Actual_Temp>User_req_Temp))
	{
		Set_Pin(HEATING_ELEMENT_PIN,LOW);
			
		Set_Pin(COOLING_ELEMENT_PIN,HIGH);
		
		Element_Flag=COOLING_STATE;
	}
	//Bug is here Fix it 
	else if (Result<=WATER_HEATER_CHANGE_RATE && (Result!=0) && (Actual_Temp<User_req_Temp) )
	{
		Set_Pin(HEATING_ELEMENT_PIN,HIGH);
					
		Set_Pin(COOLING_ELEMENT_PIN,LOW);
		
		Element_Flag=HEATING_STATE;
	}
	// This Check for protection 
	else if (Result>MAX_TEMP_ERROR)
	{
		Set_Pin(HEATING_ELEMENT_PIN,LOW);
		
		Set_Pin(COOLING_ELEMENT_PIN,LOW);
				// YOU should display N.O
	}
	else
	{
		//...Do_Nothiing
		
	}
	
	}
}
t_ELEMENT_STATE Get_Element_State()
{
	return Element_Flag;
}