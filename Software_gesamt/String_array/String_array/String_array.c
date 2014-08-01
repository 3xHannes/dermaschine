/*
 * String_array.c
 *
 * Created: 29.07.2014 22:57:55
 *  Author: Michael
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>


/*
const char Str1[]  = "Text1";
const char Str2[]  = "Text2";

const char* Strings[] = { Str1, Str2 };
*/
static const char str0[] PROGMEM = "Error 2014";
static const char str1[] PROGMEM = "Asbach";
static const char str2[] PROGMEM = "Wodka";
static const char str3[] PROGMEM = "Whyski";
static const char str4[] PROGMEM = "Rum";
static const char str5[] PROGMEM = "-------";
static const char str6[] PROGMEM = "-------";
static const char str7[] PROGMEM = "-------";
static const char str8[] PROGMEM = "-------";
static const char str9[] PROGMEM = "-------";
static const char str10[] PROGMEM = "-------";
static const char str11[] PROGMEM = "-------";
static const char str12[] PROGMEM = "-------";
static const char str13[] PROGMEM = "-------";
static const char str14[] PROGMEM = "-------";
static const char str15[] PROGMEM = "-------";
static const char str16[] PROGMEM = "Cola";
static const char str17[] PROGMEM = "O-Saft";
static const char str18[] PROGMEM = "Bull";
static const char str19[] PROGMEM = "Lemom";
 
const char * const getranke_namen[] PROGMEM = 
{
   str0,str1, str2, str3, str4, str5,str6,str7,str8,str9,str10,str11,str12,str13,str14, str15, str16, str17, str18, str19
};



int main(void)
{
	lcd_init();
	lcd_clear();
	char* buf[20];

    const char *parray = (const char*) pgm_read_word (&getranke_namen[17]); // Lese die Adresse des i-ten Strings aus array[]
    strcpy_P (buf, parray); // Kopiere den Inhalt der Zeichenkette vom Flash ins RAM
	//lcd_string(buf); // Ausgabe des Textes 
	
	
	void lcd_schnaps(uint8_t bereich)
	{
		lcd_clear();
		lcd_string("Asbach");
		lcd_setcursor(10,1); 
		lcd_string("Wodka");
		lcd_setcursor(0,2); 
		lcd_string("Whisky");
		lcd_setcursor(10,2); 
		lcd_string("Rum");
	
	}
	
	
    while(1)
    {
       
    }
}