/*
 * Analog_Umsetzer.c
 *
 * Created: 08.07.2014 19:00:18
 *  Author: Michael
 */ 

#include <avr/io.h>
#include "Analog_umsetzer.h"
#include <util/delay.h> 

void ADC_init()
{
	 ADMUX = (1<<REFS0);
	 ADMUX |= (1<<ADLAR);
	 ADCSRA = (1<<ADPS1) | (1<<ADPS2);
	 ADCSRA |= (1<<ADEN); 
	 ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
  while (ADCSRA & (1<<ADSC) )
   {         
	 }
	 (void)ADCL;
  (void) ADCH;	
}

uint16_t ADC_Read( uint8_t channel )
{
	  // Kanal waehlen, ohne andere Bits zu beeinflußen
	  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
	  while (ADCSRA & (1<<ADSC) ) 
	  {   // auf Abschluss der Konvertierung warten
	  }
  
	  (void)ADCL;
	  return ADCH;                    
}
 

uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples )
{
  uint32_t sum = 0;
 
  for (uint8_t i = 0; i < nsamples; ++i ) {
    sum += ADC_Read( channel );
  }
 
  return (uint16_t)( sum / nsamples );
}

uint16_t prozent(uint16_t input)
{
	input *= 100;
	return input / 255;
}

int adc_to_bargraph(uint16_t input)
{
	uint16_t bargraph=0b0;
	for(uint16_t i=0; i<255; i+=16)
	{
		if(input>i)
		{
			bargraph = (1<<0)|(bargraph<<1);
		}
	}

lcd_setcursor(2,2);
lcd_binaer(bargraph);	

}