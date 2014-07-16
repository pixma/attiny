/*
 * standard.cpp
 *
 * Created: 7/15/2014 12:40:33 PM
 *  Author: annim
 */ 


#ifndef STANDARD_H_
#define STANDARD_H_

#include "stdafx.h"
#include "standard.h"
#include <avr/io.h>


void intiDevice()
{
	
	
	
	
}

void setOutput( unsigned int pinNumber )
{
	//attiny 84
	/************************************************************************/
	/* PB3/rst- 1
	   PB2	 - 2
	   PA7   - 3
	   PA6   - 4/MOSI/SDA
	   PA5	 - 5/MISO/DO
	   PA4	 - 6/SCK/SCL
	   PA3	 - 7
	   PA2	 - 8
	   PA1	 - 9
	                                                                        */
	/************************************************************************/
	
	switch (pinNumber)
	{
		case 1:
			DDRB |= (1 << PB3);
		break;
		case 2:
			DDRB |= (1 << PB2);
		break;
		case 3:
			DDRA |= (1 << PA7);
		break;
		case 4:
			DDRA |= (1 << PA6);
		break;
		case 5:
			DDRA |= (1 << PA5);
		break;
		case 6:
			DDRA |= (1 << PA4);
		break;
		case 7:
			DDRA |= (1 << PA3);
		break;
		case 8:
			DDRA |= (1 << PA2);
		break;
		case 9:
		DDRA |= (1 << PA1);
		break;
	}
}

void pinMode( unsigned int pinNumber, bool state )
{
	switch( state ){
		case true:
		// HIGH 
		break;
		case false:
		// LOW
		break;
	}
}

#endif /* STANDARD_H_ */
