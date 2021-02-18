/*
 * Temp_Setting.h
 *
 * Created: 1/24/2021 9:39:24 PM
 *  Author: hp
 */ 


#ifndef TEMP_SETTING_H_
#define TEMP_SETTING_H_

#include "data_types.h"

void Temp_Setting_Init();

void Temp_Setting_Update();

uint8 Temp_Setting_Get_Temp();

Bool_t Temp_Setting_Get_Status();

void Temp_Setting_Set_Temp(uint8 Saved_temp);

#endif /* TEMP_SETTING_H_ */