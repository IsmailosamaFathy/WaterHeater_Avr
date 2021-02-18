/*
 * Display.c
 *
 * Created: 1/24/2021 11:15:26 PM
 *  Author: hp
 */ 

#include "Timers.h"
#include "SSD.h"
#include "Display.h"
#include "Temp_Setting.h"
#include "DIO_Interface.h"
#include "Temp.h"
#define DISP_PERIOD                 (20)
static Bool_t Blink_Flag=FALSE;
Bool_t Get_state()
{
	return Blink_Flag;
}
void Display_Init()
{

 SSD_Init(SSD_R);
 SSD_Init(SSD_M);
SSD_Set_symbol(SSD_R,SSD_NULL);
SSD_Set_symbol(SSD_M,SSD_NULL);
Pin_Init(PIND4,LOW);

}

void Display_Update()
{
	//Chang every start from 0 to 1 in counters
	static uint8 Disp_Counter=0;
    
	uint8 temp=0;
	
	static uint16 Time=0;
	
	Bool_t flag=FALSE;
	

     Disp_Counter+=OS_TICK;
	
	if (Disp_Counter!=DISP_PERIOD)
	{
		return;
	}
	
	
	Disp_Counter=0;
	
	flag=Temp_Setting_Get_Status();
	


	if (flag==TRUE)
	{
		temp=Temp_Setting_Get_Temp();
		
		SSD_Set_symbol(SSD_R,temp%10);
		
		SSD_Set_symbol(SSD_M,temp/10);
		
		Time+=DISP_PERIOD;
		
		if (Time%1000==0) //To blink every 1 Sec
		{
			//Bug is here
			Toggle_Pin(PIND4);
			//Not complete
		    switch(Blink_Flag)
			{
				case (TRUE):
				
				Blink_Flag=FALSE;
				
				SSD_Set_State(SSD_R,SSD_OFF);
				
				SSD_Set_State(SSD_M,SSD_OFF);
				
				break;
				
				case (FALSE):
				
				Blink_Flag=TRUE;
									
				//	SSD_update(); // here timing characteristics  is not correct as every 5 dis counter gives 1 SSD_Counter tick
				// So we will make variable (Blink_Flag) with get function & check for On in while loop
					
					
				break;
				
				default:
				
				break;
	
			}
			
		}
		else
		{
		SSD_Set_State(SSD_R,SSD_OFF);
		SSD_Set_State(SSD_M,SSD_OFF);
		}
					
	
	}
	else
	{
		temp=Get_Temperature();
		
		SSD_Set_symbol(SSD_R,temp%10);
				
		SSD_Set_symbol(SSD_M,temp/10);
			
		Time=0;
		
	
	}
	




}