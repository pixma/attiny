/*
 * standard.h
 *
 * Created: 7/18/2014 11:27:21 AM
 *  Author: annim
 */ 


#ifndef STANDARD_H_
#define STANDARD_H_

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* void initDevice();
Description: initialization of device.                                   */
/************************************************************************/
void initDevice();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* void setOutput(unsigned int portNumber, unsigned int pinNumber , bool state) 
state: true- HIGH
state: false- LOW.                                                                    */
/************************************************************************/
void setOutput(unsigned int portNumber, unsigned int pinNumber, bool state);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* void pinMode( unsigned int portnumber, unsigned int pinNumber, bool state )   
state = true : set Output
state = false: set Input.                                                                  */
/************************************************************************/
void pinMode( unsigned int portnumber, unsigned int pinNumber, bool state );
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

/**
 * \brief 
 * 
 * \param portNumber : PORT
 * \param pinNumber  : Bit
 * 
 * \return unsigned int state 0x00 or 0x01
 */
unsigned int digitalRead( unsigned int portNumber, unsigned int pinNumber );
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * Will sleep mcu.
 * 
 * \return void
 */
void sleepMe();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * a delay on button press.
 Can be configured on Macro PRESS_WAIT
 * 
 * \return bool
	true : if event valid
	false: if event recorded as invalid.
 */
bool pressWaitDelay();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * read millivolt of MCU.
 * 
 * \return unsigned int from 0 to 5000 mV.
 */
unsigned int readBatterymilliVolts();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * Check if button is pressed for long time.
 * 
 * \return bool true: if event is valid else returns false.
 */
bool isButtonPushedLong();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * 
 * \param PCiEn	Enable pin change Int port value 0, 1, 2...
 * \param PCMsKn Pin change int mask value 0, 1, 2 ....
 * \param PCInTn particular Pin .
 * 
 * \return void
 */
void plantPinChangeInt(unsigned int PCiEn, unsigned int PCMsKn, unsigned int PCInTn);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * 
 * \param PCiEn Disable pin change Int port value 0, 1, 2...
 * \param PCMsKn Pin change int mask value 0, 1, 2 ....
 * \param PCInTn particular pin
 * 
 * \return void
 */
void removePinChangeInt( unsigned int PCiEn, unsigned int PCMsKn, unsigned int PCInTn );
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * power On all peripherals.
 * 
 * \return void
 */
void powerOn();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/**
 * \brief 
 * power Down all peripherals.
 * 
 * \return void
 */
void powerDown();
//////////////////////////////////////////////////////////////////////////


#endif /* STANDARD_H_ */