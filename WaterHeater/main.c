/*
 * WaterHeater.c
 *
 * Created: 1/24/2021 9:23:27 PM
 * Author : hp
 */ 
#include "Main.h"

volatile Bool_t Status_flag=FALSE;


void System_Init();

static void T1_my_func()
{
	
		Status_flag=TRUE;
}
void System_Init()
{
	t_EX_EEprom_state Eeprom_flag;
	
	uint8 Init_flag;
	uint8 temp=0;
	//System
	Elements_Init();
	
	Sw_Init();
	
	Display_Init();
	
	Temp_Setting_Init();
	
	LED_Init();
	
	//Ex_EEprom
	External_EEPROM_Init();
	
	Eeprom_flag=External_EEPROM_Read(INIT_FLAG_ADDERESS,&Init_flag);
	if (Init_flag!=USER_DEFAULT)
	{
		// Mark as Used now!

		Eeprom_flag=External_EEPROM_Write(USER_DEFAULT,INIT_FLAG_ADDERESS);
		//delay 10ms
		_delay_ms(10);
		if (Eeprom_flag==SUCCESS)
		{
			Eeprom_flag=External_EEPROM_Write(Temp_Setting_Get_Temp(),USER_TEMP_SAVING_ADDERESS);
		}
		_delay_ms(10);
		
	}
	else
	{
		//Modify user_temp variable
		Eeprom_flag=External_EEPROM_Read(USER_TEMP_SAVING_ADDERESS,&temp);
		if (Eeprom_flag==SUCCESS)
		{
			
			
			if ((temp<75)&&(temp>30))
			{
				Temp_Setting_Set_Temp(temp);
			}
			
		}
	}
	
	Temperature_Init();
	//Scheduler
	
	Timer1_CTC_OC1RA_Set_Call_Back(T1_my_func);
	
	Timer1_OCR1A=999;
	
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_PRESCALING_CLK8,OC1RA_DISCONNECTED,OC1RB_DISCONNECTED);
	
	Timer1_CTC_OCR1A_Interrupt_State(TIMER1_CTC_OC1RA_INT_ENABLE);
	
	GLOBAL_INTERUPT_ENABLE;
	
}
int main(void)
{
	Bool_t flag;
	
	System_Init();	
	
    while (1) 
    {
		if (Status_flag==TRUE)
		{
			flag=Get_state();
			
			if (flag==FALSE)
			{
				SSD_Update();
			}
						
			Display_Update();
			
			Sw_Update();
			
			Temp_Setting_Update();
			
			Temperature_Update();	
			
			Element_Update();
			
			LED_Update();
			
			Status_flag=FALSE;
		}
    }
}

