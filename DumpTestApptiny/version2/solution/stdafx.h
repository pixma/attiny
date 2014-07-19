/*
 * stdafx.h
 *
 * Created: 7/18/2014 11:26:20 AM
 *  Author: annim
 */ 


#ifndef STDAFX_H_
#define STDAFX_H_

#include <avr/io.h>
#include <avr/iotn84.h>

#define LED0			PA1
#define LED1			PA2
#define SHDWN			PA0

#define LED0_ON			1<<PA2
#define LED0_OFF		0<<PA2
#define LED1_ON			1<<PA1
#define LED1_OFF		0<<PA1
#define AL_SHDN_HIGH	1<<PA0
#define AL_SHDN_LOW		0<<PA0
#define PWR				PA3			// by default this is HIGH as it is pulled HIGH via VDD.
#define PWR_READ		PINA3
#define PWR_BUTTON		1<<PWR

#define PRESS_WAIT 55000


#ifndef cbi
//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= -_BV(bit))
#define cbi(sfr, bit) (sfr) &= ~(1<<bit)
#endif
#ifndef sbi
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define sbi(sfr, bit) (sfr) |= (1<<bit)
#endif

#ifndef HIGH
#define HIGH true
#endif

#ifndef LOW
#define LOW false
#endif


#endif /* STDAFX_H_ */