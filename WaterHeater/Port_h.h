/*
 * Port_h.h
 *
 * Created: 9/27/2020 8:08:04 PM
 *  Author: hp
 */ 


#ifndef PORT_H_H_
#define PORT_H_H_

#include "DIO_Interface.h"



// Board_Clock
#define F_CPU 8000000UL

/*******************SSD*********************/

#define NUMBER_OF_SSD        (2)


#define SSD_DIRC     PD

#define SSD_PORT     PD

//#define SSD_CON_PIN_DIRC     PD

//#define SSD_CON_PIN_PORT     PD

#define SSDR                 (PINC2)

#define SSDM                 (PINC3)

#define SSDN                 (PINC4)

#define SSDL                 (PINC5)


/*****************SSD_END**********************/


/***********************END_LCD********************************/


#define LM35_Pin                  PINA0

#define LM35_Channel              ChanneL0




/*******************************SENSORS*********************************/


#define SW_PLUS_PORT_DR     (PORTB)
#define SW_PLUS_PORT_CR     (DDRB)
#define SW_PLUS_PORT_READ   (PINB)
#define SW_PLUS_PIN         (0)



#define SW_MINUS_PORT_DR    (PORTB)
#define SW_MINUS_PORT_CR    (DDRB)
#define SW_MINUS_PORT_READ   (PINB)
#define SW_MINUS_PIN        (1)

#define SW_ON_OFF_PORT_DR      (PORTB)
#define SW_ON_OFF_PORT_CR      (DDRB)
#define SW_ON_OFF_PORT_READ    (PINB)
#define SW_ON_OFF_PIN          (2)



/***************************ELEMENTS*****************************************/


#define HEATING_ELEMENT_PIN                 (PINB3)

#define COOLING_ELEMENT_PIN                 (PINB4)

/*****************************LED***************************************/

#define LED_PIN                            (PINB5)


/*******************I2C_PINS*********************************/

#define SCL_PIN                   (PINC0)

#define SDA_PIN                   (PINC1)


#define INIT_FLAG_ADDERESS          (0x00)
#define USER_TEMP_SAVING_ADDERESS   (0x01)

#endif /* PORT_H_H_ */