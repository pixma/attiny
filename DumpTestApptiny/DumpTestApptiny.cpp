/*
 * DumpTestApptiny.cpp
 *
 * Created: 7/15/2014 12:37:21 PM
 *  Author: annim
 */ 

/************************************************************************/
/* 
http://fab.cba.mit.edu/classes/4.140/people/charles/07/index.html
https://www.google.co.in/url?sa=t&rct=j&q=&esrc=s&source=web&cd=5&cad=rja&uact=8&ved=0CEkQtwIwBA&url=http%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3D0aAwKT0YWJU&ei=dGXGU-qGCJOPuATt-YDAAw&usg=AFQjCNExa8sP-cECpAZhHC8Po6FgOaBd7g&sig2=FJPSZw1CQt0WC_12l5U0hQ&bvm=bv.71126742,d.c2E

                                                                     */
/************************************************************************/


//////////////////////////////////////////////////////////////////////////
#define __AVR_ATtiny84__ 1
#define F_CPU 800000UL
//////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "standard.h"
//////////////////////////////////////////////////////////////////////////

bool devState = false;
char chCount = 0;
unsigned char chButtonState;
unsigned int nTimeMillis = 0;
bool intentToOff = true;
bool intentToOn = false;
bool interruptFired = false;
//////////////////////////////////////////////////////////////////////////


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= -_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//////////////////////////////////////////////////////////////////////////
void serviceRoutine(){
	
	if ( (PINA&(1<<PINA3)) == (0x00) )
	{
		intentToOn = true;
	}
	
	if (  (PINA&(1<<PINA3)) == (0x00) && intentToOn == true)
	{
		// take action on LOW state
		//////////////////////////////////////////////////////////////////////////
		// button state goes like this
		// ----____----
		//     |  |
		//    action
		//////////////////////////////////////////////////////////////////////////
		//remove pin change interrupt for now, immediately.
		cli();//this will unset the I bit in SREG, disable any interrupts to occur/ take place.
		GIMSK |= ( 0 << PCIE0);	// disable interrupt pin change.from 0 - 7 pcints. where pcint3 is been configured.
		PCMSK0 |= ( 0 << PCINT3);	// unset bit PCINT3 as button is on this interrupt.
		//////////////////////////////////////////////////////////////////////////
		// done removing PCINT
		//////////////////////////////////////////////////////////////////////////
		interruptFired = true;
		intentToOff = false;
		intentToOn = false;
		
		if (interruptFired == true)
		{
			PORTA |= (LED0_ON);
			nTimeMillis = 0;
			while ( 1 )
			{
				nTimeMillis++;
				if (nTimeMillis > PRESS_WAIT)
				{
					break;
				}
			}
			nTimeMillis = 0;
			while ( 1 )
			{
				nTimeMillis++;
				if (nTimeMillis > PRESS_WAIT)
				{
					break;
				}
			}
			interruptFired = false;
			//////////////////////////////////////////////////////////////////////////
			//  set up device
			DDRA |= ( LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set data direction.
			DDRA |= (0<<PWR);										// set PWR button pin as input.
			PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
			//////////////////////////////////////////////////////////////////////////
			nTimeMillis = 0;
			while ( 1 )
			{
				nTimeMillis++;
				if (nTimeMillis > PRESS_WAIT)
				{
					break;
				}
			}
			
		}
	}
	else
	devState = false;// on sleep ram/ registers are unaltered.
}
//////////////////////////////////////////////////////////////////////////

ISR( PCINT0_vect ){
	
	serviceRoutine();
}


//////////////////////////////////////////////////////////////////////////

long readVCC(){
	
	ADMUX =  _BV(MUX5) | _BV(MUX0);
	ADCSRA |= _BV(ADSC); // Start conversion
	
	unsigned int low  = ADCL; // must read ADCL first - it then locks ADCH
	unsigned int high = ADCH; // unlocks both
	
	long result = (high<<8 | low );
	
	result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
	
	 return result;
}


int main(void)
{	
	//////////////////////////////////////////////////////////////////////////
	// start off with clearing all interrupts.		
	MCUCR = 0x00;
	wdt_disable();
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	
	//////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////
	//  set up device
	DDRA |= ( LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set data direction.
	DDRA |= (0<<PWR);										// set PWR button pin as input.
	PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
	//////////////////////////////////////////////////////////////////////////
			
	
    while(1)
    {
         //code goes here.
		 
		 
		 
		 nTimeMillis = 0;
		 while( 1 ){
			 nTimeMillis++;
			 if (nTimeMillis > PRESS_WAIT)
			 {
				 break;
			 }
		 }
		 intentToOff = true;
		 nTimeMillis = 0;
		if( (PINA&(1<<PINA3)) == (0x00) && (intentToOff == true))
		{
			
			interruptFired = false;
			PORTA &= ~(1<<LED1);
			//////////////////////////////////////////////////////////////////////////
			// wait and until some timeout occurs
			// at same time pool for pin state.
			//////////////////////////////////////////////////////////////////////////
			while ( (PINA&(1<<PINA3)) == (0x00) )			
			{				
				nTimeMillis++;								
				
				if( nTimeMillis < PRESS_WAIT ){
					//nothing to do.
				}
				else if (nTimeMillis > PRESS_WAIT)
				{
					// timeout occurs.
					devState = true;		//indicates timeout occurs.
					break;
				}
			}
			
			if (devState == true)
			{
				nTimeMillis = 0;			//reset values now;
				devState = false;
				
				//cbi( PORTA, LED0 );
				//cbi( PORTA, LED1 );
				//cbi( PORTA, SHDWN );
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				// set indication that key is pressed
				PORTA &= ( LED0_OFF | LED1_OFF| AL_SHDN_LOW );
				//////////////////////////////////////////////////////////////////////////
				
				//now plant pin change interrupt.
				//////////////////////////////////////////////////////////////////////////
				cli();
				PCMSK0 |= ( 1 << PCINT3);	// set bit PCINT3 as button is on this interrupt.			
				GIMSK |= ( 1 << PCIE0);	// enable interrupt pin change.from 0 - 7 pcints. where pcint3 is been configured.
				sei();		//enable global interrupt for changes to come into effect.
				//////////////////////////////////////////////////////////////////////////
				
				intentToOff = false;	
				interruptFired = false;			
				//////////////////////////////////////////////////////////////////////////
				// sleep now
				//////////////////////////////////////////////////////////////////////////
				sbi(MCUCR,PUD);                                  //Disables All Internal Pullup Resistors
				ACSR = ( 1 << ACD );							// Turn off analog comparator.
				cbi(ADCSRA,ADEN);                              //switch Analog to Digital Converter OFF
				PRR = 0x0F;						// reduce all power before sleep.
				// power related steps performed now.
				set_sleep_mode( SLEEP_MODE_PWR_DOWN );
				sleep_enable();
				sleep_mode();
				// mcu goes to sleep...zzz
				//////////////////////////////////////////////////////////////////////////
				// now pci will take action
				// ISR will be served
				//////////////////////////////////////////////////////////////////////////
				
				//////////////////////////////////////////////////////////////////////////
				// and if pin goes high, then PCI will fire and wake up the mcu
				//////////////////////////////////////////////////////////////////////////
				if ( (PINA&(1<<PINA3)) == (0x04) && devState == false)
				{
					// put mcu to sleep again.
					
					//now plant pin change interrupt.
					//////////////////////////////////////////////////////////////////////////
					cli();
					PCMSK0 |= ( 1 << PCINT3);	// set bit PCINT3 as button is on this interrupt.
					GIMSK |= ( 1 << PCIE0);	// enable interrupt pin change.from 0 - 7 pcints. where pcint3 is been configured.
					sei();		//enable global interrupt for changes to come into effect.
					//////////////////////////////////////////////////////////////////////////
					sbi(MCUCR,PUD);                                  //Disables All Internal Pullup Resistors
					ACSR = ( 1 << ACD );							// Turn off analog comparator.
					cbi(ADCSRA,ADEN);                              //switch Analog to Digital Converter OFF
					PRR = 0x0F;						// reduce all power before sleep.
					//////////////////////////////////////////////////////////////////////////
					// power related steps performed now.
					//////////////////////////////////////////////////////////////////////////
					set_sleep_mode( SLEEP_MODE_PWR_DOWN );
					sleep_enable();
					sleep_mode();
					//////////////////////////////////////////////////////////////////////////
				}
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////				
				//////////////////////////////////////////////////////////////////////////
			}
			else{
				//////////////////////////////////////////////////////////////////////////
				// button is not pressed - in a valid way.
				//////////////////////////////////////////////////////////////////////////
				PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
				//////////////////////////////////////////////////////////////////////////
			}
		}
	}
}