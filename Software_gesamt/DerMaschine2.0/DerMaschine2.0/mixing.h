/*
 * Mixing.h
 *
 * Created: 02.08.2014 19:56:34
 *  Author: Adrian
 */ 


#ifndef MIXING_H_
#define MIXING_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif
#include <util/delay.h>
#include "lcd-routines.h"
#ifndef Zeichen_LCD
#define Zeichen_LCD 20
#endif

// Definition der benutzten Routinen
void lcd_graph(uint8_t wert_0_80);
void lcd_generate_bar_graphics(void);
void lcd_mixing(uint16_t ms_alk, uint16_t ms_nonalk);
void t2_init(void);
void t2_start(void);
void t2_stop(void);
ISR(TIMER2_COMP_vect);

// Globale Variablen
volatile uint16_t ms_pumpe1 = 0;
volatile uint32_t ms_timer2 = 0;
volatile uint8_t tick_pumpe = 0;

// Deklaration der benutzten Routinen
void t2_init(void)
{
	OCR2 = 125;				// ergibt bei 1Mhz eine Periodendauer von 1ms zwischen 2 Comparematches
	// wird in der ISR noch auf die CPU-Geschwindigkeit angepasst
	TCCR2 = (1<<WGM21);		// CTC-Mode (Clear Timer on Compare Match);
	TIMSK |= (1<<OCIE2);	// Interrupt bei Compare-Match enabled
	sei();					// Globales Interrupt Bit gesetzt
}

void t2_start(void)
{
	TCCR2 |= (1<<CS21);	// Timer starten mit Prescaler 8
}

void t2_stop(void)
{
	TCCR2 &= ~(1<<CS21);
	ms_timer2 = 0;
}

ISR(TIMER2_COMP_vect)
{
	static int8_t n = F_CPU / 1000000UL;
	n--;
	if (n == 0)
	{
		n = F_CPU / 1000000UL;
		ms_timer2++;
	}
	if (ms_pumpe1 == ms_timer2)
	{
		tick_pumpe = 1;
	}
}

void lcd_graph(uint8_t wert_0_80)
{
	// "wert_0_80" kann Werte von 0 bis Anzahl_Zeichen_LCD*5 annehmen
	// bei Anzahl_Zeichen_LCD=16 ist Max-Wert=80, bei Zeichen_LCD = 20 ist Max-Wert=100
	uint8_t cursor_now = 0;
	
	lcd_setcursor(0,2);
	for (; wert_0_80 >= 5 ; wert_0_80 -= 5)
	{
		lcd_data(5);
		cursor_now++;
	}
	
	lcd_data(wert_0_80);
	cursor_now++;
	
	for (uint8_t i = 0; i < (Zeichen_LCD - cursor_now); i++)
	{
		lcd_data(0);
	}
}

void lcd_generate_bar_graphics(void)
{
	uint8_t bar_0[8];
	bar_0[0] = bar_0[7] = 0;
	bar_0[1] = bar_0[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_0[i] = 0;
	}

	uint8_t bar_1[8];
	bar_1[0] = bar_1[7] = 0;
	bar_1[1] = bar_1[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_1[i] = 16;
	}

	uint8_t bar_2[8];
	bar_2[0] = bar_2[7] = 0;
	bar_2[1] = bar_2[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_2[i] = 24;
	}
	
	uint8_t bar_3[8];
	bar_3[0] = bar_3[7] = 0;
	bar_3[1] = bar_3[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_3[i] = 28;
	}
	
	uint8_t bar_4[8];
	bar_4[0] = bar_4[7] = 0;
	bar_4[1] = bar_4[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_4[i] = 30;
	}
	
	uint8_t bar_5[8];
	bar_5[0] = bar_5[7] = 0;
	bar_5[1] = bar_5[6] = 31;
	for (uint8_t i = 2; i < 6; i++)
	{
		bar_5[i] = 31;
	}
	
	lcd_generatechar(0, bar_0);
	lcd_generatechar(1, bar_1);
	lcd_generatechar(2, bar_2);
	lcd_generatechar(3, bar_3);
	lcd_generatechar(4, bar_4);
	lcd_generatechar(5, bar_5);
}

void lcd_mixing(uint16_t ms_alk, uint16_t ms_nonalk)
{
	uint32_t ms_ges = ms_alk + ms_nonalk;
	ms_pumpe1 = ms_alk;
	uint16_t divisor = ms_ges / (Zeichen_LCD * 5);			// (Anzahl_Zeichen_LCD * 5 Segmente im LCD-Bargraph)
	uint8_t fill_prev = 0;
	
	lcd_clear();
	lcd_home();
	
	//lcd_string("Mischen lauft...");
	//// "ä" nachträglich einfügen
	//lcd_setcursor(9,1);
	//lcd_data(225);
	
	//pumpe_aktiv(erste Pumpe);
	lcd_string("Mischen: Alk");
	
	t2_start();
	
	while (ms_timer2 < ms_ges)
	{
		// Platz für weiterer Code, Timer2 regelt alles ;)
		if (tick_pumpe)
		{
			tick_pumpe = 0;
			//pumpe_aktiv(nächste Pumpe);
			lcd_setcursor(9,1);
			lcd_string("Non-Alk");
		}
		if ((ms_timer2 / divisor) != fill_prev)
		{
			fill_prev = ms_timer2 / divisor;
			lcd_graph(fill_prev);
		}
	}
	lcd_graph(Zeichen_LCD * 5);		// letztes Segment auch ausfüllen
	//pumpe_stop();

	t2_stop();		// Timer anhalten
	
	_delay_ms(1400);
	lcd_clear();
	lcd_home();
	lcd_string("Guten Durst!");
	_delay_ms(2500);
}

#endif /* MIXING_H_ */