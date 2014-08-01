/*
 * nameMenu.h
 *
 * Created: 28.07.2014 19:52:54
 *  Author: Tobias
 */ 


#ifndef NAMEMENU_H_
#define NAMEMENU_H_


void nm_init();							//Muss zum Starten der eingabe aufgerufen werden

void nm_next(int8_t aufsteigend);		//Menü rechts/links bewegen ( 0 => links  /  1=> rechts )

void nm_selection();					//Auswahl der aktuellen Menüposition

char* nm_getName();						//auslesen der aktuell geschriebenen Eingabe

uint8_t nm_confirmed;					//wechselt von 0 auf 1 wenn eingabe beendet ist


#endif /* NAMEMENU_H_ */