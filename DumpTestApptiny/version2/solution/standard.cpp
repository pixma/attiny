/*
 * standard.cpp
 *
 * Created: 7/18/2014 11:30:20 AM
 *  Author: annim
 */ 

#include "stdafx.h"
#include "standard.h"

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

void initDevice(){
	// Battery Check and sleep.
	MCUCR = 0x00;		//disable any interrupt source.
	sleep_disable();
	
	unsigned int uchCount = 0;
	
	sbi(DDRA, LED0);					// set LED0 to output
	sbi(DDRA, LED1);					// set LED1 to output
	sbi(DDRA, SHDWN);					// set SHDWN to output
	cbi(DDRA, PWR);						// set PWR to input.
		
	sbi(PORTA, LED0);
	while ( uchCount < 55000 ){
		uchCount++;
	}	
	
	cbi(PORTA, LED0);
	
}

void setOutput( unsigned int portNumber, int pinNumber , bool state)
{
	if(state)
		sbi(portNumber, pinNumber);
	else
		cbi( portNumber, pinNumber );
}

void pinMode( unsigned int portnumber, int pinNumber, bool state )
{
	if (state)
	{
		sbi( portnumber, pinNumber );
	}
	else{
		cbi( portnumber, pinNumber );
	}
}

unsigned int digitalRead( unsigned int portNumber, int pinNumber )
{
	return ( (portNumber & (1<<pinNumber) ) >> pinNumber );// will return 0x00 or 0x01;
}

void sleepMe()
{		
	set_sleep_mode( SLEEP_MODE_PWR_DOWN );
	sleep_enable();
	sleep_mode();
}

bool pressWaitDelay()
{
	unsigned int nTimeM = 0;
	
	while (1)
	{
		nTimeM++;
		if (nTimeM > PRESS_WAIT)
		{
			break;
		}
	}
	
	return true;
}

unsigned int readBatterymilliVolts()
{
	// your code goes here.
	return 0;
}

bool isButtonPushedLong()
{
	unsigned int nPressCount = 0;
	bool event = false;
	
	//while (digitalRead(PORTA, PWR) == 0x00)
	while ( (PINA&(1<<PWR_READ))   == 0x00)
	{
		nPressCount++;
		if( nPressCount > PRESS_WAIT ){
			event = true;
			break;
		}
	}
	
	return event;
}

void plantPinChangeInt(  )
{
	cli();
	sbi(PCMSK0, PCINT3);	// set bit PCINTN on this interrupt.			
	sbi(GIMSK, PCIE0);      // enable interrupt pin change.
	sei();
}

void powerOn()
{	
	sbi( PORTA, LED1);
	sbi( PORTA, LED0);
	sbi( PORTA, SHDWN);	
}

void removePinChangeInt( )
{
	cli();
	cbi(SREG, SREG_I);		// clear global intterupt. alternative code line cli();
	cbi(GIMSK, PCIE0);      // enable interrupt pin change.	
	cbi(PCMSK0, PCINT3);	// set bit PCINTN on this interrupt.
	
}

void powerDown()
{
	cbi( PORTA, LED1);
	cbi( PORTA, LED0);
	cbi( PORTA, SHDWN);
	
	cbi(ADCSRA,ADEN);                              //switch Analog to Digital Converter OFF
}
