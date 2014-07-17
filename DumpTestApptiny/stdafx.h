/*
 * stdafx.h
 *
 * Created: 7/15/2014 12:41:34 PM
 *  Author: annim
 */ 


#ifndef STDAFX_H_
#define STDAFX_H_

#include <avr/io.h>

#define LED0			( PA2 )
#define LED1			( PA1 )
#define SHDWN			( PA0 )

#define LED0_ON			( 1 << PA2 )
#define LED0_OFF		( 0 << PA2 )
#define LED1_ON			( 1 << PA1 ) 
#define LED1_OFF		( 0 << PA1 )
#define AL_SHDN_HIGH	( 1 << PA0 )
#define AL_SHDN_LOW		( 0 << PA0 )
#define PWR				PA3			// by default this is HIGH as it is pulled HIGH via VDD.
#define PWR_BUTTON		( 1 << PWR)

#define PRESS_WAIT 45000



#endif /* STDAFX_H_ */