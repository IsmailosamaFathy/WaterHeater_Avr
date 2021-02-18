/*
 * ADC.h
 *
 * Created: 10/5/2020 8:01:39 PM
 *  Author: hp
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Mem_map.h"
#include "data_types.h"
#include "Ports_comman_ins.h"

typedef enum
{
	Interrupt_OFF,
	Interrupt_On,
}Interrupt_Status;




typedef enum
{
	Conversion_off=0,
	Conversion_on
}Conversion__Status;

typedef enum
{
	Vref_Turn_Off=0,
	AVCC=1,
	Internal_Vref=3,
}Vref_type;



typedef enum
{
	ChanneL0=0,
	ChanneL1,
	ChanneL2,
	ChanneL3,
	ChanneL4,
	ChanneL5,
	ChanneL6,
	ChanneL7,
}ChanneL_Select;


typedef enum
{
	FREE_RUNNING_MODE = 0,
	ANALOG_COMPARTOR = 1,
	EXTERNAL_INITERRUPT0 = 2,
	COMPARE_MATCH_TIMER0 = 3,
	OVERFLOW_TIMER0 = 4,
	COMPARE_MATCH_TIMER1=5,
	OVERFLOW_TIMER1=6,
} Mode_SelectType;


typedef enum
{
	CLK_ADC_DIV_2=1,
	CLK_ADC_DIV_4 = 2,
	CLK_ADC_DIV_8 = 3,
	CLK_ADC_DIV_16 = 4,
	CLK_ADC_DIV_32 = 5,
	CLK_ADC_DIV_64 = 6,
	CLK_ADC_DIV_128 = 7,
} Clk_SelectType;




void ADC_Init(Vref_type vref,Clk_SelectType clk);

void ADC_Converstion(Conversion__Status state);

uint16 ADC_Read(ChanneL_Select channel);


Bool_t ADC_ASY_Read(ChanneL_Select channel,uint16 *ptr);


uint16 Get_ADC_NO_BLOCK(ChanneL_Select channel);



#endif /* ADC_H_ */