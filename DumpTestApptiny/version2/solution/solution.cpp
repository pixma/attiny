/*
 * solution.cpp
 *
 * Created: 7/18/2014 11:04:27 AM
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


#include "stdafx.h"
#include "standard.h"

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


ISR( PCINT0_vect ){
	// ISR code goes here.	
}

bool isButtonPressed()
{
	if ( (PINA&(1<<PWR_READ))   == 0x00 )
	{
		return true;
	}
	else{
		return false;
	}
}

int main(void)
{
	//init device
	initDevice();
	
	// battery check code goes here
	
	// powerDown all
	powerDown();
	
	//plant PCI here
	plantPinChangeInt();	
	
	//sleep here every time.
	sleepMe();			
	
    while(1)
    {
		//remove PCINTs.
		removePinChangeInt(  );
		
        //simple delay goes here
        pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		 
		//simple delay goes here
		pressWaitDelay(); 
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay(); 
		
		//simple delay goes here
		pressWaitDelay();
        
        // power On
        powerOn();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
        
		while (isButtonPressed());
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//
        // monitor battery level or just check  battery level here a non blocking api.
		//
		
		if( !isButtonPushedLong() ){
			continue;
			// this portion is where an invalid button press event is recorded.
		}
		
		//else goes here out of if else snippet.
		
		// power Down all
		powerDown();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		//simple delay goes here
		pressWaitDelay();
		
		
		//plant PCI here
		plantPinChangeInt();
		
		//sleep here every time.
		sleepMe();		
		
    }
}