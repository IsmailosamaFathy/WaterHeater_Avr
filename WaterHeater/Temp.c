/*
 * Temp.c
 *
 * Created: 1/29/2021 9:16:25 PM
 *  Author: hp
 */ 
#include "ADC.h"
#include "Temp.h"
#include "Timers.h"
#include "Port_h.h"
#define TEMPERATURE_MEASURE_PERIOD         (100)
#define MAX_READINGS                        (10)
#include <util/delay.h>
static uint8 AVG_Temp;

void Temperature_Init()
{
	ADC_Init(AVCC,CLK_ADC_DIV_64);
    _delay_ms(500);	
	ADC_Converstion(Conversion_on);
}

void Temperature_Update()
{
	// This task executed every (100ms)
	static uint8 Temperature_Counter=1;
	static uint8 Measuring_Counter=0;
	static uint16 temp=0;
	
	uint16 temp1=0;
	Temperature_Counter+=OS_TICK; 
	if (Temperature_Counter!=TEMPERATURE_MEASURE_PERIOD)
	{
		
		return;
	}
	Temperature_Counter=1;
	if (Measuring_Counter<MAX_READINGS)
	{
			//ADC_ASY_Read
			temp1=Get_ADC_NO_BLOCK(LM35_Channel);
			
			temp1=((uint32)temp1*5000)/1024;
			
			temp1=temp1/10;
			temp+=temp1;
			Measuring_Counter++;
	}
	else
	{
		
		
		AVG_Temp=(uint16)(temp/10);
		//Reset_Everything
		Measuring_Counter=0;
		temp=0;
	}
	
	
	
	
	
	
    ADC_Converstion(Conversion_on);
	
	
	
	
}
uint8 Get_Temperature()
{
	return AVG_Temp;
}