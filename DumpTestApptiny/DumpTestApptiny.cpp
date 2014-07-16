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
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "standard.h"
//////////////////////////////////////////////////////////////////////////

bool devState = false;
char chCount = 0;
unsigned char chButtonState;
unsigned int nTimeMillis = 0;
//////////////////////////////////////////////////////////////////////////


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= -_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//////////////////////////////////////////////////////////////////////////

// void serviceRoutine(){
// 	if (devState == true)
// 	{
// 		//code goes for true state;
// 	 	sleep_disable();
// 		MCUCR = 0x00;
// 		DDRA |= ( LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set data direction.
// 		PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)	
// 	}
// 	else{
// 		//code goes for false state;
// 		DDRA |= ( LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set data direction.
// 		PORTA |= ( LED0_OFF | LED1_OFF | AL_SHDN_LOW);			// shutoff leds and regulator.
// 				
// 		set_sleep_mode( SLEEP_MODE_IDLE );
// 		sleep_enable();
// 		sleep_mode();
// 		//mcu stops at above.
// 		//if mcu resumes then it will execute from next line below.
// 		MCUCR = 0x00;		// clear MCUCR so effect of sleep or any other source of reset, shall not reset or put mcu to sleep.
// 		sleep_disable();		
// 	}
// }

//////////////////////////////////////////////////////////////////////////

ISR( PCINT0_vect ){
	
// 	chCount ++;
// 	if (chCount == 2)
// 	{
// 		chCount = 0;
// 		devState = (!devState);
// 		serviceRoutine();// call for this routine to be serviced.
// 	}	
	
	if ( (PINA&(1<<PINA3)) == 0x00 && devState == true)
	{		
		PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
		devState = false;
		//PORTA = PORTA^(LED0_ON);
	}
	
		
	//devState = true;
	
}


//////////////////////////////////////////////////////////////////////////


int main(void)
{	
	MCUCR = 0x00;
	cli();
	DDRA |= ( LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set data direction.
	DDRA |= (0<<PWR);										// set PWR button pin as input.
	PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
	
			
	
    while(1)
    {
         //code goes here.		 
		 
		if( (PINA&(1<<PINA3)) == (0x00) && devState == false){
			
			while (nTimeMillis < PRESS_WAIT)
			{
				if ( (PINA&(1<<PINA3)) == (0x00) )
				{
					nTimeMillis++;						
				}
				else{
					break;
				}
			}
			
			if (nTimeMillis < PRESS_WAIT)
			{
				nTimeMillis = 0;
				continue;
			}
// 			
			nTimeMillis = 0;
			
			PORTA &= (LED0_OFF | LED1_OFF | AL_SHDN_LOW);			// Turn off.
								
			devState = true;
								
			//////////////////////////////////////////////////////////////////////////
			// code to plant interrupt on button PWR button on PA3.
			cli();
			nTimeMillis = 0;
						
			PCMSK0 |= ( 1 << PCINT3);	// set bit PCINT3 as button is on this interrupt.			
			GIMSK |= ( 1 << PCIE0);	// enable interrupt pin change.from 0 - 7 pcints. where pcint3 is been configured.
			sei();
			//////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////
			// sleep now.
			sbi(MCUCR,PUD);                                  //Disables All Internal Pullup Resistors
			ACSR = ( 1 << ACD );			// Turn off analog comparator.
			PRR = 0x0F;						// reduce all power before sleep.
			cbi(ADCSRA,ADEN);                              //switch Analog to Digital Converter OFF
			
			set_sleep_mode( SLEEP_MODE_IDLE );			
			sleep_enable();
			sleep_mode();// sleep_diable is included in this macro function.
			//////////////////////////////////////////////////////////////////////////
			
			sbi(ADCSRA,ADEN);                             //switch Analog to Digital Converter ON
			
		}	
		
		
		for (int i=0; i < 1000; i++)
		{
			// nops.
		}
		
		if (devState == true)
		{
			set_sleep_mode( SLEEP_MODE_IDLE );
			sleep_enable();
			sleep_mode();// sleep_diable is included in this macro function.
			//////////////////////////////////////////////////////////////////////////
		}
		else{
			PORTA |= (LED0_ON | LED1_ON | AL_SHDN_HIGH);			// set HIGH.Set SHDN to HIGH (Active LOW)
		}
		
    }
}





// 	cli();
// 	PCMSK0 = 0x00;	// clear the register first.
// 	PCMSK0 |= ( 1 << PCINT3);	// set bit PCINT3 as button is on this interrupt.
// 	GIMSK |= ( 1 << PCIE0);	// enable interrupt pin change.from 0 - 7 pcints. where pcint3 is been configured.
// 	sei();	// now enable global interrupt.


// 		 if( chButtonState ==   0x00){
// 			 PORTA |= ( LED0_OFF | LED1_OFF | AL_SHDN_LOW);			// shutoff leds and regulator.
// 		 }
// 		 else if ( chButtonState ==   0x00 )
// 		 {
// 			 PORTA |= ( LED0_OFF | LED1_OFF | AL_SHDN_LOW);			// shutoff leds and regulator.
// 		 }
// 		 else{
// 			 PORTA |= ( LED0_OFF | LED1_OFF | AL_SHDN_LOW);			// shutoff leds and regulator.
// 		 }
