////////////////////////////////////////////////////////////////////////////////
// DER Maschine																  //
// Version: 2.0				Stand 08.07.2014								  // 
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//		Include Header               										  //
////////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "lcd-routines.h"
#include "Analog_umsetzer.h"

////////////////////////////////////////////////////////////////////////////////
//		Main Program												          //
////////////////////////////////////////////////////////////////////////////////

void sleep ( uint8_t ms )
{
    for(; ms > 0; ms--) _delay_ms(4);
}

void startbild()
{
	lcd_clear();
	//lcd_string("Test");
	
	
	uint8_t chrdata0[8] = {
        0b00001001,//1
        0b00001001,	//2
        0b00001001,    //   X X     3
        0b00001001,     //  XXXXX   4
        0b00001001,     //   XXX    5
        0b00001001,     //    X     6
        0b00001001,//	            7
        0b00000110				//  8
        };
    lcd_generatechar(LCD_GC_CHAR0, chrdata0);
 
    lcd_setcursor(15,1);
    lcd_data(LCD_GC_CHAR0);
	sleep(5000);
	
	lcd_clear();
}

void startbild1()
{
	lcd_clear();
	lcd_string("Der Machine 2.0");
	lcd_setcursor(0,2); 
	lcd_string("Sauf nei alter!")
	
}



int main(void)
{
	
lcd_init(); // Display Initialisieren
ADC_init();	// AD-Umsetzung Initialisieren 

uint16_t adc_in=0, adc_vorher=0, c=0,d=0;


startbild1();

    while(1)
    {		
		
		adc_in = ADC_Read_Avg(0,50);
		d=adc_in;
		
		if(adc_in!=adc_vorher)
		{
			adc_in = prozent(adc_in);
			c=100-adc_in;	
			
			lcd_clear();
		
			lcd_integer(adc_in);
			lcd_string(" ");
	
			lcd_integer(c);
			lcd_string(" ");
		
			adc_to_bargraph(d);
		
		}
		adc_vorher=adc_in;
    }
}