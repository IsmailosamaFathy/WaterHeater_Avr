/*
 * Temp_Setting.c
 *
 * Created: 1/24/2021 9:39:41 PM
 *  Author: hp
 */ 
#include "Timers.h"
#include "Sw.h"
#include "Temp_Setting.h"
#include "External_EEPROM.h"

static uint8 User_Temp;

static Bool_t Temp_Setting_Flag=FALSE;

#define TEMP_SETTING_PERIOD_MS     (20)

#define USER_TEMP_SAVING_ADDERESS   (0x01)

void Temp_Setting_Init()
{
	User_Temp=60;
}

void Temp_Setting_Update()
{
	static uint8 Temp_Setting_Counter=0;
    static uint16 Temp_Mode_Counter=0;

	Temp_Setting_Counter+=OS_TICK;
	
	if (Temp_Setting_Counter!=TEMP_SETTING_PERIOD_MS)
	{
		
		return;
	}
	Temp_Setting_Counter=0;
	
	if (Sw_Get_State(SW_PLUS)==SW_PRE_PRESSED)
	{
		if (User_Temp<75)
		{
			User_Temp+=5;
			External_EEPROM_Write(User_Temp,USER_TEMP_SAVING_ADDERESS);		
		}
		Temp_Setting_Flag=TRUE;
		
		Temp_Mode_Counter=0;
		
		
		
	}
	else if (Sw_Get_State(SW_MINUS)==SW_PRE_PRESSED)
	{
		if (User_Temp>30)
		{
			User_Temp-=5;
			External_EEPROM_Write(User_Temp,USER_TEMP_SAVING_ADDERESS);	
		}
		Temp_Setting_Flag=TRUE;
		
		Temp_Mode_Counter=0;
		
	}
	else
	{
		//Do nothing
	
	}
	if (Temp_Setting_Flag==TRUE)
	{
		Temp_Mode_Counter+=TEMP_SETTING_PERIOD_MS;
	}
	// Why can we just use 4999 ?????????????????
	
	if (Temp_Mode_Counter>4999)
	{
		Temp_Setting_Flag=FALSE;
		
		Temp_Mode_Counter=0;

		
	}
	

	
}
uint8 Temp_Setting_Get_Temp()
{
	return User_Temp;
}

Bool_t Temp_Setting_Get_Status()
{
	return Temp_Setting_Flag;
}
void Temp_Setting_Set_Temp(uint8 Saved_temp)
{
	User_Temp=Saved_temp;
	
}