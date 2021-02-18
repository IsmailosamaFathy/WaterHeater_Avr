/*
 * SSD.c
 *
 * Created: 10/19/2020 5:42:41 PM
 *  Author: hp
 */ 
#include "SSD.h"

#include "DIO_Interface.h"

#include "Port_h.h"

#include "Timers.h"


#define SSD_PERIOD   (5)

// SSD BUFFER

tSSD_Symbol SSD_Buffer[NUMBER_OF_SSD]={SSD_NULL};

// Buffer Index
static tSSD Current_SSD=SSD_R;


#if (SSD_TYPE==SSD_COMMON_CATH)
                  
		//                0      1   2    3    4    5   6    7    8   9    null
 static uint8 SSD_Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
	 
#define  SSD_SET_DIRC   0xff

#define SSD_PORT_Init   0x00


#else
uint8 SSD_Data[]={
	0xc0, //0
	0xf9, //1
	0xa4, //2
	0xb0, //3
	0x99, //4
	0x92, //5
	0x82, //6
	0xf8, //7
	0x80, //8
	0x90, //9
	0xff, //null
};
#define  SSD_SET_DIRC   0x00

#define SSD_PORT_Init   0xff

#endif



static void SSD_Out(tSSD ssd,tSSD_Symbol symbl);

void SSD_Init(tSSD ssd)
{

  
  switch(ssd)
  {
	  	case (SSD_R):
		  Pin_Init(SSDR,OUTPUT);
		  break;
	  	case (SSD_M):
		  Pin_Init(SSDM,OUTPUT);
		  break;
	  	case (SSD_N):
		  Pin_Init(SSDN,OUTPUT);
		  break;
	  	case (SSD_L):
		  Pin_Init(SSDL,OUTPUT);
		  break;
  }	
  
SSD_Out(ssd,SSD_NULL);
}

void SSD_Update()
{
	static  uint16 SSD_Counter=1;
	SSD_Counter+=OS_TICK;
	
	if (SSD_Counter!=SSD_PERIOD)
	{
		return;
	}
	
	SSD_Counter=1;
    
	SSD_Out(Current_SSD,SSD_Buffer[Current_SSD]);
	
	if (Current_SSD==(NUMBER_OF_SSD-1))
	{
		Current_SSD=SSD_R;
	}
	else
	{
		Current_SSD++;
	}
	 


}


void SSD_Set_symbol(tSSD ssd, tSSD_Symbol symbl)
{
	
	SSD_Buffer[ssd]=symbl;
}

void SSD_Set_State(tSSD ssd, tSSD_STATE state)
{
	switch(ssd)
	{
		case SSD_R:
		Set_Pin(SSDR,state);
		break;
		
		case SSD_M:
		Set_Pin(SSDM,state);
		break;

		case SSD_N:
		Set_Pin(SSDN,state);
		break;
		
		case SSD_L:
		Set_Pin(SSDL,state);
		break;
		
	}
	
	
}
static void SSD_Out(tSSD ssd,tSSD_Symbol symbl)
{
	
	SSD_Set_State(SSD_R,SSD_OFF);
	
	SSD_Set_State(SSD_M,SSD_OFF);
	
	//Not Used 
	//SSD_Set_State(SSD_N,SSD_OFF);
	
	//SSD_Set_State(SSD_L,SSD_OFF);
	
	Set_Port(SSD_PORT,SSD_Data[symbl]);
	
	SSD_Set_State(ssd,SSD_ON);
	
}
