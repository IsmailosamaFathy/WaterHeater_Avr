/*
 * External_EEPROM.h
 *
 * Created: 1/5/2021 5:00:11 AM
 *  Author: hp
 */ 


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_
#include "data_types.h"
typedef enum
{
ERROR=0,
SUCCESS	
}t_EX_EEprom_state;

void External_EEPROM_Init();

t_EX_EEprom_state External_EEPROM_Write(uint8 data,uint16 add);

t_EX_EEprom_state External_EEPROM_Read(uint16 add,uint8 *pdata);




#endif /* EXTERNAL_EEPROM_H_ */