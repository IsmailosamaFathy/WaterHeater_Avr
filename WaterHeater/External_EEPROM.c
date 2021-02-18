/*
 * External_EEPROM.c
 *
 * Created: 1/5/2021 5:00:22 AM
 *  Author: hp
 */ 
#include "I2C.h"
#include "External_EEPROM.h"
#include "data_types.h"
void External_EEPROM_Init()
{
  I2C_Init(I2C_TX);
}

t_EX_EEprom_state External_EEPROM_Write(uint8 data,uint16 add)
{
	t_EX_EEprom_state ret=ERROR;
	
	t_I2C_State status;
	
	I2C_Start();
	
	status=I2C_GetStatus();
	
	if (status!=START_TRANSMITTED)
	{
		return ret;
	}
	
	I2C_Write((uint8)(0xA0|((add & 0x0700)>>7)));
	status=I2C_GetStatus();
	if (status!=SLA_W_ACK_REC)
	{
		return ret;
	}
	
	I2C_Write((uint8)add);
	status=I2C_GetStatus();
	if (status!=DATA_TRANSMITTED_ACK_REC)
	{
		return ret;
	}
	
	I2C_Write(data);
	
	status=I2C_GetStatus();
	
	if (status!=DATA_TRANSMITTED_ACK_REC)
	{
		return ret;
	}
	I2C_Stop();


   ret=SUCCESS;
   return ret;
}
t_EX_EEprom_state External_EEPROM_Read(uint16 add,uint8 *pdata)
{
	t_EX_EEprom_state ret=ERROR;
	
	t_I2C_State status;
	
	I2C_Start();
	
	status=I2C_GetStatus();
	
	if (status!=START_TRANSMITTED)
	{
		return ret;
	}
	
	I2C_Write((uint8)(0xA0|((add & 0x0700)>>7)));
	status=I2C_GetStatus();
	if (status!=SLA_W_ACK_REC)
	{
		return ret;
	}
	
	I2C_Write((uint8)add);
	status=I2C_GetStatus();
	if (status!=DATA_TRANSMITTED_ACK_REC)
	{
		return ret;
	}
	I2C_Start();
	status=I2C_GetStatus();
	if(status!=RPEATED_START_TRANMITTED)
	{
	   return ret;
	}
	I2C_Write((uint8)(0xA0|((add & 0x0700)>>7)|1));
	status=I2C_GetStatus();
	if (status!=SLA_R_ACK_REC)
	{
		return ret;
	}
	*pdata=I2C_ReadWithNACK();
	status=I2C_GetStatus();
	if (status!=DATA_SENT_NO_ACK_REC)
	{
		return ret;
	}
	
	I2C_Stop();
    ret=SUCCESS;



return ret;


}