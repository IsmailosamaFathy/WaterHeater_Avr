/*
 * Sw.h
 *
 * Created: 10/18/2020 2:58:34 AM
 *  Author: hp
 */ 


#ifndef SW_H_
#define SW_H_
#include "data_types.h"


typedef enum
{
	SW_PLUS,
	SW_MINUS,
	SW_ON_OFF
}tSw;

typedef enum
{
SW_RELEASED,
SW_PRE_PRESSED,	
SW_PRESSED,	
SW_PRE_RELEASED	
}tSw_state;



void Sw_Init();

void Sw_Update();

tSw_state Sw_Get_State(tSw sw);


#endif /* SW_H_ */