/*
 * sr_routines.h
 *
 * Created: 12.08.2014 18:30:58
 *  Author: Adrian
 */ 


#ifndef SR_ROUTINES_H_
#define SR_ROUTINES_H_

// Pin-Configuration
#ifndef PINCONFIG_H_
#define PINCONFIG_H_

// Shift-Register: Port und Pins
#define PORTSR		PORTB
#define SCK			PB0
#define SI			PB1
#define OE_Bargrpah	PB2		// !OE = !G
#define OE_LED		PB3		// !OE = !G
#define OE_Motor	PB4		// !OE = !G
#define RCK_Bargraph PB5
#define RCK_LED		PB6
#define RCK_Motor	PB7

#endif /* PINCONFIG_H_ */

// Schieberegister-Routinen
void sr_init(void)
{
	DDRB = 255;		// alle Pins des DDRB als Ausgänge
	// Output Disable
	PORTSR |= ((1<<OE_Bargrpah) | (1<<OE_LED) | (1<<OE_Motor));
	// Taktleitungen und Datenleitungen auf LOW
	PORTSR &= ~(1<<SCK);
	PORTSR &= ~(1<<SI);
	
	PORTSR &= ~((1<<RCK_Bargraph) | (1<<RCK_LED) | (1<<RCK_Motor));
	for (uint8_t i = 0; i < 16; i++)
	{
		// Puls an SCK erzeugen = ins Shift-Register schieben
		PORTSR |= (1<<SCK);
		PORTSR &= ~(1<<SCK);
	}
	// Puls an RCK erzeugen = vom Shift-Register ins Storage-Register übernehmen
	PORTSR |= ((1<<RCK_Bargraph) | (1<<RCK_LED) | (1<<RCK_Motor));
	PORTSR &= ~((1<<RCK_Bargraph) | (1<<RCK_LED) | (1<<RCK_Motor));
}

// Bargraph, low-aktiv
void sr_push_bar(uint16_t wert, uint16_t max_wert)
{
	// Nachkommastellen werden bei den Divisionen abgeschnitten (hier nützlich, da so passende Abstufungen
	// in der Skalierung (LEDs) des Bargrpahs entstehen), LED16 leuchtet kurz vor 100%, keine LED kurz vor 0%
	uint8_t divisor = max_wert / 16;	//16 LEDs am Bargraph
	wert /= divisor;
	
	// Taktleitungen auf LOW, ansonsten erster Takt-Puls nicht möglich
	PORTSR &= ~(1<<SCK);
	PORTSR &= ~(1<<RCK_Bargraph);
	
	PORTSR |= (1<<OE_Bargrpah);
	
	for (uint8_t i = 16; i > 0; i--)
	{
		if (wert >= i)				// LEDs low-aktiv!
		{
			PORTSR &= ~(1<<SI);
		}
		else
		{
			PORTSR |= (1<<SI);
		}
		// Puls an SCK erzeugen = ins Shift-Register schieben
		PORTSR |= (1<<SCK);
		PORTSR &= ~(1<<SCK);
	}
	// Puls an RCK erzeugen = vom Shift-Register ins Storage-Register übernehmen
	PORTSR |= (1<<RCK_Bargraph);
	PORTSR &= ~(1<<RCK_Bargraph);
	// Output Enable
	PORTSR &= ~(1<<OE_Bargrpah);
}

// Motorsteuerung, high-aktiv
void pumpe_aktiv(uint8_t Pumpe_1_16)
{
	// Output Disable
	PORTSR |= (1<<OE_Motor);
	
	// Taktleitungen auf LOW, ansonsten erster Takt-Puls nicht möglich
	PORTSR &= ~(1<<SCK);
	PORTSR &= ~(1<<RCK_Motor);
	
	for (uint8_t i = 16; i > 0; i--)
	{
		if (i == Pumpe_1_16)
		{
			PORTSR |= (1<<SI);
		}
		else
		{
			PORTSR &= ~(1<<SI);
		}
		// Puls an SCK erzeugen = ins Shift-Register schieben
		PORTSR |= (1<<SCK);
		PORTSR &= ~(1<<SCK);
	}
	
	// Puls an RCK erzeugen = vom Shift-Register ins Storage-Register übernehmen
	PORTSR |= (1<<RCK_Motor);
	PORTSR &= ~(1<<RCK_Motor);
	// Output Enable
	PORTSR &= ~(1<<OE_Motor);
}

void pumpe_stop(void)
{
	// Output Disable
	PORTSR |= (1<<OE_Motor);
	
	// Sicherheitshalber alle Bits im Schieberegister löschen:
	
	// Taktleitungen und Datenleitungen auf LOW
	PORTSR &= ~(1<<SCK);
	PORTSR &= ~(1<<RCK_Motor);
	PORTSR &= ~(1<<SI);
	
	for (uint8_t i = 0; i < 16; i++)
	{
		// Puls an SCK erzeugen = ins Shift-Register schieben
		PORTSR |= (1<<SCK);
		PORTSR &= ~(1<<SCK);
	}
	// Puls an RCK erzeugen = vom Shift-Register ins Storage-Register übernehmen
	PORTSR |= (1<<RCK_Motor);
	PORTSR &= ~(1<<RCK_Motor);
}


// Beleuchtung (muss noch geschrieben werden)

#endif /* SR_ROUTINES_H_ */