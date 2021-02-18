/*
* I2C.h
*
* Created: 3/12/2014 12:05:49 PM
*  Author: Ebrahin hamouda
*/


#ifndef I2C_H_
#define I2C_H_



/* STATUS VALUES */
typedef void(*Call_backTX_t)(void);
typedef	void(*Call_backRecive_t)(unsigned char);

typedef enum
{
	//Master Transmitter MODE
	START_TRANSMITTED=0x08,
	RPEATED_START_TRANMITTED=0x10,
	SLA_W_ACK_REC=0x18,
	SLA_W_NO_ACK_REC=0x20,
	DATA_TRANSMITTED_ACK_REC=0x28,
	DATA_TRANSMITTED_No_ACK_REC=0x30,
	MASTER_ARBITRATION=0x38,
	//Master Receiver MODE
	SLA_R_ACK_REC=0x40,
	SLA_R_NO_ACK_REC=0x48,
	DATA_SENT_ACK_REC=0x50,
	DATA_SENT_NO_ACK_REC=0x58,
	//SLAVE Receiver Mode
	OWN_SLA_W_ACK_REC=0x60,
	ARBIT_LOST_ACK_RET_SLV_REC_MOD=0x68,
	GENERAL_CALL_ADDRESS_ACK_REC=0x70,
	STOP_REC_WHILE_ADDRESSED_AS_SLAVE=0xA0,
	//Slave_Trans_Mode
	DATA_BYTE_TRANSMITTED_ACK_REC=0xB8,
	DATA_BYTE_TANS_NO_ACK_REC=0xC0,
	LAST_DATA_BYTE_TRANSMITTED_ACK_REC=0xC8
}t_I2C_State;

typedef enum
{
	I2C_RX,
	I2C_TX
} I2c_Status_t;


void I2C_Init(I2c_Status_t i2c_passStatus);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);
void I2C_TxWithInterrupt(unsigned char data);
unsigned char I2C_ReadWithACK(void); //read with send Ack
unsigned char I2C_ReadWithACKAndInterrupt(void);//read with send Ack && interrupt enable
void I2C_AssignCallBackRX(Call_backRecive_t pass_callBack);
unsigned char I2C_ReadWithNACK(void); //read without send Ack
t_I2C_State I2C_GetStatus(void);
void I2C_AssignCallBackTx(Call_backTX_t pass_callBackFuncation);
void i2c_disable_interrupt();
#endif /* I2C_H_ */