/*
 * nameMenu.c
 *
 * Created: 28.07.2014 19:49:11
 *  Author: Tobias
 */ 






#include <avr/io.h>
#include "lcd-routines.h"
#include "nameMenu.h"

int8_t current=0, seite=5;

char name[20]={' '};
int8_t cntName=0;

char arr[29];




int8_t nm_getCount(int8_t i)
{
	if(i>28)
	return (i-29);
	if(i<0)
	return (i+29);
	return i;
}	
	

	
void nm_print()
{
	lcd_clear();
	lcd_home();
	lcd_string(name);
	lcd_setcursor(0,2);
	
	for(int8_t i=current-seite;i<current;i++)
	{
		lcd_data(arr[nm_getCount(i)]);
	}
	lcd_string(" |");
	lcd_data(arr[current]);
	lcd_string("| ");
	for(int8_t i=current+1;i<current+seite+1;i++)
	{
		lcd_data(arr[nm_getCount(i)]);
	}
		
}



void nm_init()
{
	nm_confirmed=0;
	lcd_init();
	lcd_clear();

	for(int8_t i=0;i<26;i++)
	{
		arr[i]=i+65;
	}
	arr[26]='_';
	arr[27]=127;
	arr[28]=126;
	nm_print();
}




void nm_next(int8_t aufsteigend)
{
	if (aufsteigend==1)
		current++;
	else
		current--;
	current=nm_getCount(current);
	nm_print();
}

void nm_selection()
{	
	if(arr[current]==127)
	{
		if(cntName>0)
		{
			cntName--;
			name[cntName]=' ';
		}
	}
	else if (arr[current]==126)
	{
		nm_confirmed=1;
	}
	else 
	{
		if(cntName<20)
		{
			name[cntName]=arr[current];
			cntName++;			
		}

	}
	nm_print();
}

char* nm_getName()
{
	if(cntName>0)
	{
		for(int8_t i=0;i<cntName;i++)
		{	
			if (name[i]=='_')
			{
				name[i]=' ';
			}
		}
		return name;
	}
	else
		return 0;
}



