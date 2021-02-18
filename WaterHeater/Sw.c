/*
 * Sw.c
 *
 * Created: 10/18/2020 2:58:50 AM
 *  Author: hp
 */ 

#include "Sw.h"
#include "Mem_map.h"
#include "Port_h.h"
#include "Timers.h"

#define SW_PERIOD_MS        (20)     

//#define TMR_TICK            (4) 

#define GPIO_OUT            (1)
#define GPIO_IN             (0)

/* SW voltage level */
#define SW_PRESSED_LEVEL    (0)
#define SW_RELEASED_LEVEL   (1)

#define N_SAMPLES           (2)
#define N_SWITCHES          (3)



typedef struct
{
	uint8 sw_samples[N_SAMPLES];
	tSw_state sw_state;
}tSW_Info;

/* Switches info */
static tSW_Info SWs_Info[N_SWITCHES];

void Sw_Init()
{


	
	    uint8 index = 0;
 
	    /* Add your code here! */
	    /* Initialize switches as inputs */
	 
	    SET_REGISTER_PIN(SW_PLUS_PORT_CR, SW_PLUS_PIN, GPIO_IN);
	    SET_REGISTER_PIN(SW_MINUS_PORT_CR, SW_MINUS_PIN, GPIO_IN);
	    SET_REGISTER_PIN(SW_ON_OFF_PORT_CR, SW_ON_OFF_PIN, GPIO_IN);

	    SET_REGISTER_PIN(SW_PLUS_PORT_DR, SW_PLUS_PIN, GPIO_OUT);
	    SET_REGISTER_PIN(SW_MINUS_PORT_DR, SW_MINUS_PIN, GPIO_OUT);
	    SET_REGISTER_PIN(SW_ON_OFF_PORT_DR, SW_ON_OFF_PIN, GPIO_OUT);


	    /* Initialize switches info */
	    for (index = SW_PLUS; index < N_SWITCHES; index++)
	    {
		 /* Initialize switch samples */
		    SWs_Info[index].sw_samples[0] = SW_RELEASED_LEVEL;
		    SWs_Info[index].sw_samples[1] = SW_RELEASED_LEVEL;

          /* Initialize sw state */
		    SWs_Info[index].sw_state = SW_RELEASED;
      
	    }
	
	

}

void Sw_Update()
{
	
static uint8 Sw_Counter=1;

tSw index;
Sw_Counter+=OS_TICK;

if (Sw_Counter!=SW_PERIOD_MS)
{
	
 return;	
}
Sw_Counter=1;


for (index=SW_PLUS;index<N_SWITCHES;index++)
{
	
	SWs_Info[index].sw_samples[0]=SWs_Info[index].sw_samples[1];
	/***********Update_Samples**********/
	switch(index)
	{
		case(SW_PLUS):
		SWs_Info[index].sw_samples[1]=READ_BIT(SW_PLUS_PORT_READ,SW_PLUS_PIN);
		break;
		
		case (SW_MINUS):
		SWs_Info[index].sw_samples[1]=READ_BIT(SW_MINUS_PORT_READ,SW_MINUS_PIN);
		break;
		
		case (SW_ON_OFF):
		SWs_Info[index].sw_samples[1]=READ_BIT(SW_ON_OFF_PORT_READ,SW_ON_OFF_PIN);
		break;
		
	}
	
	/************Update_States*****************/
	switch(SWs_Info[index].sw_state)
	{
		case SW_RELEASED:
		if ( (SWs_Info[index].sw_samples[0]==SW_PRESSED_LEVEL) &&
		(SWs_Info[index].sw_samples[1]==SW_PRESSED_LEVEL) )
		{
			SWs_Info[index].sw_state=SW_PRE_PRESSED;
		
		}
		else
		{
              // Do_Nothing
		}
		break;
		
		case SW_PRE_PRESSED:
		
		if ( (SWs_Info[index].sw_samples[1]==SW_PRESSED_LEVEL) )
		{
			SWs_Info[index].sw_state=SW_PRESSED;
		}
		else
		{
			// Do_Nothing
		}	
		
		
		break;
		
		case SW_PRESSED:
		
		if ( (SWs_Info[index].sw_samples[0]==SW_RELEASED_LEVEL) &&
		(SWs_Info[index].sw_samples[1]==SW_RELEASED_LEVEL) )
		{
			SWs_Info[index].sw_state=SW_PRE_RELEASED;
		}
		else
		{
			// Do_Nothing
		}		
		break;
		
		case SW_PRE_RELEASED:
		
		if ( (SWs_Info[index].sw_samples[1]==SW_RELEASED_LEVEL) )
		{
					SWs_Info[index].sw_state=SW_RELEASED;
		}
		else
		{
					// Do_Nothing
		}
		
		break;
		
	}
		
}

}

tSw_state Sw_Get_State(tSw sw)
{
   return SWs_Info[sw].sw_state;
}