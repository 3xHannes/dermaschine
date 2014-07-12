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

int main(void)
{
	DDRB=0x00;
	PORTB=0xFF;
	
	DDRC=0xFF;
	
	
	uint8_t vorherig_halbschritt = 0;
	uint8_t vorherig_gesamtschritt = 0;
	uint8_t aktuell;
	
    while(1)
    {

		aktuell=PINB & (Bit2(2,1));								//Beide Eingäne holen
		if ((aktuell ^ vorherig_gesamtschritt)==(Bit2(2,1) ))	//Wenn sich beide Bits geändert haben (neue position)
		{
			if ((aktuell ^ vorherig_halbschritt)==Bit(1))		//Je nachdem welches Bit sich als letztes geändert hat: 
			{
				//entweder hochzählen
				PORTC |= Bit(2);				//zum test Led blinken lassen
				_delay_ms(500);					//später auswertung
				PORTC &= ~Bit(2);
			}
			else
			{
				//oder runterzählen
				PORTC |= Bit(0);				//zum test Led blinken lassen
				_delay_ms(500);					//später auswertung
				PORTC &= ~Bit(0);
			}
			vorherig_gesamtschritt=aktuell;						//akt. als neuer wert für gesamtschritt
		}
		vorherig_halbschritt=aktuell;							//akt. als neuer wert für halbschritt

    }
}