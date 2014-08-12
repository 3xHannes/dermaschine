/*
 * pinconfig.h
 *
 * Created: 12.08.2014 18:32:12
 *  Author: Adrian
 */ 

// Pin-Configuration des ATMEGA32

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