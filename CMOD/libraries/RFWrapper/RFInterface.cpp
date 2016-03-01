/*
*
*
*
*
*
*/

#include "RFInterface.h"
#include "RFWrapper.h"

static RFWrapper *m_rfWrapper;

void interruptRoutine()
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->interrupt_handler(); // mrf24 object interrupt routine
		attachInterrupt(3, interruptRoutine, FALLING); // interrupt 3 equivalent to chipKIT_CMOD pin 7(INT3) 
		interrupts();
		Serial.println("initRF");
	}
}

void initRF()
{
	m_rfWrapper = new RFWrapper();
}

bool sendImpedance( float *samples, unsigned char numOfValues )
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->sendImpedance( samples, numOfValues );
	}
}

bool sendPhase( float *samples, unsigned char numOfValues )
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->sendPhase( samples, numOfValues );
	}
}

bool sendTemperature( float temperature )
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->sendTemperature( temperature );
	}
}

bool sendHumidity( unsigned char humidity )
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->sendHumidity( humidity );
	}
}

bool sendBatteryVoltage( float batteryVoltage )
{
	if( m_rfWrapper != 0 )
	{
		m_rfWrapper->sendBatteryVoltage( batteryVoltage );
	}
}