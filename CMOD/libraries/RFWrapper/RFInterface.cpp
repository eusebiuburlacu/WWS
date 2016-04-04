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
	}
}

void initRF()
{
	m_rfWrapper = new RFWrapper();
	attachInterrupt(3, interruptRoutine, FALLING); // interrupt 3 equivalent to chipKIT_CMOD pin 7(INT3) 
	interrupts();
	Serial.println("initRF");
}

bool sendImpedance( float *samples,  unsigned long startFreq, unsigned char numOfValues, ACKCallback callback  )
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->sendImpedance( samples, startFreq, numOfValues, callback );
	}
	return result;
}

bool sendPhase( float *samples, unsigned char numOfValues, ACKCallback callback )
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->sendPhase( samples, numOfValues, callback );
	}
	return result;
}

bool sendTemperature( float temperature, ACKCallback callback )
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->sendTemperature( temperature, callback );
	}
	return result;
}

bool sendHumidity( unsigned char humidity, ACKCallback callback )
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->sendHumidity( humidity, callback );
	}
	return result;
}

bool sendBatteryVoltage( float batteryVoltage, ACKCallback callback )
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->sendBatteryVoltage( batteryVoltage, callback );
	}
	return result;
}

bool registerRXCallback(RXCallback callback)
{
	bool result = false;
	if( m_rfWrapper != 0 )
	{
		result = m_rfWrapper->registerRXCallback( callback );
	}
	return result;
}	

rx_info *getRXData(int &dataLen)
{
	rx_info *result = 0;
	if( m_rfWrapper != 0 )
	{
		result = (rx_info *)m_rfWrapper->get_rxinfo(dataLen);
	}
	return result;
}

tx_info *getTXData()
{
	tx_info *result = 0;
	if( m_rfWrapper != 0 )
	{
		result = (tx_info *)m_rfWrapper->get_txinfo();
	}
	return result;
}