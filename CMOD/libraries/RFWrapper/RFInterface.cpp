/*
*
*
*
*
*
*/

#include "RFInterface.h"
#include "RFWrapper.h"

static RFWrapper m_rfWrapper;

bool sendImpedance( float *samples, unsigned char numOfValues )
{
	m_rfWrapper.sendImpedance( samples, numOfValues );
}

bool sendPhase( float *samples, unsigned char numOfValues )
{
	m_rfWrapper.sendPhase( samples, numOfValues );
}

bool sendTemperature( float temperature )
{
	m_rfWrapper.sendTemperature( temperature );
}

bool sendHumidity( unsigned char humidity )
{
	m_rfWrapper.sendHumidity( humidity );
}

bool sendBatteryVoltage( float batteryVoltage )
{
	m_rfWrapper.sendBatteryVoltage( batteryVoltage );
}