/*
 * Timer_C.c
 *
 * Created: 28.07.2014 16:06:57
 *  Author: Michael
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int hundertmillisekunden;
volatile unsigned int over;

int main(void)
{

	DDRC = 0xFF;
	PORTC = 0x00;
  TCCR0 = (1<<CS02); // Prescaler 256
  
   // Overflow Interrupt erlauben
  TIMSK |= (1<<TOIE0);
  sei();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR (TIMER0_OVF_vect)
{
	over++;
	if (over == 12)
	{
		over =0;
		hundertmillisekunden++;
	}
	
	if (hundertmillisekunden == 10)
	{
		PORTC ^= ( 1 << PC0 );
		hundertmillisekunden =0;
	}
 
}