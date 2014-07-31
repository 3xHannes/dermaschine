/*
 * getranke.h
 *
 * Created: 25.07.2014 13:45:56
 *  Author: Michael
 */ 


#ifndef GETRANKE_H_
#define GETRANKE_H_
//
// Bit die gesetzt werden für Pumpe
//
/*
#define Cola 1			//Bit1 setzten
#define Osaft 2			//Bit2 setzten
#define Bull 4			//Bit3 setzten
#define Lemon 8			//Bit4 setzen

#define Asbach 16
#define Wodka 32
#define Whisky 64
#define Rum	128
*/

enum schnaps
{
	asbach=1, wodka, whyski, rum, 
} schnaps_auswahl;
//schnaps schnaps_auswahl;

 enum mischgetrank
{
	cola=16, o_saft, bull, lemon, kirsch, 
}mischgetrank_auswahl;

//mischgetrank mischgetrank_auswahl;

//
// Durchlaufzeit für 0,2l je Getränk in ms
//

#define Cola_Zeit 555
#define Osaft_Zeit 5000UL
#define Bull_Zeit 5000UL
#define Lemon_Zeit 5000UL

#define Ascbach_Zeit 1444
#define Wokda_Zeit 5000UL
#define Whisky_Zeit 5000UL
#define Rum_Zeit 5000UL



#endif /* GETRANKE_H_ */