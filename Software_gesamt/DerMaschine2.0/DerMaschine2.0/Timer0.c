/*
 * Timer0.c
 *
 * Created: 25.07.2014 13:10:19
 *  Author: Michael
 */ 

#include <avr/io.h>
#include "lcd-routines.h"
#include <util/delay.h>
#include "Timer0.h"

void Timer0_init()
{
  TCCR0 = (1<<WGM01);				// CTC Modus
  TCCR0B |= (1<<CS01)|(1<<CS00) ;	// Vorteiler 64
									// ((8 MHz/64)/1000) = 125
  OCR0A = 125-1;					// wird bis hierher gezählt,   jeder Interrupt entspricht genaue 1ms!!!!
 
  // Compare Interrupt erlauben
  TIMSK |= (1<<OCIE0A);
 
  // Global Interrupts aktivieren
  sei();
}