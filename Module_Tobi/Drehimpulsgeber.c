/*
 * Drehimpulsgeber.c
 *
 * Created: 11.07.2014 17:49:29
 *  Author: Tobias
 */ 

#define Bit8(a,b,c,d,e,f,g,h) ((1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e)|(1<<f)|(1<<g)|(1<<h))
#define Bit7(a,b,c,d,e,f,g) ((1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e)|(1<<f)|(1<<g))
#define Bit6(a,b,c,d,e,f) ((1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e)|(1<<f))
#define Bit5(a,b,c,d,e) ((1<<a)|(1<<b)|(1<<c)|(1<<d)|(1<<e))
#define Bit4(a,b,c,d) ((1<<a)|(1<<b)|(1<<c)|(1<<d))
#define Bit3(a,b,c) ((1<<a)|(1<<b)|(1<<c))
#define Bit2(a,b) ((1<<a)|(1<<b))
#define Bit(a) (1<<a)



#include <avr/io.h>
#include <util/delay.h>


#define EINGANG_A 1							//Makros für Eingangsbits
#define EINGANG_B 2





int main(void)
{
	DDRB=0x00;													//Port B als eingang
	PORTB=0xFF;													//Pull up anschalten
	
	DDRC=0xFF;													//Port C ausgang
	
	
	uint8_t vorherig = 0;
	uint8_t aktuell;
	
    while(1)
    {

		aktuell=PINB & (Bit2(EINGANG_A,EINGANG_B));				//Beide Eingäne maskieren
		
		if(aktuell==0)											//Wenn beide Eingänge auf 0 sind (Stellung genau auf Rasterung)
		{
			if (aktuell ^ vorherig == Bit(EINGANG_A))			//je nachdem aus welcher Richtung man kommt
			{
				//entweder hochzählen
				PORTC |= Bit(1);				//zum test Led blinken lassen
				_delay_ms(50);					//später auswertung
				PORTC &= ~Bit(1);				
			}
			if (aktuell ^ vorherig == Bit(EINGANG_B))
			{
				//oder runterzählen
				PORTC |= Bit(0);				//zum test Led blinken lassen
				_delay_ms(50);					//später auswertung
				PORTC &= ~Bit(0);				
			}
		}
		vorherig=aktuell;
	}	

}