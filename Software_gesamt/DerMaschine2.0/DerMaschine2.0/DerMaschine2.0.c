////////////////////////////////////////////////////////////////////////////////
// Der Maschine																  //
// Version: 2.0				Stand 24.07.2014								  // 
// (c)	Adrian Wenzel, Tobias Roesch, Michael Boos							  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//		Include Header               										  //
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <stdlib.h>
#include "getranke.h"
#include "lcd-routines.h"
#include "delay.h"
#include <avr/interrupt.h>
#include "mixing.h"


////////////////////////////////////////////////////////////////////////////////
//		Definitionen                 										  //
////////////////////////////////////////////////////////////////////////////////

// #define Taster_Port PINB


void sleep ( int ms )
{
    for(; ms > 0; ms--) _delay_ms(1);
}

uint8_t taster_entprellung()
{
	uint8_t gedrucktet_Taster = 0;
	uint8_t static aktuell =0, vorher =0 ; // static deklaration damit daten nicht verloren gehen

	do 
	{
	
		aktuell = PINB;	// Einlesen von PortB
		//aktuell =~ aktuell;	// PortB invertieren,
	
		for (uint8_t i=0; i<5; i++)								// alle Pins (0-5) Prüfen
		{
			if (( aktuell & (1<<i) ) && ((vorher& (1<<i)) ^ (aktuell& (1<<i) )))	
			{
				gedrucktet_Taster = (i+1);						// Bit wird nur dann gesetzt wenn Taste gedrückt wird + Flankenwechsel vorliegt
				_delay_ms(600);
			}
		}	
		vorher=aktuell;

	} while (gedrucktet_Taster ==0 );
	
	return gedrucktet_Taster;
}

void berechnung_Pumpe(uint8_t auswahl_getrank, float schnaps_Zeit, float mischgetrank_Zeit, float schnaps_Prozent) 
{
	schnaps_Zeit = schnaps_Zeit * (schnaps_Prozent/100);
	mischgetrank_Zeit= mischgetrank_Zeit * (100-schnaps_Prozent)/100;
	
	// Zum Testen Zeiten definieren
	schnaps_Zeit = 2000;
	mischgetrank_Zeit = 4000;
	
	
	lcd_mixing(schnaps_Zeit,mischgetrank_Zeit);
	
	//Getränk fertig gemischt
	
}

void init_Timer0()
{
  TCCR0 = (1<<CS02); // Prescaler 256
  TIMSK |= (1<<TOIE0);// Overflow Interrupt erlauben
  
  
}
////////////////////////////////////////////////////////////////////////////////
//		Main Program												          //
////////////////////////////////////////////////////////////////////////////////





volatile unsigned int millisekunden;
volatile unsigned int over;


 
int main(void)
{
	DDRB  = 0x00;
	PORTB = 0xFF;
	
	DDRD  =	0xFF;
	PORTD = 0x00;
	
	lcd_init();
	init_Timer0();
	lcd_clear();
	
	t2_init();
	lcd_generate_bar_graphics();
	
	sei();
	lcd_startbild();
	sleep(2000);
	
	
	
uint8_t taster = 0,  schnaps_Prozent = 0, auswahl_getrank=0;
uint16_t schnaps_Zeit = 0;
uint16_t mischgetrank_Zeit = 0;

    while(1)
    {

	start:
	
		lcd_Homebild();
		taster = taster_entprellung();
		
		switch (taster)
		{
			case 1 : goto menue_mischen; break;
			case 2 : goto menue_mischen; break;
			case 5 : goto start; break;			
		}
		
	
	menue_mischen:
	{
		lcd_schnaps();
		taster = taster_entprellung();
		
		switch(taster)
		{
			case 1 : schnaps_auswahl = asbach;		schnaps_Zeit = Ascbach_Zeit; break;
			case 2 : schnaps_auswahl = wodka;		schnaps_Zeit = Wokda_Zeit; break;
			case 3 : schnaps_auswahl = whyski;      schnaps_Zeit = Whisky_Zeit;break;
			case 4 : schnaps_auswahl = rum;		    schnaps_Zeit = Rum_Zeit;break;
			case 5 : goto start; break;
		}
		
		
		lcd_mischgetrank();
		taster = taster_entprellung();
		
		switch(taster)
		{
			case 1 : mischgetrank_auswahl = cola;		mischgetrank_Zeit = Cola_Zeit;  break;
			case 2 : mischgetrank_auswahl = o_saft;		mischgetrank_Zeit = Osaft_Zeit; break;
			case 3 : mischgetrank_auswahl = bull ;	    mischgetrank_Zeit = Bull_Zeit;  break;
			case 4 : mischgetrank_auswahl = lemon;	    mischgetrank_Zeit = Lemon_Zeit; break;
			case 5 : goto start; break;
		}
		
		
		lcd_mischung();
		// Hier steht Routinenaufruf von Bargraph + Drehimpulsgeber
		sleep(2000);
		
		// zum Testen hier 40 zugewiesen
		schnaps_Prozent=40;
		
		
		lcd_ausgabegetrank(auswahl_getrank);
		lcd_anzeigegetranke2( );


		// Getränke zwei Sekunden anzeigen
		sleep(2000);
		
		//millisekunden=0;
		//do 
		//{
			//
		//} while (millisekunden<2000);
		
		berechnung_Pumpe(auswahl_getrank, schnaps_Zeit, mischgetrank_Zeit, schnaps_Prozent);
	
		
		goto start;
		
	
	}	
	
	menue_setup:
	{
		while (1)
		{
		}
	}			
		
      
    }
}


ISR (TIMER0_OVF_vect)
{
	over++;
	
	if (over == 12)		// es sind 100ms vergangen
	{
		over =0;
		millisekunden+=100;
	}
	
}
