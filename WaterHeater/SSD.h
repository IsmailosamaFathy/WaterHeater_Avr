/*
 * SSD.h
 *
 * Created: 10/19/2020 5:42:32 PM
 *  Author: hp
 */ 


#ifndef SSD_H_
#define SSD_H_


#define SSD_COMMON_CATH       (1)

#define SSD_COMMON_AN         (0)


#define  SSD_TYPE       SSD_COMMON_CATH



typedef enum
{
	SSD_R=0,
	SSD_M=1,
	SSD_N=2,
	SSD_L=3
	
}tSSD;


typedef enum
{
	SSD_0 = 0,
	SSD_1,
	SSD_2,
	SSD_3,
	SSD_4,
	SSD_5,
	SSD_6,
	SSD_7,
	SSD_8,
	SSD_9,
	SSD_NULL,
}tSSD_Symbol;

#if (SSD_TYPE==SSD_COMMON_CATH)
typedef enum
{
	SSD_ON= 0,
	SSD_OFF=1,
}tSSD_STATE;


#else

typedef enum
{
	SSD_OFF= 0,
	SSD_ON=1,
}tSSD_STATE;
#endif


void SSD_Init(tSSD ssd);

void SSD_Update();

void SSD_Set_symbol(tSSD ssd, tSSD_Symbol symbl);

void SSD_Set_State(tSSD ssd, tSSD_STATE state);

#endif /* SSD_H_ */