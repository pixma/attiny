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
	MCUCR = 0x00;		//disable any intterupt source.
	sleep_disable();
	
	unsigned char uchCount = 0;
	
	pinMode(DDRA, LED0 , HIGH);			// set LED0 to output
	pinMode(DDRA, LED1 , HIGH);			// set LED1 to output
	pinMode(DDRA, SHDWN , HIGH);		// set SHDWN to output
	pinMode(DDRA, PWR, LOW );			// set PWR to input.
	
	setOutput(PORTA, LED0, HIGH);
	while ( uchCount < 255 ){
		uchCount++;
	}
	setOutput(PORTA, LED0, LOW);
	
}

void setOutput( unsigned int portNumber, unsigned int pinNumber , bool state)
{
	if(state)
		sbi(portNumber, pinNumber);
	else
		cbi( portNumber, pinNumber );
}

void pinMode( unsigned int portnumber, unsigned int pinNumber, bool state )
{
	if (state)
	{
		sbi( portnumber, pinNumber );
	}
	else{
		cbi( portnumber, pinNumber );
	}
}

unsigned int digitalRead( unsigned int portNumber, unsigned int pinNumber )
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
	
	while (digitalRead(PORTA, PWR) == 0x00)
	{
		nPressCount++;
		if( nPressCount > PRESS_WAIT ){
			event = true;
			break;
		}
	}
	
	return event;
}

void plantPinChangeInt( unsigned int PCiEn, unsigned int PCMsKn, unsigned int PCInTn )
{
	setOutput(SREG, SREG_I, LOW);		// clear global intterupt. alternative code line cli();
	setOutput(PCMsKn, PCInTn, HIGH);	// set bit PCINTN on this interrupt.			
	setOutput(GIMSK, PCiEn, HIGH);      // enable interrupt pin change.
	setOutput(SREG, SREG_I, HIGH);		// set global intterupt. alternative code line sei();
}

void powerOn()
{	
	setOutput( PORTA, LED1, HIGH);
	setOutput( PORTA, LED0, HIGH);
	setOutput( PORTA, SHDWN, HIGH);	
}

void removePinChangeInt( unsigned int PCiEn, unsigned int PCMsKn, unsigned int PCInTn )
{
	setOutput(SREG, SREG_I, LOW);		// clear global intterupt. alternative code line cli();
	setOutput(GIMSK, PCiEn, LOW);      // enable interrupt pin change.	
	setOutput(PCMsKn, PCInTn, LOW);	// set bit PCINTN on this interrupt.
	
}

void powerDown()
{
	setOutput( PORTA, LED1, LOW);
	setOutput( PORTA, LED0, LOW);
	setOutput( PORTA, SHDWN, LOW);
	
	cbi(ADCSRA,ADEN);                              //switch Analog to Digital Converter OFF
}
