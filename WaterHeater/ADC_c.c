/*
 * ADC_c.c
 *
 * Created: 10/5/2020 8:01:56 PM
 *  Author: hp
 */ 
#include "ADC.h"

#define ADC_Busy           (((ADC_ADCSRA) & (1<<ADSC) ))




void ADC_Init(Vref_type vref,Clk_SelectType clk)
{
	switch(vref)
	{
			case (Vref_Turn_Off):
			
			CLEAR_BIT(ADC_ADUMX,REFS0);
			CLEAR_BIT(ADC_ADUMX,REFS0);
			break;
			
			case (AVCC):
			
			Set_BIT(ADC_ADUMX,REFS0);
			CLEAR_BIT(ADC_ADUMX,REFS1);
			break;
			
			case(Internal_Vref):
		    
			Set_BIT(ADC_ADUMX,REFS1);
			Set_BIT(ADC_ADUMX,REFS1);
		    break;
			
			default:
                 // Wrong Enter
			break;
		
			
	}
	
	switch(clk)
	{
			case(CLK_ADC_DIV_2):
			
			Set_BIT(ADC_ADCSRA,ADPS0);
			CLEAR_BIT(ADC_ADCSRA,ADPS1);
			CLEAR_BIT(ADC_ADCSRA,ADPS2);
			
			break;
			
			case(CLK_ADC_DIV_4):
			
			CLEAR_BIT(ADC_ADCSRA,ADPS0);
			Set_BIT(ADC_ADCSRA,ADPS1);
			CLEAR_BIT(ADC_ADCSRA,ADPS2);
			
			break;
			
			case(CLK_ADC_DIV_8):
			
			Set_BIT(ADC_ADCSRA,ADPS0);
			Set_BIT(ADC_ADCSRA,ADPS1);
			CLEAR_BIT(ADC_ADCSRA,ADPS2);
			
			break;
			
			case(CLK_ADC_DIV_16):
			
			CLEAR_BIT(ADC_ADCSRA,ADPS0);
			CLEAR_BIT(ADC_ADCSRA,ADPS1);
			Set_BIT(ADC_ADCSRA,ADPS2);
			
			break;
			
			case(CLK_ADC_DIV_32):
			
		    Set_BIT(ADC_ADCSRA,ADPS0);
		    CLEAR_BIT(ADC_ADCSRA,ADPS1);
		    Set_BIT(ADC_ADCSRA,ADPS2);
			
			
			break;
			
			case(CLK_ADC_DIV_64):
			
			CLEAR_BIT(ADC_ADCSRA,ADPS0);
			Set_BIT(ADC_ADCSRA,ADPS1);
			Set_BIT(ADC_ADCSRA,ADPS2);
			
			break;
			
		    case(CLK_ADC_DIV_128):
			
			Set_BIT(ADC_ADCSRA,ADPS0);
			Set_BIT(ADC_ADCSRA,ADPS1);
			Set_BIT(ADC_ADCSRA,ADPS2);		    
			
			break;
			
			default:
                     // Wrong Enter
			break;
		
	}
	
	CLEAR_BIT(ADC_ADUMX,ADLAR);
	
	
	 //ADC   ADCSRA Enable bit
	
	Set_BIT(ADC_ADCSRA,ADEN);

}


void ADC_Converstion(Conversion__Status state)
{
	SET_REGISTER_PIN(ADC_ADCSRA,ADSC,state);
}
uint16 ADC_Read(ChanneL_Select channel)
{
	uint16 ret=0;
	/*
  switch(channel)
  {
		case (ChanneL0):
        CLEAR_BIT();
		CLEAR_BIT();
		CLEAR_BIT();
		CLEAR_BIT();
		CLEAR_BIT();
				
		break
		
		case (ChanneL1):
		
		break;
		
		case(ChanneL2):
		
		break;
		
		
		case (ChanneL3):
		
		break;
		
		case (ChanneL4):
		
		break;
		
		case (ChanneL5):
		
		break;
		case (ChanneL6):
		
		break;
		
		case(ChanneL7):
		
		break  
  
  
  
  
  
  
  }	*/
	
		ADC_ADUMX &=~(0x1f);              // Clear all channels
		
		ADC_ADUMX|=(channel<<MUX0);
		
        ADC_Converstion(Conversion_on);

        while(ADC_Busy);
		
		ret=ADC;
		
		return ret;

}

Bool_t ADC_ASY_Read(ChanneL_Select channel,uint16 *ptr)
{
 	Bool_t ret=FALSE;
	
   return ret; 
}

//uint16 Temp_read()
//{
	/* you have to flags
	
	*Flag to check adc is ready to read if not ready do not store it in buffer
	
	*After 10 readings take (AVG) then raise second flag 
	
	*After getting temp Lower flag
	
	*/
	/*
	uint16 temp;
	//ADC_ASY_Read
	temp=ADC_Read(LM35_Channel);
	temp=((uint32)temp*5000)/1024;
	temp=temp/10;
	return temp;


}
*/
uint16 Get_ADC_NO_BLOCK(ChanneL_Select channel)
{
		uint16 ret=0;
		
		ADC_ADUMX &=~(0x1f);              // Clear all channels
		
		ADC_ADUMX|=(channel<<MUX0);
			
		ret=ADC;
		
		return ret;
}