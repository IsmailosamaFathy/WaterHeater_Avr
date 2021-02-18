/*
 * Elements.h
 *
 * Created: 2/4/2021 12:18:06 AM
 *  Author: hp
 */ 


#ifndef ELEMENTS_H_
#define ELEMENTS_H_
typedef enum
{
	COOLING_STATE=0,
	HEATING_STATE
}t_ELEMENT_STATE;


void Elements_Init();

void Element_Update();

t_ELEMENT_STATE Get_Element_State();


#endif /* ELEMENTS_H_ */