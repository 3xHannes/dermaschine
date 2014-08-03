// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// http://www.mikrocontroller.net/articles/HD44780
// http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/LCD-Ansteuerung
//
// Die Pinbelegung ist über defines in lcd-routines.h einstellbar
 
#include <avr/io.h>
#include "lcd-routines.h"
#include <util/delay.h>
#include "getranke.h"




 
////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls
static void lcd_enable( void )
{
    LCD_PORT |= (1<<LCD_EN);     // Enable auf 1 setzen
    _delay_us( LCD_ENABLE_US );  // kurze Pause
    LCD_PORT &= ~(1<<LCD_EN);    // Enable auf 0 setzen
}
 
////////////////////////////////////////////////////////////////////////////////
// Sendet eine 4-bit Ausgabeoperation an das LCD
static void lcd_out( uint8_t data )
{
    data &= 0xF0;                       // obere 4 Bit maskieren
 
    LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // Maske löschen
    LCD_PORT |= (data>>(4-LCD_DB));     // Bits setzen
    lcd_enable();
}
 
////////////////////////////////////////////////////////////////////////////////
// Initialisierung: muss ganz am Anfang des Programms aufgerufen werden.
void lcd_init( void )
{
    // verwendete Pins auf Ausgang schalten
    uint8_t pins = (0x0F << LCD_DB) |           // 4 Datenleitungen
                   (1<<LCD_RS) |                // R/S Leitung
                   (1<<LCD_EN);                 // Enable Leitung
    LCD_DDR |= pins;
 
    // initial alle Ausgänge auf Null
    LCD_PORT &= ~pins;
 
    // warten auf die Bereitschaft des LCD
    _delay_ms( LCD_BOOTUP_MS );
 
    // Soft-Reset muss 3mal hintereinander gesendet werden zur Initialisierung
    lcd_out( LCD_SOFT_RESET );
    _delay_ms( LCD_SOFT_RESET_MS1 );
 
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS2 );
 
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS3 );
 
    // 4-bit Modus aktivieren 
    lcd_out( LCD_SET_FUNCTION |
             LCD_FUNCTION_4BIT );
    _delay_ms( LCD_SET_4BITMODE_MS );
 
    // 4-bit Modus / 2 Zeilen / 5x7
    lcd_command( LCD_SET_FUNCTION |
                 LCD_FUNCTION_4BIT |
                 LCD_FUNCTION_2LINE |
                 LCD_FUNCTION_5X7 );
 
    // Display ein / Cursor aus / Blinken aus
    lcd_command( LCD_SET_DISPLAY |
                 LCD_DISPLAY_ON |
                 LCD_CURSOR_OFF |
                 LCD_BLINKING_OFF); 
 
    // Cursor inkrement / kein Scrollen
    lcd_command( LCD_SET_ENTRY |
                 LCD_ENTRY_INCREASE |
                 LCD_ENTRY_NOSHIFT );
 
    lcd_clear();
}
 
////////////////////////////////////////////////////////////////////////////////
// Sendet ein Datenbyte an das LCD
void lcd_data( uint8_t data )
{
    LCD_PORT |= (1<<LCD_RS);    // RS auf 1 setzen
 
    lcd_out( data );            // zuerst die oberen, 
    lcd_out( data<<4 );         // dann die unteren 4 Bit senden
 
    _delay_us( LCD_WRITEDATA_US );
}
 
////////////////////////////////////////////////////////////////////////////////
// Sendet einen Befehl an das LCD
void lcd_command( uint8_t data )
{
    LCD_PORT &= ~(1<<LCD_RS);    // RS auf 0 setzen
 
    lcd_out( data );             // zuerst die oberen, 
    lcd_out( data<<4 );           // dann die unteren 4 Bit senden
 
    _delay_us( LCD_COMMAND_US );
}
 
////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl zur Löschung des Displays
void lcd_clear( void )
{
    lcd_command( LCD_CLEAR_DISPLAY );
    _delay_ms( LCD_CLEAR_DISPLAY_MS );
}
 
////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl: Cursor Home
void lcd_home( void )
{
    lcd_command( LCD_CURSOR_HOME );
    _delay_ms( LCD_CURSOR_HOME_MS );
}
 
////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (1..4) 
 
void lcd_setcursor( uint8_t x, uint8_t y )
{
    uint8_t data;
 
    switch (y)
    {
        case 1:    // 1. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;
 
        case 2:    // 2. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;
 
        case 3:    // 3. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
            break;
 
        case 4:    // 4. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
            break;
 
        default:
            return;                                   // für den Fall einer falschen Zeile
    }
 
    lcd_command( data );
}
 
////////////////////////////////////////////////////////////////////////////////
// Schreibt einen String auf das LCD
 
void lcd_string( const char *data )
{
    while( *data != '\0' )
        lcd_data( *data++ );
}
 
////////////////////////////////////////////////////////////////////////////////
// Schreibt ein Zeichen in den Character Generator RAM
 
void lcd_generatechar( uint8_t code, const uint8_t *data )
{
    // Startposition des Zeichens einstellen
    lcd_command( LCD_SET_CGADR | (code<<3) );
 
    // Bitmuster übertragen
    for ( uint8_t i=0; i<8; i++ )
    {
        lcd_data( data[i] );
    }
}

void lcd_binaer( uint16_t data )
{
	char Buffer[20];

	itoa( data, Buffer, 2 );
	lcd_string( Buffer ); // ggf. auch lcd_out() o.ä. in anderen Libraries
}

void lcd_integer( uint16_t data )
{
	char Buffer[20];

	itoa( data, Buffer, 10 );
	lcd_string( Buffer ); // ggf. auch lcd_out() o.ä. in anderen Libraries
}

////////////////////////////////////////////////////////////////////////////////
// Bildschrim anzeige Text

void lcd_startbild()
{
	lcd_clear();
	lcd_string("Der Maschine 2.0");
	lcd_setcursor(0,2); 
	lcd_string("Sauf nei alter!");
}

void lcd_Homebild()
{
	lcd_clear();
	lcd_string("Mischen");
	lcd_setcursor(12,1); 
	lcd_string("Setup");
}

void lcd_mischgetrank()
{
	lcd_clear();
	lcd_string("Cola");
	lcd_setcursor(10,1); 
	lcd_string("O-Saft");
	lcd_setcursor(0,2); 
	lcd_string("Bull");
	lcd_setcursor(10,2); 
	lcd_string("Lemon");
}

void lcd_schnaps()
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

void lcd_mischung()
{
	lcd_clear();
	lcd_string("Mischung mit Poti");
	lcd_setcursor(0,2); 
	lcd_string("Eingabe");
		
}

void lcd_ausgabegetrank(uint8_t liste)
{
	lcd_clear();
	lcd_binaer(liste);
}

void lcd_anzeigegetranke(uint8_t getrank)
{
	lcd_clear();
	if (getrank & (1<<0))
	{
		lcd_string("Cola");
	}
	
	if (getrank & (1<<1))
	{
		lcd_string("O-saft");
	}
	
	if (getrank & (1<<2))
	{
		lcd_string("Bull");
	}
	
	if (getrank & (1<<3))
	{
		lcd_string("Lemon");
	}
	
	if (getrank & (1<<4))
	{
		lcd_setcursor(0,2); 
		lcd_string("Asbach");
	}
	
	if (getrank & (1<<5))
	{
		lcd_setcursor(0,2); 
		lcd_string("Wodka");
	}
	
	if (getrank & (1<<6))
	{	
		lcd_setcursor(0,2); 
		lcd_string("Whisky");
	}
	
	if (getrank & (1<<7))
	{
		lcd_setcursor(0,2); 
		lcd_string("Rum");
	}
	
}


void lcd_anzeigegetranke2()
{
	lcd_clear();
	if (mischgetrank_auswahl == cola)
	{
		lcd_string("Cola");
	}
	
	if (mischgetrank_auswahl == o_saft)
	{
		lcd_string("O-saft");
	}
	
	if (mischgetrank_auswahl == bull)
	{
		lcd_string("Bull");
	}
	
	if (mischgetrank_auswahl == lemon)
	{
		lcd_string("Lemon");
	}
	
	if (schnaps_auswahl == asbach)
	{
		lcd_setcursor(0,2); 
		lcd_string("Asbach");
	}
	
	if (schnaps_auswahl == wodka)
	{
		lcd_setcursor(0,2); 
		lcd_string("Wodka");
	}
	
	if (schnaps_auswahl == whyski)
	{	
		lcd_setcursor(0,2); 
		lcd_string("Whisky");
	}
	
	if (schnaps_auswahl == rum)
	{
		lcd_setcursor(0,2); 
		lcd_string("Rum");
	}
	
}

